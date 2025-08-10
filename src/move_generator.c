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

bitboard_t rook_occupancy(square_t square) {
  bitboard_t result = 0ULL;
  int rank = square / 8;
  int file = square % 8;
  int r, f;
  for (r = rank + 1; r < 7; r++)
    set_bit(result, file_rank_to_square(file, r));
  for (r = rank - 1; r > 0; r--)
    set_bit(result, file_rank_to_square(file, r));
  for (f = file + 1; f < 7; f++)
    set_bit(result, file_rank_to_square(f, rank));
  for (f = file - 1; f > 0; f--)
    set_bit(result, file_rank_to_square(f, rank));
  return result;
}

void get_rook_moves(magic_t magic, bitboard_t blockers) {}

bitboard_t bishop_occupancy(square_t square) {
  bitboard_t result = 0ULL;
  int rank = square / 8;
  int file = square % 8;
  int r, f;
  for (r = rank + 1, f = file + 1; r < 7 && f < 7; r++, f++)
    set_bit(result, file_rank_to_square(f, r));
  for (r = rank + 1, f = file - 1; r < 7 && f > 0; r++, f--)
    set_bit(result, file_rank_to_square(f, r));
  for (r = rank - 1, f = file + 1; r > 0 && f < 7; r--, f++)
    set_bit(result, file_rank_to_square(f, r));
  for (r = rank - 1, f = file - 1; r > 0 && f > 0; r--, f--)
    set_bit(result, file_rank_to_square(f, r));
  return result;
}

bitboard_t generate_bishop_attack(square_t square, bitboard_t blockers) {
  bitboard_t result = 0ULL;
  int rank = square / 8;
  int file = square % 8;
  int r, f;
  for (r = rank + 1, f = file + 1; r <= 7 && f <= 7; r++, f++) {
    set_bit(result, file_rank_to_square(f, r));
    if (square_mask(file_rank_to_square(f, r)) & blockers)
      break;
  }
  for (r = rank + 1, f = file - 1; r <= 7 && f >= 0; r++, f--) {
    set_bit(result, file_rank_to_square(f, r));
    if (square_mask(file_rank_to_square(f, r)) & blockers)
      break;
  }
  for (r = rank - 1, f = file + 1; r >= 0 && f <= 7; r--, f++) {
    set_bit(result, file_rank_to_square(f, r));
    if (square_mask(file_rank_to_square(f, r)) & blockers)
      break;
  }
  for (r = rank - 1, f = file - 1; r >= 0 && f >= 0; r--, f--) {
    set_bit(result, file_rank_to_square(f, r));
    if (square_mask(file_rank_to_square(f, r)) & blockers)
      break;
  }
  return result;
}

bitboard_t generate_rook_attack(square_t square, bitboard_t blockers) {
  bitboard_t result = 0ULL;
  int rank = square / 8;
  int file = square % 8;
  int r, f;
  for (r = rank + 1; r <= 7; r++) {
    set_bit(result, file_rank_to_square(file, r));
    if (square_mask(file_rank_to_square(file, r)) & blockers)
      break;
  }
  for (r = rank - 1; r >= 0; r--) {
    set_bit(result, file_rank_to_square(file, r));
    if (square_mask(file_rank_to_square(file, r)) & blockers)
      break;
  }
  for (f = file + 1; f <= 7; f++) {
    set_bit(result, file_rank_to_square(f, rank));
    if (square_mask(file_rank_to_square(f, rank)) & blockers)
      break;
  }
  for (f = file - 1; f >= 0; f--) {
    set_bit(result, file_rank_to_square(f, rank));
    if (square_mask(file_rank_to_square(f, rank)) & blockers)
      break;
  }
  return result;
}

bitboard_t set_occupancy(int index, int bit_count, bitboard_t attack_mask) {
  bitboard_t occupancy = 0ULL;
  
  for(int i = 0; i < bit_count; i++){
    square_t square = least_significant_one_bit(attack_mask); 
    unset_bit(attack_mask, square);

    if(index & (1 << i)){
      occupancy |= (1ULL << square);
    }
  }

  return occupancy;
}
