#include "attack.h"
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

  bitboard_t board = square_mask(C5);
  board |= square_mask(F2);
  board |= square_mask(G7);
  board |= square_mask(B2);
  board |= square_mask(G5);
  board |= square_mask(E2);
  board |= square_mask(E7);

  print_board(board);
  print_board(get_bishop_attacks(E5, board));
  print_board(get_rook_attacks(E5, board));
  print_board(get_queen_attacks(E5, board));

  return 0;
}
