#include "types.hpp"

#pragma once

namespace Protocols::Debug {
  enum class Flag {
    __START = 0x00,
    Start,
    End,
    Esc,
    __END
  };

  enum class Event {
    StringMessage = 0,          // Null-Terminated string
    InitializationDone
  };

  typedef struct __attribute__ (( packed )) {
    u32         event;
    u8          payload[0];
  } packet_t;

  typedef struct __attribute__ (( packed )) {
    u16         len;
    u16         cs;
    packet_t    packet;
  } frame_t;

  ////////////////////////////////////////////////////////////////////
  // TransmittingSession                                            //
  ////////////////////////////////////////////////////////////////////

  class TransmittingSession {
  public:
    /// Writes an frame to the debug session.
    [[ maybe_unused ]] void WriteFrame (const frame_t *frame);

    /// Writes an frame byte, and escapes if required.
    [[ maybe_unused ]] void WriteByte (u8 byte);

    /// Writes a simple non-payload event.
    [[ maybe_unused ]] void WriteSimpleEvent (Event event) noexcept;

    /// Writes an frame byte without escaping.
    virtual void WriteByteDirect (u8 byte) = 0;

    /// Gets the default write buffer for the debug session.
    inline uint8_t *GetWriteBuffer (void) noexcept
    { return TransmittingSession::WRITE_BUFFER; }
  protected:
    uint8_t WRITE_BUFFER[128];
  };

  ////////////////////////////////////////////////////////////////////
  // ReceivingSession                                               //
  ////////////////////////////////////////////////////////////////////

  class ReceivingSession {
  public:
    /// Gets called when debug frame received.
    virtual void OnDebugFrame (const frame_t *frame) noexcept = 0;

    /// Updates the state machine with the received byte.
    [[ maybe_unused ]] void UpdateStateMachine (u8 byte) noexcept;
  protected:
    /* Temp Buffer */
    uint8_t   m_TempBuffer[128];
    u16       m_TempBufferLevel;
    /* Single-Bit state fields */
    unsigned  m_EscapeNext : 1;
    unsigned  m_Receiving  : 1;
    unsigned  _            : 6;
  };

  /// Assigns an checksum to a debug frame.
  [[ maybe_unused ]] void AssignChecksum (frame_t *frame) noexcept;

  /// Validates an checksum.
  [[ maybe_unused ]] bool ValidateChecksum (frame_t *frame) noexcept;
};
