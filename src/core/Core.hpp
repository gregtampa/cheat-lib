//=============================================================================
// Core template library.
//=============================================================================
#pragma once
#include "Types.hpp"

namespace Core {

//=============================================================================
// Utilities.
//=============================================================================

// Dereference support.
template<typename>
struct Dereference;

template <typename TypePtr>
struct Dereference<TypePtr*> {
	typedef typename TypePtr Type;
};

// Swaps two items.
template <typename Type>
FORCEINLINE void Swap(Type& a, Type& b) {
	Type c = a;
	a = b;
	b = c;
}

//=============================================================================
// Algorithms.
//=============================================================================

// Returns true if the range[first, last) contains value, false otherwise.
template <typename Iterator, typename Type>
inline b32 Contains(Iterator first, Iterator last, const Type& value) {
	while (first != last) {
		if (*first++ == value) {
			return true;
		}
	}

	return false;
}

// Returns true if the range[first, last) contains value, false otherwise.
template <typename Iterator, typename Type, typename Predicate>
inline b32 ContainsEx(Iterator first, Iterator last, const Type& value, Predicate predicate) {
	while (first != last) {
		if (predicate(*first++, value)) {
			return true;
		}
	}

	return false;
}

// Returns iterator to first element in range[first, last) that's value. If no element is found, returns last.
template <typename Iterator, typename Type>
inline Iterator Find(Iterator first, Iterator last, const Type& value) {
	while ((first != last) && !(*first == value)) {
		++first;
	}

	return first;
}

// Returns iterator to first element in range[first, last) that's value. If no element is found, returns last.
template <typename Iterator, typename Type, typename Predicate>
inline Iterator FindEx(Iterator first, Iterator last, const Type& value, Predicate predicate) {
	while ((first != last) && !predicate(*first, value)) {
		++first;
	}

	return first;
}

// Reverses the values within the range [first, last)
template <typename Iterator>
inline void Reverse(Iterator first, Iterator last) {
	if (first != last) {
		for (; first < --last; ++first) {
			Swap(*first, *last);
		}
	}
}

//=============================================================================
// Functional.
//=============================================================================

// Returns the < function for the given type.
template <typename T>
struct Less {
	constexpr b32 operator()(const T& a, const T& b) const {
		return a < b;
	}
};

// Returns the > function for the given type.
template <typename T>
struct Greater {
	constexpr b32 operator()(const T& a, const T& b) const {
		return a > b;
	}
};

//=============================================================================
// Insertion sorts.
//=============================================================================

// Sorts the items between [first, last) using an insertion sort.
template <typename Iterator>
void InsertionSort(Iterator first, Iterator last) {
	typedef typename Dereference<Iterator>::Type Type;

	if (first != last) {
		Iterator iCurrent, iNext, iSorted = first;

		for (++iSorted; iSorted != last; ++iSorted) {
			const Type temp = *iSorted;

			iNext = iCurrent = iSorted;
			for (--iCurrent; (iNext != first) && (temp < *iCurrent); --iNext, --iCurrent) {
				*iNext = *iCurrent;
			}

			*iNext = temp;
		}
	}
}

// Sorts the items between [first, last) using an insertion sort with a custom compare function.
template <typename Iterator, typename StrictWeakOrdering>
void InsertionSortEx(Iterator first, Iterator last, StrictWeakOrdering compare) {
	typedef typename Dereference<Iterator>::Type Type;

	if (first != last) {
		Iterator iCurrent, iNext, iSorted = first;

		for (++iSorted; iSorted != last; ++iSorted) {
			const Type temp = *iSorted;

			iNext = iCurrent = iSorted;

			for (--iCurrent; (iNext != first) && compare(temp, *iCurrent); --iNext, --iCurrent) {
				*iNext = *iCurrent;
			}

			*iNext = temp;
		}
	}
}

}
