#include "peripherals/TIMx.hpp"

namespace Peripherals {
  /// Resets the timer to default config.
  [[ maybe_unused ]] void TIMx::Reset (void) noexcept {
    m_TIM->CNT = 0;
  }

  /// Creates new TIMx instance.
  [[ maybe_unused ]] TIMx::TIMx (TIM_TypeDef *tim) noexcept:
    m_TIM (tim)
  {}
}
