#include "drivers/Buzzer.hpp"
#include "Delay.hpp"

namespace Drivers {
    /// Creates new buzzer instance.
    [[ maybe_unused ]] Buzzer::Buzzer (Peripherals::GPIOx &gpio, u8 pin) noexcept:
        m_GPIO (gpio), m_Pin (pin)
    {}

    /// Initializes the buzzer.
    [[ maybe_unused ]] void Buzzer::Init (void) noexcept {
        m_GPIO.SetMode (m_Pin, GPIO_Mode::Output);
        m_GPIO.SetSpeed (m_Pin, GPIO_OSpeed::VeryHigh);
    }

    /// Performs some buzz.
    [[ maybe_unused ]] void Buzzer::Buzz (u16 delay, u16 pulses) noexcept {
        while (pulses-- > 0) {
            m_GPIO.WriteHigh (m_Pin);
            Delay::Us (delay);
            m_GPIO.WriteLow (m_Pin);
            Delay::Us (delay);
        }
    }
}
