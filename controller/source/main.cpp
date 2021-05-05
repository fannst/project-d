#include "main.hpp"

#include "SysClock.hpp"
#include "dog/Main.hpp"

extern "C" void __libc_init_array (void);

extern "C" void HardFault_Handler (void) noexcept {
  for (;;);
}

/// Gets called when the startup code is done, and ready for C / CXX.
extern "C" int main (void) noexcept {
  // Enables the FPU and calls the constructors.
  SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));
  __libc_init_array ();

  // Initializes the system clock to full speed.
  SysClock::Init ();

  // Starts the dog software.s
  Dog::Main &instance = Dog::Main::GetInstance ();
  instance.InitializePeripherals ();
  instance.InitializeDrivers ();

  for (;;) {
    instance.Loop ();
  }
}
