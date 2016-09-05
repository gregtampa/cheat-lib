#pragma once
#include "Types.hpp"
#include <Windows.h>

class FProcess;

class FWindow {
	friend class FRender;
public:
	//=========================================================================
	// Public types.
	//=========================================================================

	// Key binding.
	struct FBind {
		u32 Code; // Virtual-key code (VK).
		u32 Flags; // Modifier flags (MOD_ALT, MOD_CONTROL, MOD_SHFIT...)
		void* Data; // Data to pass into the callback function.
		void(*Func)(void* data); // The function to call when the bind is down.
	};

	//=========================================================================
	// Interface functions.
	//=========================================================================

	// Creates the window overlay associated with the given process.
	void Create(FProcess* process);

	// Destroys the overlay.
	void Destroy();

	// Pumps events out of the window's message queue. Returns false when the window has closed.
	b32 PumpEvents();

	// Registers a list of hot keys.
	void RegisterKeys(FBind const* binds, u32 count);

	// Updates the overlay's size/position relative to the process. Returns true if the window size changed.
	b32 Retrack();

	// Exits the application.
	void Quit();

protected:
	//=========================================================================
	// Private functions.
	//=========================================================================

	// Win32 message callback for the overlay's window class.
	static LRESULT CALLBACK MessageCallback(HWND wnd, UINT msg, WPARAM wp, LPARAM lp);

	// Class message handler for the specific instance of the overlay.
	LRESULT HandleMessage(HWND wnd, UINT msg, WPARAM wp, LPARAM lp);

	//=========================================================================
	// Private data.
	//=========================================================================

	FProcess* Process; // Process the window will match its size and position with.
	HWND Handle; // Handle for the overlay window.
	POINT Pos; // Position of the overlay.
	POINT Size; // Size of the overlay.
	b32 IsOpen; // True if the overlay is open and hasn't been asked to close.
	FBind Binds[32]; // Registered hotkeys.
};
