#include "stm32f767xx.h"

#pragma once


#define SYSCLOCK_ETHERNET 			      216UL
#define SYSCLOCK_HCLK_MHZ				      216UL
#define SYSCLOCK_SYSTEM				        216UL
#define SYSCLOCK_FCLK					        216UL
#define SYSCLOCK_APB1_PERIPHERALS		  54UL
#define SYSCLOCK_APB1_TIMERS			    108UL
#define SYSCLOCK_APB2_PERIPHERALS		  108UL
#define SYSCLOCK_APB2_TIMERS			    216UL
#define MHZ(A) 						            (A * 1000UL * 1000UL)

class SysClock {
public:
  /// Initializes the system clock to full speed.
  static void Init (void) noexcept;
};
