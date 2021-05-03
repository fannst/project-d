#include "types.hpp"

#pragma once

namespace NET {
  ////////////////////////////////////////////////////////////////////
  // MAC (Data-Link layer)                                          //
  ////////////////////////////////////////////////////////////////////

  typedef struct __attribute__ (( packed )) {
    u8    destination[6];
    u8    source[6];
    u16   type;
    u8    payload;
  } mac_frame_t;
}
