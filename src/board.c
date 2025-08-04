#include "board.h"
#include "common.h"
#include <stdio.h>

board_t create_new_board() {
  board_t new_board = {.is_white_turn = true,
                       .castle_rights = 0b11110000,

                       .white_king = 1ULL << E1,
                       .white_queen = 1ULL << D1,
                       .white_rooks = 1ULL << A1 | 1ULL << H1,
                       .white_bishops = 1ULL << C1 | 1ULL << F1,
                       .white_knights = 1ULL << B1 | 1ULL << G1,
                       .white_pawns = 1ULL << A2 | 1ULL << B2 | 1ULL << C2 | 1ULL << D2 | 1ULL << E2 | 1ULL << F2 | 1ULL << G2 | 1ULL << H2,

                       .black_king = 1ULL << E8,
                       .black_queen = 1ULL << D8,
                       .black_rooks = 1ULL << A8 | 1ULL << H8,
                       .black_bishops = 1ULL << C8 | 1ULL << F8,
                       .black_knights = 1ULL << B8 | 1ULL << G8,
                       .black_pawns = 1ULL << A7 | 1ULL << B7 | 1ULL << C7 | 1ULL << D7 | 1ULL << E7 | 1ULL << F7 | 1ULL << G7 | 1ULL << H7};

  return new_board;
}

void print_board(uint64_t bitboard) {
  for(int rank = 7; rank >= 0; rank--) {
    if(rank == 7)
      printf("%d ", rank + 1);
    else
      printf("\n%d ", rank + 1);
    for(int file = 0; file < 8; file++) {
      printf("%d ", (bitboard & (1ULL << ((rank * 8) + file))) ? 1 : 0);
    }
  }
  printf("\n  A B C D E F G H \n");
}
