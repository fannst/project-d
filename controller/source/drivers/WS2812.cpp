#include "drivers/WS2812.hpp"
#include "Delay.hpp"

namespace Drivers {
    WS2812 WS2812::INSTANCE;

    /// Initializes the WS2812 Driver.
    [[ maybe_unused ]] void WS2812::Init (void) noexcept {
        //
        // Configures the DMA Stream
        //

        // Sets the initial buffer to BufferA.
        m_CurrentBuffer = m_BufferA;

        // Sets the control register values.
        DMA2_Stream5->CR = ((6 << DMA_SxCR_CHSEL_Pos)       // 2: TIM1_CH1
            | DMA_SxCR_MINC                                 // Increment Memory
            | (0b01 << DMA_SxCR_MSIZE_Pos)                  // Memory Size 16-bit
            | (0b01 << DMA_SxCR_PSIZE_Pos)                  // Periph Size 16-bit
            | (0b01 << DMA_SxCR_DIR_Pos)                    // Memory To-Peripheral
        );

        // Sets the peripheral memory address.
        DMA2_Stream5->PAR = reinterpret_cast<uintptr_t>(&TIM1->CCR1);

        //
        // Configures the timer.
        //

        // Enables the TIM1 in the RCC.
        RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

        // Sets the prescalar and auto-reload register.
        TIM1->SR = 0xFFFFFFFF;
        TIM1->PSC = 11;         // 216,000,000 ÷ 11 = 20,000,000
        TIM1->ARR = 25;         // 1.25us, (20 * 5) + (5 * 5)

        // Configures the capture-control register.
        TIM1->CCR1 = 26;        // Always-High

        // Enables the main output.
        TIM1->BDTR = TIM_BDTR_MOE;

        // Enables DMA for update event.
        TIM1->DIER |= TIM_DIER_UDE;

        // Enables capture-compare 1.
        TIM1->CCER |= TIM_CCER_CC1E;

        // Sets PWM mode to 1, and enables the auto-reload preload register.
        TIM1->CCMR1 = ((0b0110 << TIM_CCMR1_OC1M_Pos)
            | TIM_CCMR1_OC1PE);

        // Sets the ARPE bit.
        TIM1->CR1 |= TIM_CR1_ARPE;
        TIM1->CR2 = TIM_CR2_CCDS;

        // Generates the update event.
        TIM1->EGR |= TIM_EGR_UG;

        // Enables the timer.
        TIM1->CR1 |= TIM_CR1_CEN;

        //
        // Configures the GPIO.
        //

        Peripherals::GPIOs::A.SetMode (8, GPIO_Mode::AF);
        Peripherals::GPIOs::A.SetSpeed (8, GPIO_OSpeed::VeryHigh);
        Peripherals::GPIOs::A.SetAF (8, 1);
    }

    /// Swaps the read & write buffers.
    [[ maybe_unused ]] void WS2812::SwapBuffers (void) noexcept {
        if (m_BufferA == m_CurrentBuffer) {
            m_CurrentBuffer = m_BufferB;
        } else if (m_BufferB == m_CurrentBuffer) {
            m_CurrentBuffer = m_BufferA;
        } 
    }
    /// Gets the write buffer.
    u16 *WS2812::GetWriteBuffer (void) noexcept {
        if (m_BufferA == m_CurrentBuffer) {
            return m_BufferB;
        } else if (m_BufferB == m_CurrentBuffer) {
            return m_BufferA;
        } 
    }

    /// Clears all the colors.
    [[ maybe_unused ]] void WS2812::ClearColors (void) noexcept {
        for (u16 i = 0; i < static_cast<u16>(WS2812_LED_COUNT); ++i) {
            SetColor (i, 0, 0, 0, 0);
        }
    }

    /// Sends the RGB burst.
    [[ maybe_unused ]] void WS2812::SendBurst (void) noexcept {
        // Waits for previous burst to finish.
        while (DMA2_Stream5->CR & DMA_SxCR_EN);

        //
        // Sends reset.
        //

        // Sets duty cycle to 0 for ~70 us, after which
        //  we set it to 100 again.
        TIM1->CCR1 = 0;
        Delay::Us (80);
        TIM1->CCR1 = 26;

        //
        // Starts burst transfer.
        //

        // Sets the memory address to the first of the DMA buffer,
        //  and enables the DMA stream.
        DMA2->HIFCR |= DMA_HIFCR_CTCIF5 | DMA_HIFCR_CHTIF5 | DMA_HIFCR_CTEIF5 | DMA_HIFCR_CDMEIF5;
        DMA2_Stream5->M0AR = reinterpret_cast<uintptr_t>(m_CurrentBuffer);
        DMA2_Stream5->NDTR = (WS2812_LED_COUNT * 32);
        DMA2_Stream5->CR |= DMA_SxCR_EN;
    }

    /// Sets the color of an specific LED.
    [[ maybe_unused ]] void WS2812::SetColor (u16 led, u8 r, u8 g, u8 b, u8 w) noexcept {
        #define WS2812_SET_COLOR__BIT_1     16
        #define WS2812_SET_COLOR__BIT_0     8
        
        u16 *addr = &GetWriteBuffer()[led * 32];

        // Calculates G.
        for (u8 i = 0; i < 8; ++i) {
            *addr = (g & 0x80) ? WS2812_SET_COLOR__BIT_1 : WS2812_SET_COLOR__BIT_0;
            ++addr;
            g <<= 1;
        }

        // Calculates R.
        for (u8 i = 0; i < 8; ++i) {
            *addr = (r & 0x80) ? WS2812_SET_COLOR__BIT_1 : WS2812_SET_COLOR__BIT_0;
            ++addr;
            r <<= 1;
        }

        // Calculates B.
        for (u8 i = 0; i < 8; ++i) {
            *addr = (b & 0x80) ? WS2812_SET_COLOR__BIT_1 : WS2812_SET_COLOR__BIT_0;
            ++addr;
            b <<= 1;
        }

        // Calculates W.
        for (u8 i = 0; i < 8; ++i) {
            *addr = (w & 0x80) ? WS2812_SET_COLOR__BIT_1 : WS2812_SET_COLOR__BIT_0;
            ++addr;
            w <<= 1;
        }

        #undef  WS2812_SET_COLOR__BIT_0
        #undef  WS2812_SET_COLOR__BIT_1
    }
}
