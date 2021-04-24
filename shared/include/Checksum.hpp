#include <stdlib.h>
#include "types.hpp"

#pragma once

namespace Checksums {
  /// Adds 2 bytes to the OC16 checksum.
	uint16_t __oc16_add (uint16_t cs, uint16_t val) noexcept;

	/// Calculates an OC16 checksum.
	uint16_t __oc16_do (const uint8_t *buffer, uint16_t size) noexcept;
}
