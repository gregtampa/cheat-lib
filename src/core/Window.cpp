#include "Window.hpp"
#include "Math.hpp"
#include "Process.hpp"
#include "Utility.hpp"
#include <windowsx.h>
#include <dwmapi.h>

void FWindow::Create(FProcess * process) {
	Process = process;

	WNDCLASS wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MessageCallback;
	wc.hInstance = GetModuleHandleW(0);
	wc.hIcon = LoadIconW(0, IDI_APPLICATION);
	wc.hCursor = LoadCursorW(0, IDC_ARROW);;
	wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
	wc.lpszClassName = L"c";
	RegisterClassW(&wc);

	RECT r;
	GetWindowRect(GetDesktopWindow(), &r);

	Size.x = r.right - r.left;
	Size.y = r.bottom - r.top;

	Handle = CreateWindowExW(
		WS_EX_NOACTIVATE | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_TRANSPARENT,
		wc.lpszClassName, L"", WS_POPUP | WS_VISIBLE, r.left, r.top, Size.x, Size.y, 0, 0, wc.hInstance, 0);

	if (Handle == 0) {
		return;
	}

	SetLastError(0);
	SetWindowLongPtrW(Handle, GWLP_USERDATA, (LONG_PTR)this);
	if (GetLastError() != 0) {
		return;
	}

	if (SetLayeredWindowAttributes(Handle, 0, 0xFF, LWA_ALPHA) == FALSE) {
		return;
	}

	if (FAILED(DwmExtendFrameIntoClientArea(Handle, (MARGINS*)&r))) {
		return;
	}

	IsOpen = true;

	if (process->IsOpen()) {
		Retrack();
	}
}

void FWindow::Destroy() {
	if (Handle) {
		CloseWindow(Handle);
	}
}

b32 FWindow::PumpEvents() {
	MSG msg;
	while (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return IsOpen;
}

void FWindow::RegisterKeys(FBind const* binds, u32 count) {
	CLEAR(Binds);

	u32 end = Math::Min((u32)COUNT(Binds), count);
	for (u32 i = 0; i < end; ++i) {
		auto& bind = binds[i];
		if (RegisterHotKey(Handle, WM_USER + i, bind.Flags, bind.Code)) {
			Binds[i] = binds[i];
		}
	}
}

b32 FWindow::Retrack() {
	if (Process->Window == 0) {
		return false;
	}

	SetWindowPos(Handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	RECT r = {};
	if (GetClientRect(Process->Window, &r) == FALSE) {
		return false;
	}

	i32 width = r.right - r.left;
	i32 height = r.bottom - r.top;

	if (width <= 0 || height <= 0) {
		return false;
	}

	POINT p = {};
	if (ClientToScreen(Process->Window, &p) == FALSE) {
		return false;
	}

	b32 sameSize = (width == Size.x && height == Size.y);
	if (p.x == Pos.x && p.y == Pos.y && sameSize) {
		return false;
	}

	SetWindowPos(Handle, HWND_TOPMOST, p.x, p.y, width, height, 0);

	Pos = p;
	Size.x = width;
	Size.y = height;

	return (sameSize == false);
}

void FWindow::Quit() {
	IsOpen = false;
}

LRESULT CALLBACK FWindow::MessageCallback(HWND wnd, UINT msg, WPARAM wp, LPARAM lp) {
	if (auto window = (FWindow*)GetWindowLongPtrW(wnd, GWLP_USERDATA)) {
		return window->HandleMessage(wnd, msg, wp, lp);
	}

	return DefWindowProcW(wnd, msg, wp, lp);
}

LRESULT FWindow::HandleMessage(HWND wnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
		case WM_CLOSE: {
			IsOpen = false;
		} return 0;

		case WM_DEVICECHANGE: {
			Retrack();
		} return 0;

		case WM_GETMINMAXINFO: {
			MINMAXINFO* mmi = (MINMAXINFO*)lp;
			mmi->ptMinTrackSize = { 64, 64 };
		} return 0;

		case WM_HOTKEY: {
			if (wp >= WM_USER && wp < WM_USER + COUNT(Binds)) {
				auto& bind = Binds[wp - WM_USER];
				if (bind.Func) {
					bind.Func(bind.Data);
				}
			}
		} break;

		case WM_SIZE: {
			Size.x = LOWORD(lp);
			Size.y = HIWORD(lp);
		} break;

		case WM_SYSCOMMAND: {
			switch (wp) {
				case SC_CLOSE: {
					IsOpen = false;
				} return 0;
			}
		} break;

		case WM_SYSKEYDOWN: {
			if (wp == VK_F4) {
				IsOpen = false;
			}
		} return 0;

		case WM_QUIT: {
			IsOpen = false;
		} return 0;
	}

	return DefWindowProcW(wnd, msg, wp, lp);
}
