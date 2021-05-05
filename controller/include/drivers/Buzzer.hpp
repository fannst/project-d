#include "types.hpp"
#include "peripherals/GPIOx.hpp"

#pragma once

namespace Drivers {
    class Buzzer {
    public:
        /// Creates new buzzer instance.
        [[ maybe_unused ]] Buzzer (Peripherals::GPIOx &gpio, u8 pin) noexcept;

        /// Initializes the buzzer.
        [[ maybe_unused ]] void Init (void) noexcept;

        /// Performs some buzz.
        [[ maybe_unused ]] void Buzz (u16 delay, u16 pulses) noexcept;
    protected:
        Peripherals::GPIOx &m_GPIO;
        u8 m_Pin;
    };
}
