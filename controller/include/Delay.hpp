#include "types.hpp"
#include "SysClock.hpp"

#pragma once

class Delay {
public:	
	/// Initializes the delay timer.
	static void Init (void) noexcept;

	/// Delays N US.
	static void Us (u16 n) noexcept;

	/// Delays N MS.
	static void Ms (u16 n) noexcept;

	/// Delays N S.
	static void S (u16 n) noexcept;
};
