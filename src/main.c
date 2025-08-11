#include "bitboard.h"
#include "board.h"
#include "common.h"
#include "magic.h"
#include "move_generator.h"
#include "prng.h"

#include <stdint.h>
#include <stdio.h>

int main() {
  printf("dd_chess\n");

  for (int i = 0; i < SQUARE_COUNT; i++) {
    printf("0x%016llxULL\n", find_magic_number(i, rook_occupancy_count[i], ROOK), 16);
  }
  // printf("0x%llx\n", find_magic_number(i, bishop_occupancy_count[i], BISHOP));

  return 0;
}
