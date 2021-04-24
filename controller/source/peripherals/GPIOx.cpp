#include "peripherals/GPIOx.hpp"

namespace Peripherals {
    /// Creates bew GPIOx instance.
    [[ maybe_unused ]] GPIOx::GPIOx (GPIO_TypeDef *gpio) noexcept:
        m_GPIO (gpio)
    {}

    /// Sets the mode for the specified GPIO pin.
    [[ maybe_unused ]] void GPIOx::SetMode (u8 pin, GPIO_Mode mode) noexcept {
        m_GPIO->MODER &= (0x3 << (static_cast<u32>(pin) * 2));
        m_GPIO->MODER |= (static_cast<u32>(mode) << (static_cast<u32>(pin) * 2));
    }

    /// Sets the speed for specified pin.
    [[ maybe_unused ]] void GPIOx::SetSpeed (u8 pin, GPIO_OSpeed speed) noexcept {
        m_GPIO->OSPEEDR &= (0x3 << (static_cast<u32>(pin) * 2));
        m_GPIO->OSPEEDR |= (static_cast<u32>(speed) << (static_cast<u32>(pin) * 2));
    }

    /// Sets the output type for specified pin.
    [[ maybe_unused ]] void GPIOx::SetOutputType (u8 pin, GPIO_OType type) noexcept {
        m_GPIO->OSPEEDR &= (0x3 << (static_cast<u32>(pin)));
        m_GPIO->OSPEEDR |= (static_cast<u32>(type) << static_cast<u32>(pin));
    }

    /// Sets the pullup / pulldown for specified pin.
    [[ maybe_unused ]] void GPIOx::SetPUPD (u8 pin, GPIO_PUPD pupd) noexcept {
        m_GPIO->PUPDR &= (0x3 << (static_cast<u32>(pin) * 2));
        m_GPIO->PUPDR |= (static_cast<u32>(pupd) << (static_cast<u32>(pin) * 2));
    }

    /// Sets the AF for specified pin.
    [[ maybe_unused ]] void GPIOx::SetAF (u8 pin, u8 mode) noexcept {
        volatile u32 *reg = (pin <= 7) ? &m_GPIO->AFR[0] : &m_GPIO->AFR[1];
        *reg &= ~(0xF << (static_cast<u32>(pin) * 4));
        *reg |= ((static_cast<u32>(mode) & 0xF) << (static_cast<u32>(pin) * 4));
    }

    /// Initializes the clocks for GPIO A-F.
    [[ maybe_unused ]] void GPIOs::Init (void) noexcept {
        RCC->AHB1ENR |= (
            RCC_AHB1ENR_GPIOAEN_Msk | 
            RCC_AHB1ENR_GPIOBEN_Msk | 
            RCC_AHB1ENR_GPIOCEN_Msk | 
            RCC_AHB1ENR_GPIODEN_Msk | 
            RCC_AHB1ENR_GPIOAEN_Msk | 
            RCC_AHB1ENR_GPIOFEN_Msk
        );
    }

    GPIOx GPIOs::A (GPIOA);
    GPIOx GPIOs::B (GPIOB);
    GPIOx GPIOs::C (GPIOC);
    GPIOx GPIOs::D (GPIOD);
    GPIOx GPIOs::E (GPIOE);
    GPIOx GPIOs::F (GPIOF);
}