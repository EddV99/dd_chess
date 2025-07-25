#include "board.h"

Board create_new_board() {
  Board new_board = {.is_white_turn = true,
                     .castle_rights = 0b11110000,

                     .white_king = 0x8,
                     .white_queen = 0x10,
                     .white_rooks = 0x81,
                     .white_bishops = 0x24,
                     .white_knights = 0x42,
                     .white_pawns = 0xff00,

                     .black_king = 0x0800000000000000,
                     .black_queen = 0x1000000000000000,
                     .black_rooks = 0x8100000000000000,
                     .black_bishops = 0x2400000000000000,
                     .black_knights = 0x4200000000000000,
                     .black_pawns = 0x00ff000000000000,

                     .squares = { EMPTY }};
  
  // layout here: https://www.chessprogramming.org/0x88#Layout
  new_board.squares[0x00] = WHITE_ROOK;
  new_board.squares[0x01] = WHITE_KNIGHT;
  new_board.squares[0x02] = WHITE_BISHOP;
  new_board.squares[0x03] = WHITE_QUEEN;
  new_board.squares[0x04] = WHITE_KING;
  new_board.squares[0x05] = WHITE_BISHOP;
  new_board.squares[0x06] = WHITE_KNIGHT;
  new_board.squares[0x07] = WHITE_ROOK;

  new_board.squares[0x10] = WHITE_PAWN;
  new_board.squares[0x11] = WHITE_PAWN;
  new_board.squares[0x12] = WHITE_PAWN;
  new_board.squares[0x13] = WHITE_PAWN;
  new_board.squares[0x14] = WHITE_PAWN;
  new_board.squares[0x15] = WHITE_PAWN;
  new_board.squares[0x16] = WHITE_PAWN;
  new_board.squares[0x17] = WHITE_PAWN;

  new_board.squares[0x70] = BLACK_ROOK;
  new_board.squares[0x71] = BLACK_KNIGHT;
  new_board.squares[0x72] = BLACK_BISHOP;
  new_board.squares[0x73] = BLACK_QUEEN;
  new_board.squares[0x74] = BLACK_KING;
  new_board.squares[0x75] = BLACK_BISHOP;
  new_board.squares[0x76] = BLACK_KNIGHT;
  new_board.squares[0x77] = BLACK_ROOK;

  new_board.squares[0x60] = BLACK_PAWN;
  new_board.squares[0x61] = BLACK_PAWN;
  new_board.squares[0x62] = BLACK_PAWN;
  new_board.squares[0x63] = BLACK_PAWN;
  new_board.squares[0x64] = BLACK_PAWN;
  new_board.squares[0x65] = BLACK_PAWN;
  new_board.squares[0x66] = BLACK_PAWN;
  new_board.squares[0x67] = BLACK_PAWN;


  return new_board;
}
