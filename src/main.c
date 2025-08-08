#include "bitboard.h"
#include "board.h"
#include "common.h"
#include "move_generator.h"

#include <stdio.h>

int main() {
  printf("dd_chess\n");

  generate_pawn_attacks();
  generate_knight_attacks();
  generate_king_attacks();

  print_board(rook_occupancy(A8));
  return 0;
}
