#include "bitboard.h"
#include "board.h"
#include "common.h"
#include "move_generator.h"

#include <stdio.h>

int main() {
  printf("dd_chess\n");
  bitboard_t board = 0;
  printf("%d", population_count(board));

  return 0;
}
