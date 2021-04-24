#include "Checksum.hpp"

namespace Checksums {
  /// Adds 2 bytes to the OC16 checksum.
  uint16_t __oc16_add (uint16_t cs, uint16_t val) noexcept {
    if ((static_cast<uint32_t>(cs) + static_cast<uint32_t>(val)) >= 0xFFFF) {
      ++cs;
    }

    cs += val;

    return cs;
  }

  /// Calculates an OC16 checksum.
  uint16_t __oc16_do (const uint8_t *buffer, uint16_t size) noexcept {
    uint16_t cs = 0x0000;

    // Performs the cehcksum calculation of the even part of the checksum
    //  we will skip the (possible) last byte, and truncate it with zero
    //  later in the process.
    uint16_t n = (size % 2 == 0) ? size : size - 1;
    for (uint16_t i = 0; i < n; i += 2) {
      cs = __oc16_add (cs, *reinterpret_cast<const uint16_t *>(buffer));
      buffer += 2;
    }

    // Checks if N is not equal to the size, if so we know truncation is
    //  required to make clean checksum.
    if (n != size) {
      uint16_t halfword = (static_cast<uint16_t>(*buffer) << 8);
      cs = __oc16_add (cs, halfword);
    }

    // Idk why, but the IP protocol performs an invert operation.
    return ~cs;
  }
}
