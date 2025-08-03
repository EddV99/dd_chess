#include "board.h"
#include "common.h"

board_t create_new_board() {
  board_t new_board = {.is_white_turn = true,
                       .castle_rights = 0b11110000,

                       .white_king = BIT_E1,
                       .white_queen = BIT_D1,
                       .white_rooks = BIT_A1 | BIT_H1,
                       .white_bishops = BIT_C1 | BIT_F1,
                       .white_knights = BIT_B1 | BIT_G1,
                       .white_pawns = BIT_A2 | BIT_B2 | BIT_C2 | BIT_D2 | BIT_E2 | BIT_F2 | BIT_G2 | BIT_H2,

                       .black_king = BIT_E8,
                       .black_queen = BIT_D8,
                       .black_rooks = BIT_A8 | BIT_H8,
                       .black_bishops = BIT_C8 | BIT_F8,
                       .black_knights = BIT_B8 | BIT_G8,
                       .black_pawns = BIT_A7 | BIT_B7 | BIT_C7 | BIT_D7 | BIT_E7 | BIT_F7 | BIT_G7 | BIT_H7};

  return new_board;
}
