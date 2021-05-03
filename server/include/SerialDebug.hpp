#include <list>
#include <fstream>
#include <mutex>

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>

#include "types.hpp"
#include "shared_proto/Debug.hpp"

#pragma once

namespace Protocols::Debug {

  ////////////////////////////////////////////////////////////////////
  // ReceivingSerialSession                                         //
  ////////////////////////////////////////////////////////////////////

  class ReceivingSerialSession : public ReceivingSession {
  public:
    /// Gets called when debug frame received.
    [[ maybe_unused ]] virtual void OnDebugFrame (const frame_t *frame) noexcept;

    /// Opens the FD to specified path with baud rate.
    [[ maybe_unused ]] void Open (const char *path, u64 baud);

    /// Gets one of the available frames.
    [[ maybe_unused ]] const frame_t *GetFrame (void);

    /// Checks if an frame is available.
    [[ maybe_unused ]] bool HasFrame (void) noexcept;

    /// Performs some FD polling, gets called by event thread.
    [[ maybe_unused ]] void Poll (void);
  protected:
    std::mutex m_FramesMutex;
    std::list<const frame_t *> m_Frames;
    i32 m_FD;
  };
};
