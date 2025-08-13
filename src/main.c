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
  move_t moves[MAX_MOVES] = {0};

  generate_pseudo_legal_pawn_moves(&board, moves);

  int i = 0;
  while (i < MAX_MOVES && moves[i]) {
    move_t move = moves[i];
    bitboard_t b = board.all_pieces;
    set_bit(b, get_move_to(move));
    unset_bit(b, get_move_from(move));
    print_board(b);
    set_bit(b, get_move_from(move));
    unset_bit(b, get_move_to(move));
    i++;
  }

  return 0;
}
