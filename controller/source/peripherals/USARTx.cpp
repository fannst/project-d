#include "peripherals/USARTx.hpp"

#include "SysClock.hpp"

namespace Peripherals {
  /// Creates new USARTx instance.
  [[ maybe_unused ]] USARTx::USARTx (USART_TypeDef *usart, u64 busFreq) noexcept:
    m_USART (usart),
    m_BusFreq (busFreq)
  {}

  /// Resets the USART peripheral to the default configuration.
  [[ maybe_unused ]] void USARTx::Reset (void) noexcept {
    // Sets CR1, CR2, CR3 and BRR to 0.
    volatile_memset (&m_USART->CR1, 0, sizeof (u32) * 4);
  }

  /// Calculates and sets the baud rate for the USART peripheral.
  [[ maybe_unused ]] void USARTx::SetBaud (u64 baud) noexcept {
    m_USART->BRR = static_cast<u32>(((2 * m_BusFreq) + baud) / (2 * baud));
  }

  /// Writes N bytes to the USART peripheral.
  [[ maybe_unused ]] void USARTx::WriteBytes (const u8 *bytes, u32 n) noexcept {
    while (n-- > 0) {
      USARTx::WriteSafe (*bytes++);
    }
  }

  /// Writes an byte and waits for the TXE flag to be cleared.
  [[ maybe_unused ]] void USARTx::WriteSafe (u8 byte) noexcept {
    m_USART->TDR = static_cast<u32>(byte);
    while (!USARTx::Writable ());
  }

  /// Writes an byte and does not wait for TXE flag.
  [[ maybe_unused ]] void USARTx::WriteDangerous (u8 byte) noexcept {
    m_USART->TDR = static_cast<u32>(byte);
  }

  /// Reads an byte and waits for the RXNE flag first.
  [[ maybe_unused ]] u8 USARTx::ReadSafe (void) noexcept {
    while (!USARTx::Readable ());
    return static_cast<u8>(m_USART->RDR);
  }

  /// Reads an byte even if there is no data available.
  [[ maybe_unused ]] u8 USARTx::ReadDangerous (void) noexcept {
    return static_cast<u8>(m_USART->RDR);
  }

  /// Initializes the clock sources for the USARTs.
  [[ maybe_unused ]] void USARTs::Init (void) noexcept {
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
  }

  USARTx USARTs::I1 (USART1, MHZ(SYSCLOCK_APB2_PERIPHERALS));
  USARTx USARTs::I2 (USART2, MHZ(SYSCLOCK_APB1_PERIPHERALS));
}
