#include <list>
#include <fstream>

#include <string.h>

#include "types.hpp"
#include "shared_proto/Debug.hpp"

#pragma once

namespace Protocols::Debug {
  class ReceivingSerialSession : public ReceivingSession {
  public:
    /// Gets called when debug frame received.
    [[ maybe_unused ]] virtual void OnDebugFrame (const frame_t *frame) noexcept;

    /// Gets one of the available frames.
    [[ maybe_unused ]] const frame_t *GetFrame (void);

    /// Checks if an frame is available.
    inline bool HasFrame (void) noexcept
    { return !m_Frames.empty (); }

    /// Gets the currently available frames.
    inline std::list<const frame_t *> GetFrames (void) noexcept
    { return m_Frames; }
  protected:
    std::list<const frame_t *> m_Frames;
    i32 m_FD:
  };
};