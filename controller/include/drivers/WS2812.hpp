#include "stm32f767xx.h"
#include "types.hpp"
#include "peripherals/GPIOx.hpp"

#pragma once

#ifndef WS2812_LED_COUNT
#define WS2812_LED_COUNT 8UL
#endif

namespace Drivers {
    class WS2812 {
    public:
        /// Initializes the WS2812 Driver.
        [[ maybe_unused ]] void Init (void) noexcept;

        /// Sends the RGB burst.
        [[ maybe_unused ]] void SendBurst (void) noexcept;

        /// Sets the color of an specific LED.
        [[ maybe_unused ]] void SetColor (u16 led, u8 r, u8 g, u8 b, u8 w) noexcept;

        /// Swaps the read & write buffers.
        [[ maybe_unused ]] void SwapBuffers (void) noexcept;

        /// Clears all the colors.
        [[ maybe_unused ]] void ClearColors (void) noexcept;

        /// Gets the write buffer.
        u16 *GetWriteBuffer (void) noexcept;

        static inline WS2812 &GetInstance (void) noexcept
        { return INSTANCE; }
    protected:
        u16 *m_CurrentBuffer;
        u16 m_BufferA[WS2812_LED_COUNT * 32UL];
        u16 m_BufferB[WS2812_LED_COUNT * 32UL];

        [[ maybe_unused ]] WS2812 (void) noexcept = default;
        [[ maybe_unused ]] ~WS2812 (void) noexcept = default;

        static WS2812 INSTANCE;
    };
}
