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

static const int lsb_index[64] = {0,  47, 1,  56, 48, 27, 2,  60, 57, 49, 41, 37, 28, 16, 3,  61, 54, 58, 35, 52, 50, 42,
                                21, 44, 38, 32, 29, 23, 17, 11, 4,  62, 46, 55, 26, 59, 40, 36, 15, 53, 34, 51, 20, 43,
                                31, 22, 10, 45, 25, 39, 14, 33, 19, 30, 9,  24, 13, 18, 8,  12, 7,  6,  5,  63};
/**
 * @author Kim Walisch (2012)
 */
int least_significant_one_bit(uint64_t bitboard);
#endif
