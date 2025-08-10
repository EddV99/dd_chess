#include "prng.h"
#include <stdint.h>

prng_t create_random_generator() {
  prng_t prng = {.state = DEFAULT_SEED};
  return prng;
}

uint32_t get_random_number(prng_t *prng) {
  uint32_t number = prng->state;
  number ^= number << 13;
  number ^= number >> 17;
  number ^= number << 5;
  prng->state = number;
  return number;
}
