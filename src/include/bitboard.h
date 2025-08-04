#ifndef DD_BIT_BOARD_H_
#define DD_BIT_BOARD_H_

#include <stdint.h>

#define square_mask(square) (1ULL << square)
#define get_bit(bitboard, square) (bitboard & square_mask(square))
#define set_bit(bitboard, square) (bitboard |= square_mask(square))
#define unset_bit(bitboard, square) (bitboard &= ~square_mask(square))

typedef uint64_t bitboard_t;

void print_board(bitboard_t bitboard);

#endif
