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

  print_board(rook_occupancy(D4));
  print_board(bishop_occupancy(D4));
  return 0;
}
