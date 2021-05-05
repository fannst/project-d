#include "Delay.hpp"

/// Initializes the delay timer.
void Delay::Init (void) noexcept {
	DWT->LAR = 0xC5ACCE55;
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/// Delays N US.
void Delay::Us (u16 n) noexcept {
	    uint32_t startTick  = DWT->CYCCNT,
             targetTick = DWT->CYCCNT + n * (216000000/1000000);

    // Must check if target tick is out of bounds and overflowed
    if (targetTick > startTick) {
        // Not overflowed
        while (DWT->CYCCNT < targetTick);
    } else {
        // Overflowed
        while (DWT->CYCCNT > startTick || DWT->CYCCNT < targetTick);
    }
}

/// Delays N MS.
void Delay::Ms (u16 n) noexcept {
	for (; n > 0; --n) {
		Delay::Us(1000);
	}
}

/// Delays N S.
void Delay::S (u16 n) noexcept {
	for (; n > 0; --n) {
		Delay::Ms(1000);
	}
}
