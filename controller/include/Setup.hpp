#include "stm32f767xx.h"

#pragma once

class Setup {
public:
    static void RCC_Init (void) noexcept;

    static void UARTS_Init (void) noexcept;
protected:
};
