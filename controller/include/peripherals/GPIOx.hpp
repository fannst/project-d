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

class GPIOx {
public:
    void SetMode (u8 pin, GPIO_Mode mode) noexcept;
    void SetSpeed (u8 pin, GPIO_OSpeed speed) noexcept;
    void SetOutputType (u8 pin, GPIO_OType type) noexcept;
    void SetPUPD (u8 pin, GPIO_PUPD pupd) noexcept;
    void SetAF (u8 pin, u8 mode) noexcept;

    inline void WriteHigh (u8 pin) noexcept {
        m_GPIO->ODR |= (0x1 << static_cast<u32>(pin));
    }

    inline void WriteLow (u8 pin) noexcept {
        m_GPIO->ODR &= ~(0x1 << static_cast<u32>(pin));
    }

    inline void Toggle (u8 pin) noexcept {
        m_GPIO->ODR ^= (0x1 << static_cast<u32>(pin));
    }

    inline bool IsHigh (u8 pin) const noexcept {
        return m_GPIO->IDR & (0x1 << static_cast<u32>(pin));
    }

    inline bool IsLow (u8 pin) const noexcept {
        return !IsHigh (pin);
    }
protected:
    friend class GPIOs;

    GPIOx (GPIO_TypeDef *gpio) noexcept;

    GPIO_TypeDef *m_GPIO;
};

class GPIOs {
public:
    /// Initializes the clocks for GPIO A-F.
    static void Init (void) noexcept;

    static GPIOx A;
    static GPIOx B;
    static GPIOx C;
    static GPIOx D;
    static GPIOx E;
    static GPIOx F;
protected:
};
