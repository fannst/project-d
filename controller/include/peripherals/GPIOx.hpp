#include "stm32f767xx.h"
#include "types.hpp"

#pragma once

enum class GPIO_Mode {
    Input = 0x0,
    Output = 0x1,
    AF = 0x2,
    Analog = 0x3
};

enum class GPIO_OType {
    PushPull = 0x0,
    OpenDrain = 0x1  
};

enum class GPIO_OSpeed {
    Low = 0x0,
    Medium = 0x1,
    High = 0x2,
    VeryHigh = 0x3
};

enum class GPIO_PUPD {
    None = 0x0,
    PullUp = 0x1,
    PullDown = 0x2
};

namespace Peripherals {
    class GPIOx {
    public:
        /// Sets the mode for the specified GPIO pin.
        [[ maybe_unused ]] void SetMode (u8 pin, GPIO_Mode mode) noexcept;

        /// Sets the speed for specified pin.
        [[ maybe_unused ]] void SetSpeed (u8 pin, GPIO_OSpeed speed) noexcept;
        
        /// Sets the output type for specified pin.
        [[ maybe_unused ]] void SetOutputType (u8 pin, GPIO_OType type) noexcept;
        
        /// Sets the pullup / pulldown for specified pin.
        [[ maybe_unused ]] void SetPUPD (u8 pin, GPIO_PUPD pupd) noexcept;

        /// Sets the AF for specified pin.
        [[ maybe_unused ]] void SetAF (u8 pin, u8 mode) noexcept;

        /// Writes high to ODR.
        inline void WriteHigh (u8 pin) noexcept {
            m_GPIO->ODR |= (0x1 << static_cast<u32>(pin));
        }

        /// Writes low to ODR.
        inline void WriteLow (u8 pin) noexcept {
            m_GPIO->ODR &= ~(0x1 << static_cast<u32>(pin));
        }

        /// Toggles the ODR for specified pin.
        inline void Toggle (u8 pin) noexcept {
            m_GPIO->ODR ^= (0x1 << static_cast<u32>(pin));
        }

        /// Checks if input pin is high.
        inline bool IsHigh (u8 pin) const noexcept {
            return m_GPIO->IDR & (0x1 << static_cast<u32>(pin));
        }

        /// Checks if input pin is low.
        inline bool IsLow (u8 pin) const noexcept {
            return !IsHigh (pin);
        }

        inline GPIO_TypeDef *GetGPIO (void) noexcept
        { return m_GPIO; }
    protected:
        friend class GPIOs;

        /// Creates bew GPIOx instance.
        [[ maybe_unused ]] GPIOx (GPIO_TypeDef *gpio) noexcept;
        ~GPIOx () = default;

        GPIO_TypeDef *m_GPIO;
    };

    class GPIOs {
    public:
        /// Initializes the clocks for GPIO A-F.
        [[ maybe_unused ]] static void Init (void) noexcept;

        static GPIOx A;
        static GPIOx B;
        static GPIOx C;
        static GPIOx D;
        static GPIOx E;
        static GPIOx F;
    protected:
    };
}
