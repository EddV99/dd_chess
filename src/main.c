#include "bitboard.h"
#include "board.h"
#include "common.h"
#include "move_generator.h"

#include <stdio.h>

int main() {
  printf("dd_chess\n");
  bitboard_t board = 0;
  printf("%d", least_significant_one_bit(board));

  return 0;
}
