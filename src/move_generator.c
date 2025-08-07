#include "move_generator.h"

#include "bitboard.h"
#include "common.h"

bitboard_t pawn_attacks[2][SQUARE_COUNT] = {0};

void generate_pawn_attacks() {
  const bitboard_t NOT_A_FILE = 0x7f7f7f7f7f7f7f7f;
  const bitboard_t NOT_H_FILE = 0xfefefefefefefefe;

  for (int i = 0; i < SQUARE_COUNT; i++) {
    bitboard_t board = 0;
    set_bit(board, i);

    bitboard_t board_west = board;
    bitboard_t board_east = board;
    board_west = (board << 9) & NOT_H_FILE;
    board_east = (board << 7) & NOT_A_FILE;
    pawn_attacks[WHITE][i] = board_west | board_east;

    board_west = board;
    board_east = board;
    board_west = (board >> 7) & NOT_H_FILE;
    board_east = (board >> 9) & NOT_A_FILE;
    pawn_attacks[BLACK][i] = board_west | board_east;
  }
}
