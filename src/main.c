#include "attack.h"
#include "bitboard.h"
#include "board.h"
#include "common.h"
#include "magic.h"
#include "move_generator.h"
#include "prng.h"
#include "perft.h"

#include <stdint.h>
#include <stdio.h>

int main() {
  printf("dd_chess\n");
  init_attacks();

  board_t board = create_new_board();
  const int size = 3;
  int depths[] = {0, 1, 2};  
  printf("PERFT Results\n");
  printf("========================================================\n");
  for(int i = 0; i < size; i++){
    printf("DEPTH: %d COUNT: %ld\n", depths[i], perft(depths[i], &board));
  }

  return 0;
}
