#include "move_generator.h"

#include "bitboard.h"
#include "common.h"
#include "magic.h"

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

bitboard_t king_attacks[SQUARE_COUNT] = {0};

void generate_king_attacks() {
  for (int i = 0; i < SQUARE_COUNT; i++) {
    bitboard_t board = 0;
    set_bit(board, i);

    bitboard_t attacks = (board << 1) & NOT_H_FILE;
    attacks |= (board << 9) & NOT_H_FILE;
    attacks |= (board << 8);
    attacks |= (board << 7) & NOT_A_FILE;
    attacks |= (board >> 1) & NOT_A_FILE;
    attacks |= (board >> 9) & NOT_A_FILE;
    attacks |= (board >> 8);
    attacks |= (board >> 7) & NOT_H_FILE;

    king_attacks[i] = attacks;
  }
}

uint64_t bishop_occupancy_masks[64] = {0};
uint64_t bishop_attacks[SQUARE_COUNT][512] = {0};

uint64_t rook_occupancy_masks[64] = {0};
uint64_t rook_attacks[SQUARE_COUNT][4096] = {0};

void generate_slider_attacks() {
  for (int sq = 0; sq < SQUARE_COUNT; sq++) {
    bishop_occupancy_masks[sq] = bishop_occupancy(sq);
    bitboard_t occupancy_mask = bishop_occupancy_masks[sq];
    int bit_count = population_count(occupancy_mask);
    int occupancy_indices = 1 << bit_count;
    for (int i = 0; i < occupancy_indices; i++) {
      bitboard_t occupancy = set_occupancy(i, bit_count, occupancy_mask);
      int magic_index = (occupancy * BISHOP_MAGICS[sq]) >> (64 - bishop_occupancy_count[sq]);
      bishop_attacks[sq][magic_index] = generate_bishop_attack(sq, occupancy);
    }

    rook_occupancy_masks[sq] = rook_occupancy(sq);
    occupancy_mask = rook_occupancy_masks[sq];
    bit_count = population_count(occupancy_mask);
    occupancy_indices = 1 << bit_count;
    for (int i = 0; i < occupancy_indices; i++) {
      bitboard_t occupancy = set_occupancy(i, bit_count, occupancy_mask);
      int magic_index = (occupancy * ROOK_MAGICS[sq]) >> (64 - rook_occupancy_count[sq]);
      rook_attacks[sq][magic_index] = generate_rook_attack(sq, occupancy);
    }
  }
}

bitboard_t get_bishop_attacks(square_t square, bitboard_t occupancy) {
  occupancy &= bishop_occupancy(square);
  occupancy *= BISHOP_MAGICS[square];
  occupancy >>= 64 - bishop_occupancy_count[square];
  return bishop_attacks[square][occupancy];
}

bitboard_t get_rook_attacks(square_t square, bitboard_t occupancy) {
  occupancy &= rook_occupancy(square);
  occupancy *= ROOK_MAGICS[square];
  occupancy >>= 64 - rook_occupancy_count[square];
  return rook_attacks[square][occupancy];
}
bitboard_t get_queen_attacks(square_t square, bitboard_t occupancy) {
  return get_rook_attacks(square, occupancy) | get_bishop_attacks(square, occupancy);
}

void init_attacks() {
  generate_pawn_attacks();
  generate_knight_attacks();
  generate_king_attacks();
  generate_slider_attacks();
}
