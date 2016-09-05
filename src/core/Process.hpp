#pragma once
#include "Types.hpp"
#include <Windows.h>

class FProcess {
	friend class FWindow;
public:
	// Finds the process.
	b32 Find(WCHAR const* wndName, WCHAR const* wndClass);

	// Returns true if the process is currently open.
	b32 IsOpen();

	// Opens the process for memory access.
	b32 Open(b32 writeAccess);

	// Closes the process for read/write access.
	void Close();

	// Reads memory from a process.
	b32 ReadBytes(u64 base, void* dst, u32 dstBytes);

	// Writes memory into the process.
	b32 WriteBytes(u64 base, void const* src, u32 srcBytes);

	// Type generic memory read.
	template <typename Type>
	Type Read(u64 base) {
		Type x;
		return ReadBytes(base, &x, sizeof(x)) ? x : Type{};
	}

	// Type generic memory write.
	template <typename Type>
	b32 Write(u64 base, Type const& x) {
		return WriteBytes(base, &x, sizeof(x));
	}

private:
	HANDLE Process;
	HWND Window;
	DWORD ProcessID;
};
