#include "types.hpp"
#include "protocols/USARTDebug.hpp"

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
  private:
    Protocols::Debug::USARTTransmittingSession m_DebugUSART;

    /// Performs the USARTs initialization.
    void __InitializeUSARTs (void) noexcept;

    Main (void) noexcept;
    ~Main (void) noexcept = default;

    static Main INSTANCE;
  };
}
