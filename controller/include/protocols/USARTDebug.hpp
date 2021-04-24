#include "types.hpp"
#include "shared_proto/Debug.hpp"
#include "peripherals/USARTx.hpp"

#pragma once

namespace Protocols::Debug {
  class USARTTransmittingSession : public TransmittingSession {
  public:
    // Creates new USARTTransmittingSession instance.
    [[ maybe_unused ]] USARTTransmittingSession (Peripherals::USARTx &usart) noexcept;

    /// Writes an frame byte without escaping.
    [[ maybe_unused ]] virtual void WriteByteDirect (u8 byte) noexcept;
  protected:
    Peripherals::USARTx &m_USART;
  };
}
