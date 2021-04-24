#include "entry.hpp"

#include "SysClock.hpp"
#include "dog/Main.hpp"

extern "C" {
  /// Gets called when the startup code is done, and ready for C / CXX.
  int main (void) noexcept {
    Dog::Main &instance = Dog::Main::GetInstance ();

    // Initializes the system clock to full available speed (and above ;P).
    SysClock::Init ();

    // Initializes the peripherals first, and the drivers after. We do it
    //  in this order to prevent drivers from using non-ready peripherals.
    instance.InitializePeripherals ();
    instance.InitializeDrivers ();

    for (;;);
  }
}
