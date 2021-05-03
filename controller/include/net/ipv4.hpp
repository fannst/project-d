#include "types.hpp"

#pragma once

namespace NET {
  ////////////////////////////////////////////////////////////////////
  // IPv4 (Network Layer)                                           //
  ////////////////////////////////////////////////////////////////////

  typedef struct __attribute__ (( packed )) {
    u8    version_hlen;
    u8    service;
    u16   length;
    u16   id;
    u16   fragment;
    u8    ttl;
    u8    proto;
    u16   cs;
    u32   src;
    u32   dest;
  } IPv4_hdr_t;

  typedef struct __attribute__ (( packed )) {
    IPv4_hdr_t    hdr;
    u8            payload[0];
  } IPv4_pkt_t;
}
