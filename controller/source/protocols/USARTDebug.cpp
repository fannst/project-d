#include "protocols/USARTDebug.hpp"

namespace Protocols::Debug {
    // Creates new USARTTransmittingSession instance.
    [[ maybe_unused ]] USARTTransmittingSession::USARTTransmittingSession (Peripherals::USARTx &usart) noexcept:
      m_USART (usart)
    {}


    /// Writes an frame byte without escaping.
    [[ maybe_unused ]] void USARTTransmittingSession::WriteByteDirect (u8 byte) noexcept {
      m_USART.WriteSafe (byte);
    }
}
