#include "drivers/ServoCluster.hpp"

namespace Drivers {
  /// Creates new servo cluster instance.
  [[ maybe_unused ]] ServoCluster::ServoCluster (TIM_TypeDef *tim, u16 arr, u16 psc, float min, float max, float degrees) noexcept:
    m_TIM (tim), m_Arr (arr), m_Psc (psc), m_Min (min), m_Max (max), m_Degrees (degrees)
  {}

  /// Initializes the servo cluster.
  [[ maybe_unused ]] void ServoCluster::Init (void) noexcept {
    // Sets the prescalar and the auto reload register.
    m_TIM->PSC = static_cast<u32>(m_Psc);
    m_TIM->ARR = static_cast<u32>(m_Arr);

    // Sets the CCRx register values.
    m_TIM->CCR1 = m_TIM->CCR2 = m_TIM->CCR3 = m_TIM->CCR4 = static_cast<u32>(
      (((float) m_Arr) / 20.f) * m_Min
    ); 

    // Enables the Capture/Compare thingy, with active-high.
    m_TIM->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;

    // Sets the PWM mode to 1, and enables the auto-reload preload register.
    m_TIM->CCMR1 = ((0b110 << TIM_CCMR1_OC1M_Pos)
      | (0b110 << TIM_CCMR1_OC2M_Pos)
      | TIM_CCMR1_OC1PE
      | TIM_CCMR1_OC2PE);
    m_TIM->CCMR2 |= ((0b110 << TIM_CCMR2_OC3M_Pos)
      | (0b110 << TIM_CCMR2_OC4M_Pos)
      | TIM_CCMR2_OC3PE
      | TIM_CCMR2_OC4PE);

    // Sets the ARPE bit.
    m_TIM->CR1 |= TIM_CR1_ARPE;

    // Generates the update event.
    m_TIM->EGR |= TIM_EGR_UG;

    // Enables the timer.
    m_TIM->CR1 |= TIM_CR1_CEN;
  }

  /// Moves a servo.
  [[ maybe_unused ]] void ServoCluster::Move (u8 n, float deg) noexcept {
    float v = m_Min + ((m_Max - m_Min) * (deg / m_Degrees));
    (&m_TIM->CCR1)[n] = (uint32_t) ((((float) m_Arr) / 20.f) * v);
  }
}
