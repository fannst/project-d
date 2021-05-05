#include "main.hpp"

#include "SysClock.hpp"
#include "dog/Main.hpp"

/// Gets called when the startup code is done, and ready for C / CXX.
extern "C" int main (void) noexcept {
  Dog::Main &instance = Dog::Main::GetInstance ();

  SysClock::Init ();

  instance.InitializePeripherals ();
  instance.InitializeDrivers ();

  for (;;);
}
