#include "stm32f767xx.h"
#include "types.hpp"

#pragma once

namespace Drivers {
  class ServoCluster {
  public:
    /// Creates new servo cluster instance.
    [[ maybe_unused ]] ServoCluster (TIM_TypeDef *tim, u16 arr, u16 psc, float min, float max, float degrees) noexcept;

    /// Initializes the servo cluster.
    [[ maybe_unused ]] void Init (void) noexcept;

    /// Moves a servo.
    [[ maybe_unused ]] void Move (u8 n, float deg) noexcept;
  protected:
    TIM_TypeDef *m_TIM;
    u16 m_Arr, m_Psc;
    float m_Min, m_Max, m_Degrees;
  };
}
