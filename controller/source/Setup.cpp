#include "Setup.hpp"

#include "peripherals/GPIOx.hpp"

void Setup::RCC_Init (void) noexcept {
    GPIOs::Init ();
}

void Setup::UARTS_Init (void) noexcept {
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

    //
    // SPFP Connection UART setup
    //

    // Initializes the UART to 921600 BAUD (Almost 1Mhz).

    //
    // GPS RX UART setup
    //

    // Initializes the UART to 9600 BAUD.

}