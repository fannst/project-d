#include "stm32f767xx.h"
#include "types.hpp"

#pragma once

namespace Peripherals {
  class TIMx {
  public:
    /// Resets the timer to default config.
    [[ maybe_unused ]] void Reset (void) noexcept;

    /// Sets the PSC register value.
    inline void SetPrescalar (u16 presc) noexcept
    { m_TIM->PSC = presc; }

    /// Sets the ARR register value.
    inline void SetAutoReload (u16 arr) noexcept
    { m_TIM->ARR = arr; }

    /// Sets the counter value.
    inline void SetCounter (u16 cnt) noexcept
    { m_TIM->CNT = cnt; }

    /// Sets the CEN bit in the CR1.
    inline void EnableCounter (void) noexcept
    { m_TIM->CR1 |= TIM_CR1_CEN; }

    /// Gets the actual timer.
    inline TIM_TypeDef *GetTimer (void) noexcept
    { return m_TIM; }
  protected:
    /// Creates new TIMx instance.
    [[ maybe_unused ]] TIMx (TIM_TypeDef *tim) noexcept;
    [[ maybe_unused ]] ~TIMx (void) noexcept = default;

    TIM_TypeDef *m_TIM;
  };
}
