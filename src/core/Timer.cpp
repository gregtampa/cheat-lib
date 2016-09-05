#include "Timer.hpp"
#include <Windows.h>

void FTimer::Start() {
	QueryPerformanceFrequency((LARGE_INTEGER*)&Frequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&InitTicks);
	PrevTicks = InitTicks;
}

void FTimer::Update() {
	i64 now;
	QueryPerformanceCounter((LARGE_INTEGER*)&now);

	TotalUS = ((now - InitTicks) * 1000000) / Frequency;
	DeltaUS = ((now - PrevTicks) * 1000000) / Frequency;
	PrevTicks = now;
}
