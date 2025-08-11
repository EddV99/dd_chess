#ifndef DD_MAGIC_H_
#define DD_MAGIC_H_

#include "bitboard.h"
#include "common.h"
#include "prng.h"

extern const int rook_occupancy_count[SQUARE_COUNT];
bitboard_t rook_occupancy(square_t square);
bitboard_t generate_rook_attack(square_t square, bitboard_t blockers);

extern const int bishop_occupancy_count[SQUARE_COUNT];
bitboard_t bishop_occupancy(square_t square);
bitboard_t generate_bishop_attack(square_t square, bitboard_t blockers);

bitboard_t set_occupancy(int index, int bit_count, bitboard_t attack_mask);

bitboard_t generate_magic_number(prng_t *prng);
bitboard_t find_magic_number(square_t square, int bit_count, pieces_t piece, prng_t* prng);
void init_magic();

#endif
