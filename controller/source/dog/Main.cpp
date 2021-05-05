#include "dog/Main.hpp"

#include "Delay.hpp"
#include "peripherals/GPIOx.hpp"
#include "peripherals/USARTx.hpp"
#include "drivers/WS2812.hpp"

namespace Dog {
  Main::Main (void) noexcept:
    m_Buzzer (Peripherals::GPIOs::C, 2),
    m_Paw1 (
      TIM4,
      1200,   /* ARR: 60,000 / 1,200 = 50Hz*/
      1800,   /* PSC: 108,000,000 / 1,800: 60,000Hz */
      .8F,    /* Min */
      2.3F,   /* Max */
      180.F   /* Degrees */
    )
  {}

  /// Gets the main instance class reference.
  Main &Main::GetInstance (void) noexcept {
    return Main::INSTANCE;
  }

  /// Performs the peripheral initialization.
  void Main::InitializePeripherals (void) noexcept {
    using namespace Peripherals;

    /// Initializes the delay timer.
    Delay::Init ();

    /// Initializes the clock sources for peripherals.
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN | RCC_AHB1ENR_DMA2EN;

    GPIOs::Init ();
    USARTs::Init ();

    /// Initializes the specific hardware.
    Main::__InitializeUSARTs ();
    Main::__InitializeETHs ();
  }

  /// Performs the driver initialization.
  void Main::InitializeDrivers (void) noexcept {
    __InitializeStatusIndicators ();
    __InitializeServos ();

    Drivers::WS2812::GetInstance().Init ();
    Drivers::WS2812 &driver = Drivers::WS2812::GetInstance ();
    driver.ClearColors ();
    driver.SetColor (0, 10, 0, 0, 0);
    driver.SwapBuffers ();
    driver.SendBurst ();

    // Writes the initialization done debug event.
    m_Buzzer.Buzz (200, 200);
  }


  /// The loop method.
  void Main::Loop (void) noexcept {
    Drivers::WS2812 &driver = Drivers::WS2812::GetInstance ();

    for (u8 i = 0; i < 8; ++i) {
      driver.ClearColors ();
      driver.SetColor (i, 0, 40, 0, 0);
      
      driver.SwapBuffers ();
      driver.SendBurst ();
      for (u32 i = 0; i < 10000000; ++i) asm ("NOP\n\t");
    }
    // m_Paw1.Move (0, 90.F);
    // m_Paw1.Move (1, 10.F);
    // m_Paw1.Move (2, 50.F);
    // Delay::Ms (1000);
    // m_Paw1.Move (0, 150.F);
    // m_Paw1.Move (1, 80.F);
    // m_Paw1.Move (2, 0.F);
    //     Delay::Ms (1000);

  }

  /// Performs the USARTs initialization.
  void Main::__InitializeUSARTs (void) noexcept {
    using namespace Peripherals;
  }

  /// Performs the ETHs initializtion.
  void Main::__InitializeETHs (void) noexcept {
    using namespace Peripherals;
  }

  /// Performs status indicator initialization.
  void Main::__InitializeStatusIndicators (void) noexcept {
    m_Buzzer.Init ();
  }

  /// Initializes the servos.
  void Main::__InitializeServos (void) noexcept {    // Initializes the servos.
    using namespace Peripherals;

    // Iniitalizes the timer
    m_Paw1.Init ();

    // Initializes the GPIO.
    GPIOs::B.SetMode (6, GPIO_Mode::AF);
    GPIOs::B.SetAF (6, 2);

    GPIOs::B.SetMode (7, GPIO_Mode::AF);
    GPIOs::B.SetAF (7, 2);

    GPIOs::B.SetMode (8, GPIO_Mode::AF);
    GPIOs::B.SetAF (8, 2);
  }

  Main Main::INSTANCE;
}
