#include "datatypes/CriticalRingBuffer.hpp"

namespace Datatypes {
  ////////////////////////////////////////////////////////////////////
  // CriticalRingBuffer                                             //
  ////////////////////////////////////////////////////////////////////

  /// Creates new CriticalRingBuffer instance.
  [[ maybe_unused ]] CriticalRingBuffer::CriticalRingBuffer (u32 size, u32 cap, u8 *buf) noexcept:
    m_Size (size),
    m_Capacity (cap),
    m_Read (),
    m_Write (0),
    m_Buffer (buf)
  {}

  /// Pushes a byte into the ring buffer.
  [[ maybe_unused ]] CriticalRingBufferError CriticalRingBuffer::Push (u8 byte) noexcept {
    Lock ();

    if ((m_Size + 1) > m_Capacity) {
      return CriticalRingBufferError::Overflow;
    }

    m_Buffer[m_Write] = byte;
    m_Write = (m_Write + 1) % m_Capacity;

    ++m_Size;

    Unlock ();
    return CriticalRingBufferError::OK;
  }

  /// Pushes N bytes onto the ring buffer.
  [[ maybe_unused ]] CriticalRingBufferError CriticalRingBuffer::PushMany (const u8 *bytes, u32 n) noexcept {
    if ((m_Size + n) > m_Capacity) {
      return CriticalRingBufferError::Overflow;
    }
    
    for (u32 i = 0; i < n; ++i) {
      if (Push (bytes[i]) == CriticalRingBufferError::Overflow) {
        return CriticalRingBufferError::Overflow;
      }
    }

    return CriticalRingBufferError::OK;
  }

  /// Pops a byte from the ring buffer.
  [[ maybe_unused ]] CriticalRingBufferError CriticalRingBuffer::Pop (u8 *byte) noexcept {
    Lock ();
    
    if (m_Size == 0) {
      return CriticalRingBufferError::Underflow;
    }

    *byte = m_Buffer[m_Read];
    m_Read = (m_Read + 1) % m_Capacity;

    --m_Size;

    Unlock ();
    return CriticalRingBufferError::OK;
  }

  /// Pops many bytes off the ring buffer.
  [[ maybe_unused ]] CriticalRingBufferError CriticalRingBuffer::PopMany (u8 *bytes, u32 n) noexcept {
    if (n > m_Size) {
      return CriticalRingBufferError::Underflow;
    }

    for (u32 i = 0; i < n; ++i) {
      if (Pop (&bytes[i]) == CriticalRingBufferError::Underflow) {
        return CriticalRingBufferError::Underflow;
      }
    }

    return CriticalRingBufferError::OK;
  }

  ////////////////////////////////////////////////////////////////////
  // TempRead_CriticalRingBuffer                                    //
  ////////////////////////////////////////////////////////////////////

  /// Creates new TempRead_CriticalRingBuffer instance.
  [[ maybe_unused ]] TempRead_CriticalRingBuffer::TempRead_CriticalRingBuffer (u32 size, u32 cap, u8 *buf) noexcept:
    CriticalRingBuffer::CriticalRingBuffer (size, cap, buf),
    m_TempRead (0)
  {}

  /// Pops a byte from the ring buffer.
  [[ maybe_unused ]] CriticalRingBufferError TempRead_CriticalRingBuffer::TempPop (u8 *byte) noexcept {
    Lock ();
    
    if (m_TempRead == m_Write) {
      return CriticalRingBufferError::Underflow;
    }

    *byte = m_Buffer[m_TempRead];
    m_TempRead = (m_TempRead + 1) % m_Capacity;

    Unlock ();
    return CriticalRingBufferError::OK;
  }

  /// Pops many bytes off the ring buffer.
  [[ maybe_unused ]] CriticalRingBufferError TempRead_CriticalRingBuffer::TempPopMany (u8 *bytes, u32 n) noexcept {
    for (u32 i = 0; i < n; ++i) {
      if (Pop (&bytes[i]) == CriticalRingBufferError::Underflow) {
        return CriticalRingBufferError::Underflow;
      }
    }

    return CriticalRingBufferError::OK;
  }
}
