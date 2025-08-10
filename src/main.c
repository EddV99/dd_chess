#include "bitboard.h"
#include "board.h"
#include "common.h"
#include "move_generator.h"
#include "prng.h"

#include <stdio.h>

int main() {
  printf("dd_chess\n");

  prng_t prng = create_random_generator();

  for (int i = 0; i < 100; i++) {
    printf("%d. %u\n", i, get_random_number(&prng));
  }

  return 0;
}
