#ifndef DD_MOVE_H_
#define DD_MOVE_H_

#include "common.h"
#include <stdint.h>

#define set_move_capture(move) (move |= (1 << 12))
#define set_move_promotion(move) (move |= (1 << 13))
#define set_move_en_passant(move) (move |= (1 << 14))
#define set_move_from(move, square) (move = (move & 0b1111111111000000) | ((uint16_t)square))
#define set_move_to(move, square) (move = (move & 0b1111000000111111) | ((uint16_t)square) << 6)

#define get_move_capture(move) (move & (1 << 12))
#define get_move_promotion(move) (move & (1 << 13))
#define get_move_en_passant(move) (move & (1 << 14))
#define get_move_from(move) ((square_t)(move & 0b0000000000111111))
#define get_move_to(move) ((square_t)((move & 0b0000111111000000) >> 6))

/*
 * 16 bits needed to represent a move.
 * en passant  promotion  capture  to        from
 * [14]        [13]       [12]     [11 - 6]  [5 - 0]
 */
typedef uint16_t move_t;

#endif
