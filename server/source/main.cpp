#include "main.hpp"

#include "SerialDebug.hpp"

const char *DEBUG_PATH = "/dev/ttyUSB0";
u64 DEBUG_BAUD = 921600UL;

int main(int argc, const char **argv) noexcept {
  try {
    Protocols::Debug::ReceivingSerialSession session;

    // Opens the session to the controller.
    std::cout << "Attempting to open serial session to \"" << DEBUG_PATH
      << "\" with " << DEBUG_BAUD << " BAUD" << std::endl;
    session.Open (DEBUG_PATH, DEBUG_BAUD);
    std::cout << "Serial connection opened!" << std::endl;
    
    // Creates the polling loop, which allows us to offload the
    //  FD-IO to other threads.
    auto thread = std::thread ([&] (void) {
      std::cout << "Event polling thread started ..." << std::endl;
      for (;;) {
        session.Poll ();

        // If there are any debug frames available after polling, get the
        //  message and print it to the console.
        while (session.HasFrame ()) {
          const Protocols::Debug::frame_t *frame = session.GetFrame ();
          std::cout << "[DEBUG] -> " << frame->packet.event << std::endl;
          delete frame;
        }

        std::this_thread::yield ();
      }
    });


    // To prevent from the process of bugging out, join the thread.
    thread.join ();
  } catch (const std::runtime_error &e) {
    std::cerr << "Runtime error in main thread: " << e.what () << std::endl;
  }

  return 0;
}
