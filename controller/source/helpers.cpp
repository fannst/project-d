#include "helpers.hpp"

[[ maybe_unused ]] void volatile_memset (volatile void *s, u8 c, size_t n) {
  volatile u8 *p = reinterpret_cast<volatile u8 *>(s);
  while (n-- > 0) {
    *p++ = c;
  }
}