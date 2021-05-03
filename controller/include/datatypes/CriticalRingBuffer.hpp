#include "stm32f767xx.h"
#include "types.hpp"

#pragma once

namespace Datatypes {
  enum class CriticalRingBufferError {
    Overflow, Underflow, OK
  };

  ////////////////////////////////////////////////////////////////////
  // CriticalRingBuffer                                             //
  ////////////////////////////////////////////////////////////////////

  class CriticalRingBuffer {
  public:
    /// Creates new CriticalRingBuffer instance.
    [[ maybe_unused ]] CriticalRingBuffer (u32 size, u32 cap, u8 *buf) noexcept;

    /// Pushes a byte into the ring buffer.
    [[ maybe_unused ]] CriticalRingBufferError Push (u8 byte) noexcept;

    /// Pushes N bytes onto the ring buffer.
    [[ maybe_unused ]] CriticalRingBufferError PushMany (const u8 *bytes, u32 n) noexcept;

    /// Pops a byte from the ring buffer.
    [[ maybe_unused ]] CriticalRingBufferError Pop (u8 *byte) noexcept;

    /// Pops many bytes off the ring buffer.
    [[ maybe_unused ]] CriticalRingBufferError PopMany (u8 *bytes, u32 n) noexcept;

    /// Checks if the buffer is empty.
    inline bool IsEmpty (void) noexcept
    { return m_Size == 0; }

    /// Checks if the buffer is full.
    inline bool IsFull (void) noexcept
    { return !IsEmpty (); }
  protected:
    /// Locks interrupts while accessing the ring buffer.
    inline void Lock (void) noexcept
    { __disable_irq (); }

    /// Unlocks interrupts while accessing the ring buffer.
    inline void Unlock (void) noexcept
    { __enable_irq (); }

    u32 m_Size, m_Capacity, m_Read, m_Write;
    u8 *m_Buffer;
  };

  ////////////////////////////////////////////////////////////////////
  // TempRead_CriticalRingBuffer                                    //
  ////////////////////////////////////////////////////////////////////

  class TempRead_CriticalRingBuffer : public CriticalRingBuffer {
  public:
    /// Creates new TempRead_CriticalRingBuffer instance.
    [[ maybe_unused ]] TempRead_CriticalRingBuffer (u32 size, u32 cap, u8 *buf) noexcept;

    /// Pops a byte from the ring buffer.
    [[ maybe_unused ]] CriticalRingBufferError TempPop (u8 *byte) noexcept;

    /// Pops many bytes off the ring buffer.
    [[ maybe_unused ]] CriticalRingBufferError TempPopMany (u8 *bytes, u32 n) noexcept;

    /// Resets the temp read to the read pointer.
    inline void ResetTempRead (void) noexcept
    { m_TempRead = m_Read; }
  protected:
    u32 m_TempRead;
  };
}
