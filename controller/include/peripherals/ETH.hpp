#include "stm32f767xx.h"

#pragma once

namespace Peripherals {
  typedef struct {
    unsigned    fast          : 1;    /* Use Fast-Ethernet ? */
    unsigned    full_duplex   : 1;    /* Use Full-Duplex Mode */
  } Ethernet_Init_t;

  typedef struct {
    unsigned    used          : 1;    /* Is the pool used ? */
  } Ethernet_BufferPool_t;

  class Ethernet {
  public:
    /// Creates new Ethernet driver instance.
    [[ maybe_unused ]] Ethernet (ETH_TypeDef *eth) noexcept;

    /// Initializes the current Ethernet driver.
    [[ maybe_unused ]] void Init (const Ethernet_Init_t &cfg) noexcept;
  protected:
    ETH_TypeDef *m_ETH;
  };

  class Ethernets {
  public:
  protected:
  };
}
