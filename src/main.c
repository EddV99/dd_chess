#include "attack.h"
#include "bitboard.h"
#include "board.h"
#include "common.h"
#include "magic.h"
#include "move_generator.h"
#include "perft.h"
#include "prng.h"

#include <stdint.h>
#include <stdio.h>

int main() {
  printf("dd_chess\n");
  init_attacks();

  int start = 0;
  int end = 2;
  int depths[] = {0, 1, 2, 3, 4, 5};
  printf("PERFT Results\n");
  printf("========================================================\n");
  for (int i = start; i <= end; i++) {
    board_t board = create_new_board();
    printf("DEPTH: %d COUNT: %ld\n", depths[i], perft(depths[i], &board, 0));
  }

  return 0;
}
