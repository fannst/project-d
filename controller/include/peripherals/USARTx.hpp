#include <string.h>

#include "stm32f767xx.h"
#include "helpers.hpp"
#include "types.hpp"

#pragma once

namespace Peripherals {
  class USARTx {
  public:
    /// Resets the USART peripheral to the default configuration.
    [[ maybe_unused ]] void Reset (void) noexcept;

    /// Calculates and sets the baud rate for the USART peripheral.
    [[ maybe_unused ]] void SetBaud (u64 baud) noexcept;

    /// Writes N bytes to the USART peripheral.
    [[ maybe_unused ]] void WriteBytes (const u8 *bytes, u32 n) noexcept;

    /// Writes an byte and waits for the TXE flag to be cleared.
    [[ maybe_unused ]] void WriteSafe (u8 byte) noexcept;

    /// Writes an byte and does not wait for TXE flag.
    [[ maybe_unused ]] void WriteDangerous (u8 byte) noexcept;

    /// Reads an byte and waits for the RXNE flag first.
    [[ maybe_unused ]] u8 ReadSafe (void) noexcept;

    /// Reads an byte even if there is no data available.
    [[ maybe_unused ]] u8 ReadDangerous (void) noexcept;

    /// Enables the receiver for the USART.
    inline void EnableReceiver (void) noexcept
    { m_USART->CR1 |= USART_CR1_RE; }

    /// Enables the transmitter for the USART.
    inline void EnableTransmitter (void) noexcept
    { m_USART->CR1 |= USART_CR1_TE; }

    /// Enables the USART peripheral itself.
    inline void Enable (void) noexcept
    { m_USART->CR1 |= USART_CR1_UE; } 

    /// Enables Receiver, Transmitter and USART peripheral.
    inline void EnableAll (void) noexcept
    { m_USART->CR1 |= (USART_CR1_RE | USART_CR1_TE | USART_CR1_UE); }

    /// Checks if new data can be written to TDR.
    inline bool Writable (void) const noexcept
    { return m_USART->ISR & USART_ISR_TXE; }

    /// Checks if data can be read from RDR.
    inline bool Readable (void) const noexcept
    { return m_USART->ISR & USART_ISR_RXNE; }
  protected:
    /// Creates new USARTx instance.
    [[ maybe_unused ]] USARTx (USART_TypeDef *usart, u64 busFreq) noexcept;
    ~USARTx () = default;

    friend class USARTs;

    USART_TypeDef *m_USART;
    u64 m_BusFreq;
  };

  class USARTs {
  public:
    /// Initializes the clock sources for the USARTs.
    [[ maybe_unused ]] static void Init (void) noexcept;

    static USARTx I1;
    static USARTx I2;
  protected:
  };
}
