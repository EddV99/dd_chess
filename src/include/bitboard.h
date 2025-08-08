#ifndef DD_BIT_BOARD_H_
#define DD_BIT_BOARD_H_

#include <stdint.h>

#define square_mask(square) (1ULL << square)
#define get_bit(bitboard, square) (bitboard & square_mask(square))
#define set_bit(bitboard, square) (bitboard |= square_mask(square))
#define unset_bit(bitboard, square) (bitboard &= ~square_mask(square))
#define toggle_bit(bitboard, square) (bitboard ^= square_mask(square))
#define file_rank_to_square(file, rank) ((rank * 8) + file)

/*
 * Use 64 bits to represent a board. Layout of bits is as shown below:
 *
 * 8  (MSB) 0 0 0 0 0 0 0 0
 * 7        0 0 0 0 0 0 0 0
 * 6        0 0 0 0 0 0 0 0
 * 5        0 0 0 0 0 0 0 0
 * 4        0 0 0 0 0 0 0 0
 * 3        0 0 0 0 0 0 0 0
 * 2        0 0 0 0 0 0 0 0
 * 1        0 0 0 0 0 0 0 0 (LSB)
 *
 *          A B C D E F G H
 */
typedef uint64_t bitboard_t;

void print_board(bitboard_t bitboard);
int population_count(bitboard_t bitboard);

#endif
