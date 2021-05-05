#include "types.hpp"
#include "protocols/USARTDebug.hpp"
#include "drivers/Buzzer.hpp"
#include "drivers/ServoCluster.hpp"

#pragma once

namespace Dog {
  class Main {
  public:
    /// Gets the main instance class reference.
    static Main &GetInstance (void) noexcept;

    /// Performs the peripheral initialization.
    void InitializePeripherals (void) noexcept;

    /// Performs the driver initialization.
    void InitializeDrivers (void) noexcept;

    /// The loop method.
    void Loop (void) noexcept;
  private:
    Drivers::Buzzer m_Buzzer;
    Drivers::ServoCluster m_Paw1;

    /// Performs the USARTs initialization.
    void __InitializeUSARTs (void) noexcept;

    /// Performs the ETHs initializtion.
    void __InitializeETHs (void) noexcept;

    /// Performs status indicator initialization.
    void __InitializeStatusIndicators (void) noexcept;

    /// Initializes the servos.
    void __InitializeServos (void) noexcept;

    Main (void) noexcept;
    ~Main (void) noexcept = default;

    static Main INSTANCE;
  };
}
