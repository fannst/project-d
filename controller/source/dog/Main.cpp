#include "dog/Main.hpp"

#include "peripherals/GPIOx.hpp"
#include "peripherals/USARTx.hpp"

namespace Dog {
  Main::Main (void) noexcept:
    m_DebugUSART (Peripherals::USARTs::I1)
  {}

  /// Gets the main instance class reference.
  Main &Main::GetInstance (void) noexcept {
    return Main::INSTANCE;
  }

  /// Performs the peripheral initialization.
  void Main::InitializePeripherals (void) noexcept {
    using namespace Peripherals;

    /// Initializes the clock sources for peripherals.
    GPIOs::Init ();
    USARTs::Init ();

    /// Initializes the specific hardware.
    Main::__InitializeUSARTs ();

    /// Prints to the serial console that we're done initializing.
    USARTs::I1.WriteBytes ((const u8 *)"Hello World\r\n", 13);
  }

  /// Performs the driver initialization.
  void Main::InitializeDrivers (void) noexcept {

    // Writes the initialization done debug event.
    m_DebugUSART.WriteSimpleEvent (Protocols::Debug::Event::InitializationDone);
  }

  /// Performs the USARTs initialization.
  void Main::__InitializeUSARTs (void) noexcept {
    using namespace Peripherals;
    
    //
    // Debug Connection UART setup
    //

    // Sets PA9 and PA10 to AF mode.
    GPIOs::A.SetMode (9, GPIO_Mode::AF);
    GPIOs::A.SetMode (10, GPIO_Mode::AF);

    // Selects AF7 for PA9 (RX) and PA10 (TX).
    GPIOs::A.SetAF (9, 7);
    GPIOs::A.SetAF (10, 7);

    // Initializes the UART to 921600 BAUD (Almost 1Mhz).
    USARTs::I1.Reset ();
    USARTs::I1.SetBaud (921600UL);
    USARTs::I1.EnableTransmitter ();      // Sets TE
    USARTs::I1.Enable ();                 // Sets UE

    //
    // SPFP Connection UART setup
    //

    // Sets PD5 (TX) and PD6 (RX) to AF mode.
    GPIOs::D.SetMode (5, GPIO_Mode::AF);
    GPIOs::D.SetMode (6, GPIO_Mode::AF);

    // Selects AF7 for PD5 (TX) and PD6 (RX).
    GPIOs::D.SetAF (5, 7);
    GPIOs::D.SetAF (6, 7);

    // Initializes the UART to 921600 BAUD (Almost 1Mhz).
    USARTs::I2.Reset ();
    USARTs::I2.SetBaud (921600UL);
    USARTs::I2.EnableAll ();              // Sets UE, TE and RE
  }

  Main Main::INSTANCE;
}
