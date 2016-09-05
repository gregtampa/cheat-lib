//=============================================================================
// Type-generic containers. These are used over the std containers like
// vector, map, array, etc because of domain specific requirements imposed
// for the sake of performance, code bloat and complexity.
//
// Dynamic memory allocation is limited and frowned upon in use (favoring
// fixed size, known limits). CRT allocators (new/delete) can't be used on
// Win32 builds to reduce binary bloat. Constructors / Destructors are never
// used on any data type (favoring explicit initialization and cleanup), and
// exceptions are disabled because of poor code generation from currnet
// compilers.
//
// The principles of std containers are however inherited in the design of
// these containers and many of the same conventions are duplicated for
// convenience.
//=============================================================================
#pragma once
#include "Core.hpp"

// Fixed capacity array (does not allocate memory when full). Not functionally equivalent to std::array because
// it keeps track of the number of items in the array and provides convenience functions for working with them.
template <typename Type, u32 Capacity> struct TFixedArray {
	u32 Count; // Current number of items in the fixed array.
	Type Items[Capacity]; // Item data.

	// Returns an item from the array.
	FORCEINLINE Type& operator[](i32 index) {
		return Items[index];
	}

	// Returns a pointer to an item in the array.
	FORCEINLINE Type* operator+(i32 index) {
		return Items + index;
	}

	// Returns a pointer to the start of the array.
	FORCEINLINE Type* begin() {
		return Items;
	}
	
	// Returns a pointer to the end of the array.
	FORCEINLINE Type* end() {
		return Items + Count;
	}

	// Returns a pointer to an item in the array if the index is valid. Returns item on failure.
	FORCEINLINE Type* At(u32 index, Type* item = 0) {
		return (index < Count) ? (Items + index) : item;
	}
	
	// Returns the last element in the array.
	FORCEINLINE Type& Back() {
		return Items[Count - 1];
	}

	// Returns the first element in the array.
	FORCEINLINE Type& Front() {
		return Items[0];
	}

	// Returns the array pointer.
	FORCEINLINE Type* Data() {
		return Items;
	}

	// Returns true if the array is full.
	CONSTEXPR b32 Full() const {
		return Count >= Capacity;
	}

	// Returns the maximum capacity of the array.
	CONSTEXPR u32 MaxSize() const {
		return Capacity;
	}

	// Returns the current number of items in the array.
	CONSTEXPR u32 Size() const {
		return Count;
	}

	// Adds a number of items to the end of the array and returns a pointer to the first one added.
	// Returns 0 if the array can't contain all the items given.
	FORCEINLINE Type* AddBack(u32 count = 1) {
		u32 total = Items + count;

		if (total >= Capacity) {
			return 0;
		}

		Type* added = Items + Count;
		Count = total;

		return added;
	}

	// Resets the number of elements in the array.
	FORCEINLINE void Clear() {
		Count = 0;
	}

	// Pops an item from the end of the array.
	FORCEINLINE void PopBack() {
		if (Count > 0) {
			--Count;
		}
	}

	// Pushes an item onto the end of the array.
	FORCEINLINE b32 PushBack(Type const& value) {
		if (Count >= Capacity) {
			return false;
		}

		Items[Count++] = value;
		return true;
	}
};
