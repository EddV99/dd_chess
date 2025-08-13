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
  generate_pseudo_legal_pawn_moves(&board, (void *)0);

  return 0;
}
