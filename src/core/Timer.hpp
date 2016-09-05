#pragma once
#include "Types.hpp"

// High resolution timing interface.
class FTimer {
public:
	// Starts or resets timing. Update isn't valid until this is called.
	void Start();

	// Updates the timer values.
	void Update();

public:
	i64 TotalUS; // Time in microseconds since the start of the timer.
	i64 DeltaUS; // Time in microseconds since the last update or the start of the timer.

private:
	i64 Frequency; // Timer CPU frequency.
	i64 InitTicks; // The time in CPU ticks when the timer started.
	i64 PrevTicks; // The time in CPU ticks when the last update happened.
};
