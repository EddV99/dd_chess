#include "move_generator.h"

#include "bitboard.h"
#include "common.h"

bitboard_t pawn_attacks[2][SQUARE_COUNT] = {0};

void generate_pawn_attacks() {
  for (int i = 0; i < SQUARE_COUNT; i++) {
    bitboard_t board = 0;
    set_bit(board, i);

    bitboard_t attacks = (board << 9) & NOT_H_FILE;
    attacks |= (board << 7) & NOT_A_FILE;
    pawn_attacks[WHITE][i] = attacks;

    attacks = (board >> 7) & NOT_H_FILE;
    attacks |= (board >> 9) & NOT_A_FILE;
    pawn_attacks[BLACK][i] = attacks;
  }
}

bitboard_t knight_attacks[SQUARE_COUNT] = {0};

void generate_knight_attacks() {
  for (int i = 0; i < SQUARE_COUNT; i++) {
    bitboard_t board = 0;
    set_bit(board, i);

    // west side attacks
    bitboard_t attacks = (board >> 6) & NOT_GH_FILE;
    attacks |= (board << 10) & NOT_GH_FILE;
    attacks |= (board >> 15) & NOT_H_FILE;
    attacks |= (board << 17) & NOT_H_FILE;

    // east side attacks
    attacks |= (board << 6) & NOT_AB_FILE;
    attacks |= (board >> 10) & NOT_AB_FILE;
    attacks |= (board << 15) & NOT_A_FILE;
    attacks |= (board >> 17) & NOT_A_FILE;

    knight_attacks[i] = attacks;
  }
}
