#include "prng.h"
#include <stdint.h>

prng_t create_random_generator() {
  prng_t prng = {.state = DEFAULT_SEED};
  return prng;
}

uint32_t get_random_number_u32(prng_t *prng) {
  uint32_t number = prng->state;
  number ^= number << 13;
  number ^= number >> 17;
  number ^= number << 5;
  prng->state = number;
  return number;
}

uint64_t get_random_number_u64(prng_t *prng) {
  uint64_t n1, n2, n3, n4;
  n1 = ((uint64_t)get_random_number_u32(prng)) & 0xFFFF;
  n2 = ((uint64_t)get_random_number_u32(prng)) & 0xFFFF;
  n3 = ((uint64_t)get_random_number_u32(prng)) & 0xFFFF;
  n4 = ((uint64_t)get_random_number_u32(prng)) & 0xFFFF;
  return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}
