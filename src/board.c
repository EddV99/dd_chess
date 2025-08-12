#include "board.h"
#include "common.h"

board_t create_new_board() {
  board_t new_board = {
      .is_white_turn = true,
      .castle_rights = 0b11110000,
      .bitboards[INDEX_BITBOARD(WHITE, KING)] = square_mask(E1),
      .bitboards[INDEX_BITBOARD(WHITE, QUEEN)] = square_mask(D1),
      .bitboards[INDEX_BITBOARD(WHITE, ROOK)] = square_mask(A1) | square_mask(H1),
      .bitboards[INDEX_BITBOARD(WHITE, BISHOP)] = square_mask(C1) | square_mask(F1),
      .bitboards[INDEX_BITBOARD(WHITE, KNIGHT)] = square_mask(B1) | square_mask(G1),
      .bitboards[INDEX_BITBOARD(WHITE, PAWN)] = square_mask(A2) | square_mask(B2) | square_mask(C2) | square_mask(D2) |
                                                square_mask(E2) | square_mask(F2) | square_mask(G2) | square_mask(H2),
      .bitboards[INDEX_BITBOARD(BLACK, KING)] = square_mask(E8),
      .bitboards[INDEX_BITBOARD(BLACK, QUEEN)] = square_mask(D8),
      .bitboards[INDEX_BITBOARD(BLACK, ROOK)] = square_mask(A8) | square_mask(H8),
      .bitboards[INDEX_BITBOARD(BLACK, BISHOP)] = square_mask(C8) | square_mask(F8),
      .bitboards[INDEX_BITBOARD(BLACK, KNIGHT)] = square_mask(B8) | square_mask(G8),
      .bitboards[INDEX_BITBOARD(BLACK, PAWN)] = square_mask(A7) | square_mask(B7) | square_mask(C7) | square_mask(D7) |
                                                square_mask(E7) | square_mask(F7) | square_mask(G7) | square_mask(H7),
  };
  return new_board;
}
