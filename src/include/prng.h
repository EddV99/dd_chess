#ifndef DD_PRNG_GENERATOR_H_
#define DD_PRNG_GENERATOR_H_

#include <stdint.h>

#define DEFAULT_SEED 1804289383

typedef struct {
  uint32_t state;
} prng_t;

prng_t create_random_generator();

uint32_t get_random_number(prng_t *prng);

#endif
