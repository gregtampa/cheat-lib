#pragma once
#include "Types.hpp"

//=============================================================================
// Helper macros.
//=============================================================================

// Clears the given structure.
#define CLEAR(x) memset(x, 0, sizeof(*(x)))

// Returns the number of elements in a array.
#define COUNT(x) (sizeof(x) / sizeof(*(x)))

// Combines the expansion of the given two macros together.
#define COMBINE_EXPAND(x, y) x##y

// Combines the two expressions together.
#define COMBINE(x, y) COMBINE_EXPAND(x, y)

// If x is non-zero false is returned.
#define FALSE_IF(x) if (x) { return false; }

// If x is zero false is returned.
#define FALSE_IF_ZERO(x) if ((x) == 0) { return false; }

// If x is non-zero a jump is performed to the cleanup label.
#define JMP_IF(x) if (x) { goto __cleanup; }

// If x is zero a jump is performed to the cleanup label.
#define JMP_IF_ZERO(x) if ((x) == 0) { goto __cleanup; }

// If x is non-zero a return is performed with the given arguments.
#define RET_IF(x, ...) if (x) { return __VA_ARGS__; }

// If x is zero a return is performed with the given arguments.
#define RET_IF_ZERO(x, ...) if ((x) == 0) { return __VA_ARGS__; }

// Turns the given expression into a string.
#define STRING(x) #x

// Expands the given expression and turns it into a string.
#define STRING_EXPAND(x) STRING(x)
