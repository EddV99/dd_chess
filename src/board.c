#include "board.h"
#include "common.h"

board_t create_new_board() {
  board_t new_board = {.is_white_turn = true,
                       .castle_rights = 0b11110000,

                       .white_king = square_mask(E1),
                       .white_queen = square_mask(D1),
                       .white_rooks = square_mask(A1) | square_mask(H1),
                       .white_bishops = square_mask(C1) | square_mask(F1),
                       .white_knights = square_mask(B1) | square_mask(G1),
                       .white_pawns = square_mask(A2) | square_mask(B2) | square_mask(C2) | square_mask(D2) |
                                      square_mask(E2) | square_mask(F2) | square_mask(G2) | square_mask(H2),

                       .black_king = square_mask(E8),
                       .black_queen = square_mask(D8),
                       .black_rooks = square_mask(A8) | square_mask(H8),
                       .black_bishops = square_mask(C8) | square_mask(F8),
                       .black_knights = square_mask(B8) | square_mask(G8),
                       .black_pawns = square_mask(A7) | square_mask(B7) | square_mask(C7) | square_mask(D7) |
                                      square_mask(E7) | square_mask(F7) | square_mask(G7) | square_mask(H7)};

  return new_board;
}
