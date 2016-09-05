#pragma once
// Required.
#include "core/Process.hpp"
#include "core/Render.hpp"
#include "core/Timer.hpp"
#include "core/Window.hpp"

// Helpers.
#include "Core.hpp"
#include "core/Math.hpp"
#include "core/Matrix.hpp"
#include "core/Utility.hpp"
#include "core/Vector.hpp"

class FCheat {
public:
	//=========================================================================
	// Interface functions.
	//=========================================================================

	// Runs the cheat. Only a single instance is allowed at a time.
	void Run(WCHAR const* cmdLine, WCHAR const* wndName, WCHAR const* clsName);

protected:
	//=========================================================================
	// User functions.
	//=========================================================================

	virtual b32 Create() = 0;
	virtual b32 Ready() = 0;
	virtual void Update() = 0;

	//=========================================================================
	// Private interfaces.
	//=========================================================================

	FTimer Timer;
	FProcess Process;
	FWindow Window;
	FRender Render;
};
