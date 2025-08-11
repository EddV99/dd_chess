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
  init_attacks();

  bitboard_t board = square_mask(E3);
  board |= square_mask(E4);
  print_board(board);
  print_board(get_bishop_attacks(D4, board));
  print_board(get_rook_attacks(D4, board));

  return 0;
}
