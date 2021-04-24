#include "SerialDebug.hpp"

namespace Protocols::Debug {
  ////////////////////////////////////////////////////////////////////
  // ReceivingSerialSession                                         //
  ////////////////////////////////////////////////////////////////////

  /// Gets one of the available frames.
  [[ maybe_unused ]] const frame_t *ReceivingSerialSession::GetFrame (void) {
    // Gets the longest in-buffer frame, pops it off and returns it.
    const frame_t *t = m_Frames.back ();
    m_Frames.pop_back ();
    return t;
  }

  /// Gets called when debug frame received.
  [[ maybe_unused ]] void ReceivingSerialSession::OnDebugFrame (const frame_t *frame) noexcept {
    // Allocates the memory for the copied frame.
    frame_t *copied = reinterpret_cast<frame_t *>(new u8[frame->len]);
    if (copied == nullptr) {
      // TODO: Add error handling.
      return;
    }

    // Copies the frame, and pushes it to the doubly linked-list, so we can
    //  read the debug message later on.
    memcpy (copied, frame, frame->len);
    m_Frames.push_front (copied);
  }
}