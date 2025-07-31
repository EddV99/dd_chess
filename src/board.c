#include "common.h"
#include "board.h"

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
                       .black_pawns = BIT_A7 | BIT_B7 | BIT_C7 | BIT_D7 | BIT_E7 | BIT_F7 | BIT_G7 | BIT_H7,

                       .squares = {EMPTY}};

  // layout here: https://www.chessprogramming.org/0x88#Layout
  new_board.squares[MAILBOX_A1] = WHITE_ROOK;
  new_board.squares[MAILBOX_B1] = WHITE_KNIGHT;
  new_board.squares[MAILBOX_C1] = WHITE_BISHOP;
  new_board.squares[MAILBOX_D1] = WHITE_QUEEN;
  new_board.squares[MAILBOX_E1] = WHITE_KING;
  new_board.squares[MAILBOX_F1] = WHITE_BISHOP;
  new_board.squares[MAILBOX_G1] = WHITE_KNIGHT;
  new_board.squares[MAILBOX_H1] = WHITE_ROOK;

  new_board.squares[MAILBOX_A2] = WHITE_PAWN;
  new_board.squares[MAILBOX_B2] = WHITE_PAWN;
  new_board.squares[MAILBOX_C2] = WHITE_PAWN;
  new_board.squares[MAILBOX_D2] = WHITE_PAWN;
  new_board.squares[MAILBOX_E2] = WHITE_PAWN;
  new_board.squares[MAILBOX_F2] = WHITE_PAWN;
  new_board.squares[MAILBOX_G2] = WHITE_PAWN;
  new_board.squares[MAILBOX_H2] = WHITE_PAWN;

  new_board.squares[MAILBOX_A8] = BLACK_ROOK;
  new_board.squares[MAILBOX_B8] = BLACK_KNIGHT;
  new_board.squares[MAILBOX_C8] = BLACK_BISHOP;
  new_board.squares[MAILBOX_D8] = BLACK_QUEEN;
  new_board.squares[MAILBOX_E8] = BLACK_KING;
  new_board.squares[MAILBOX_F8] = BLACK_BISHOP;
  new_board.squares[MAILBOX_G8] = BLACK_KNIGHT;
  new_board.squares[MAILBOX_H8] = BLACK_ROOK;

  new_board.squares[MAILBOX_A7] = BLACK_PAWN;
  new_board.squares[MAILBOX_B7] = BLACK_PAWN;
  new_board.squares[MAILBOX_C7] = BLACK_PAWN;
  new_board.squares[MAILBOX_D7] = BLACK_PAWN;
  new_board.squares[MAILBOX_E7] = BLACK_PAWN;
  new_board.squares[MAILBOX_F7] = BLACK_PAWN;
  new_board.squares[MAILBOX_G7] = BLACK_PAWN;
  new_board.squares[MAILBOX_H7] = BLACK_PAWN;

  return new_board;
}
