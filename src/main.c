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
  board_t board = create_new_board();
  print_board(board.black_pieces);
  unset_least_significant_one_bit(board.black_pieces);
  print_board(board.black_pieces);
  unset_least_significant_one_bit(board.black_pieces);
  print_board(board.black_pieces);

  return 0;
}
