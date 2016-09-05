#include "Cheat.hpp"

void FCheat::Run(WCHAR const* cmdLine, WCHAR const* wndName, WCHAR const* clsName) {
	// Ensure single instance.
	if (HANDLE mutex = OpenMutexW(MUTEX_ALL_ACCESS, 0, cmdLine)) {
		CloseHandle(mutex);
		return;
	} else {
		CreateMutexW(0, 0, cmdLine);
	}

	// Create subsystems.
	Process.Find(wndName, clsName);
	Window.Create(&Process);
	Render.Create(&Window);
	Render.SetFont(L"Consolas", 16);

	// Setup the cheat.
	Create();

	// Run the overlay until it closes.
	Timer.Start();

	i64 lastTrack = 0;
	b32 isGameOpen = false;

	while (Window.PumpEvents()) {
		Timer.Update();

		// Resize and reposition the overlay to match the game window every ~1s.
		if (Timer.TotalUS - lastTrack > 1000000) {
			lastTrack = Timer.TotalUS;
			isGameOpen = Process.IsOpen();
			Window.Retrack();
		}

		if (Render.FrameInit() == false) {
			break;
		}

		f32 hue = 0.5f + sin(Timer.TotalUS / 10000000.0) * 0.5f;
		u32 color = Render.HSVAtoRGBA(hue, 1.0f, 1.0f, 1.0f);

		// Run the cheat.
		if (isGameOpen) {
			if (Ready()) {
				Update();
			} else {
				Render.DrawText({ 15.f, 15.f }, color, "Not Ready");
			}
		} else {
			Render.DrawText({ 15.f, 15.f }, color, "Game Not Found");
		}


		Render.FramePost();
		Sleep(6);
	}

	Render.Destroy();
	Window.Destroy();
	Process.Close();
}
