#ifndef DD_MOVE_H_
#define DD_MOVE_H_

#include "common.h"
#include <stdint.h>

#define set_move_en_passant(move) (move |= (1 << 15))
#define set_move_promotion_knight(move) (move = (move & 0b1000111111111111) | ((uint16_t)KNIGHT << 12))
#define set_move_promotion_bishop(move) (move = (move & 0b1000111111111111) | ((uint16_t)BISHOP << 12))
#define set_move_promotion_rook(move) (move = (move & 0b1000111111111111) | ((uint16_t)ROOK << 12))
#define set_move_promotion_queen(move) (move = (move & 0b1000111111111111) | ((uint16_t)QUEEN << 12))
#define set_move_to(move, square) (move = (move & 0b1111000000111111) | ((uint16_t)square) << 6)
#define set_move_from(move, square) (move = (move & 0b1111111111000000) | ((uint16_t)square))

#define get_move_promotion(move) ((move & 0b0111000000000000) >> 12)
#define get_move_en_passant(move) (move & (1 << 15))
#define get_move_from(move) ((square_t)(move & 0b0000000000111111))
#define get_move_to(move) ((square_t)((move & 0b0000111111000000) >> 6))

/*
 * 16 bits needed to represent a move.
 * en passant  promotion  to        from
 * [15]        [14-12]    [11 - 6]  [5 - 0]
 */
typedef uint16_t move_t;

#endif
