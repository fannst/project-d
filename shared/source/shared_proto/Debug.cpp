#include "shared_proto/Debug.hpp"
#include "Checksum.hpp"

namespace Protocols::Debug {
  ////////////////////////////////////////////////////////////////////
  // TransmittingSession                                            //
  ////////////////////////////////////////////////////////////////////


  /// Writes an frame to the debug session.
  [[ maybe_unused ]] void TransmittingSession::WriteFrame (const frame_t *frame) {
    // Sends the start flag.
    WriteByteDirect (static_cast<u8>(Flag::Start));

    // Writes the actual frame, if required bytes will be escaped.
    const u8 *p = reinterpret_cast<const u8 *>(frame);
    for (u16 i = 0; i < frame->len; ++i) {
      WriteByte (p[i]);
    }

    // Sends the end flag.
    WriteByteDirect (static_cast<u8>(Flag::End));
  }

  /// Writes an frame byte, and escapes if required.
  [[ maybe_unused ]] void TransmittingSession::WriteByte (u8 byte) {
    // Checks if the current byte is a flag, if so write an escape byte first.
    if (byte > static_cast<u8>(Flag::__START) && byte < static_cast<u8>(Flag::__END)) {
      WriteByteDirect (static_cast<u8>(Flag::Esc));
    }

    // Writes the actual byte physically.
    WriteByteDirect (byte);
  }

  /// Writes a simple non-payload event.
  [[ maybe_unused ]] void TransmittingSession::WriteSimpleEvent (Event event) noexcept {
    frame_t *frame = reinterpret_cast<frame_t *>(TransmittingSession::WRITE_BUFFER);

    // Sets the frame length, and the simple event.
    frame->len = sizeof (frame_t) + sizeof (packet_t);
    frame->packet.event = static_cast<u32>(event);

    // Signs the frame, and sends it.
    AssignChecksum (frame);
    WriteFrame (frame);
  }

  ////////////////////////////////////////////////////////////////////
  // ReceivingSession                                               //
  ////////////////////////////////////////////////////////////////////

  /// Updates the state machine with the received byte.
  [[ maybe_unused ]] void ReceivingSession::UpdateStateMachine (u8 byte) noexcept {
    if (m_EscapeNext) {
      switch (byte) {
        // START flag received.
        case static_cast<u8>(Flag::Start):
          m_TempBufferLevel = 0;
          m_Receiving = true;
          return;
        // END flag received.
        case static_cast<u8>(Flag::End):
          // Checks if we're receiving in the first place, if not just
          //  ignore current flag.
          if (m_Receiving) {
            OnDebugFrame (reinterpret_cast<const frame_t *>(m_TempBuffer));
            m_Receiving = false;
          }
          return;
        // ESC flag received.
        case static_cast<u8>(Flag::Esc):
          m_EscapeNext = true;
          return;
        // Normal byte received.
        default:
          break;
      }
    } else {
      m_EscapeNext = false;
    }

    m_TempBuffer[m_TempBufferLevel++] = byte;
  }

  /// Assigns an checksum to a debug frame.
  [[ maybe_unused ]] void AssignChecksum (frame_t *frame) noexcept {
		frame->cs = 0x0000;
		frame->cs = Checksums::__oc16_do (reinterpret_cast<const uint8_t *>(frame), frame->len);
  }

  /// Validates an checksum.
  [[ maybe_unused ]] bool ValidateChecksum (frame_t *frame) noexcept {
    return Checksums::__oc16_do (reinterpret_cast<const uint8_t *>(frame), frame->len) == 0xFFFF;
  }
}
