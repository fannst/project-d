#include "SerialDebug.hpp"

namespace Protocols::Debug {
  ////////////////////////////////////////////////////////////////////
  // ReceivingSerialSession                                         //
  ////////////////////////////////////////////////////////////////////

  /// Gets one of the available frames.
  [[ maybe_unused ]] const frame_t *ReceivingSerialSession::GetFrame (void) {
    m_FramesMutex.lock ();

    // Gets the back of the list, and pops it off.
    const frame_t *t = m_Frames.back ();
    m_Frames.pop_back ();

    // Unlocks the mutex, and returns the pointer.
    m_FramesMutex.unlock ();
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

    m_FramesMutex.lock ();
    m_Frames.push_front (copied);
    m_FramesMutex.unlock ();
  }

  /// Opens the FD to specified path with baud rate.
  [[ maybe_unused ]] void ReceivingSerialSession::Open (const char *path, u64 baud) {
      struct termios tty;
      
      // Attempts to open the FD.
      if ((m_FD = open (path, O_RDWR | O_NOCTTY | O_SYNC)) < 0) {
        throw std::runtime_error (std::string("Failed to create file pointer: ") + strerror (errno));
      }

      if (tcgetattr (m_FD, &tty) != 0) {
        throw std::runtime_error (std::string("Failed to get attributes: ") + strerror (errno));
      }

      cfsetspeed (&tty, baud);

      tty.c_cflag &= ~(CSIZE | PARENB | PARODD | CSTOPB | CRTSCTS);
      tty.c_cflag |= (CLOCAL | CREAD | CS8);

      tty.c_iflag &= ~(IGNBRK | IXON | IXOFF | IXANY);

      tty.c_lflag = 0;
      tty.c_oflag = 0;

      tty.c_cc[VMIN] = 0;
      tty.c_cc[VTIME] = 1;

      if (tcsetattr (m_FD, TCSANOW, &tty) != 0) {
        throw std::runtime_error (std::string("Failed to set attributes: ") + strerror (errno));
      }
  }

  /// Checks if an frame is available.
  [[ maybe_unused ]] bool ReceivingSerialSession::HasFrame (void) noexcept {
    // Locks the mutex, checks if the frames are empty, and unlocks
    //  after which we return if there is something available.
    m_FramesMutex.lock ();
    bool empty = m_Frames.empty();
    m_FramesMutex.unlock ();
    return !empty;
  }

  /// Performs some FD polling, gets called by event thread.
  [[ maybe_unused ]] void ReceivingSerialSession::Poll (void) {
    // Attempts to get the number of available bytes to read, throw
    //  exception if this fails.
    i32 cnt;
    if (ioctl (m_FD, FIONREAD, &cnt) == -1) {
      throw std::runtime_error (std::string ("ioctl() failed: ") + strerror (errno));
    }

    // Makes sure there is data available, if it is less or equal to zero
    //  just return, there is nothing.
    if (cnt <= 0) {
      return;
    }

    // Allocates the memory required for reading those N bytes, and reads
    //  those number of bytes.
    u8 *buffer = new u8[cnt];
    if (buffer == nullptr) {
      throw std::runtime_error ("new u8[cnt]: Allocation failed.");
    }

    if (read (m_FD, buffer, cnt) == -1) {
      throw std::runtime_error (std::string ("read() failed: ") + strerror (errno));
    }

    // Loops over all the bytes, and updates the frame state machine.
    for (i32 i = 0; i < cnt; ++i) {
      UpdateStateMachine (buffer[i]);
    }

    // De-allocates the buffer.
    delete buffer;
  }
}