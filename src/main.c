#include "bitboard.h"
#include "board.h"
#include "common.h"
#include "move_generator.h"

#include <stdio.h>

int main() {
  printf("dd_chess\n");

  generate_pawn_attacks();
  print_board(pawn_attacks[WHITE][G4]);

  return 0;
}
