#include "Process.hpp"

b32 FProcess::Find(WCHAR const* wndName, WCHAR const* wndClass) {
	Window = FindWindowW(wndClass, wndName);

	if (Window == 0) {
		ProcessID = 0;
		return false;
	}

	GetWindowThreadProcessId(Window, &ProcessID);

	return true;
}

b32 FProcess::IsOpen() {
	if (IsWindow(Window)) {
		return true;
	}

	Window = 0;
	ProcessID = 0;

	return false;
}

b32 FProcess::Open(b32 writeAccess) {
	if (Process) {
		Close();
	}

	Process = OpenProcess(writeAccess ? PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION : PROCESS_VM_READ, FALSE, ProcessID);
	return (Process != NULL);
}

void FProcess::Close() {
	if (Process) {
		CloseHandle(Process);
		Process = NULL;
	}
}

b32 FProcess::ReadBytes(u64 base, void * dst, u32 dstBytes) {
	return ReadProcessMemory(Process, (void*)base, dst, dstBytes, 0);
}

b32 FProcess::WriteBytes(u64 base, void const * src, u32 srcBytes) {
	return WriteProcessMemory(Process, (void*)base, src, srcBytes, 0);
}
