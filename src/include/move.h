#ifndef DD_MOVE_H_
#define DD_MOVE_H_

#include "common.h"
#include <stdint.h>

#define unset_move_capture(move) (move = (move & 0b000111111111111111111))

#define set_move_old_en_passant_square(move, square) (move = (move & 0b000000111111111111111111111) | ((uint16_t)(square)) << 21)
#define set_move_capture(move, piece) (move = (move & 0b111111000111111111111111111) | ((piece + 1) << 18))
#define set_move_castle_east(move) (move = (move & 0b111111111001111111111111111) | (EAST << 16))
#define set_move_castle_west(move) (move = (move & 0b111111111001111111111111111) | (WEST << 16))
#define set_move_en_passant(move) (move |= (1 << 15))
#define set_move_promotion_knight(move) (move = (move & 0b111111111111000111111111111) | ((uint16_t)KNIGHT << 12))
#define set_move_promotion_bishop(move) (move = (move & 0b111111111111000111111111111) | ((uint16_t)BISHOP << 12))
#define set_move_promotion_rook(move) (move = (move & 0b111111111111000111111111111) | ((uint16_t)ROOK << 12))
#define set_move_promotion_queen(move) (move = (move & 0b111111111111000111111111111) | ((uint16_t)QUEEN << 12))
#define set_move_to(move, square) (move = (move & 0b111111111111111000000111111) | ((uint16_t)square) << 6)
#define set_move_from(move, square) (move = (move & 0b111111111111111111111000000) | ((uint16_t)square))

#define get_move_old_en_passant_square(move) (((move & 0b111111000000000000000000000) >> 21))
#define get_move_capture(move) (((move & 0b000000111000000000000000000) >> 18) - 1)
#define get_move_castle(move) ((move & 0b000000000110000000000000000) >> 16)
#define get_move_en_passant(move) (move & (1 << 15))
#define get_move_promotion(move) ((move & 0b000000000000111000000000000) >> 12)
#define get_move_to(move) ((square_t)((move & 0b000000000000000111111000000) >> 6))
#define get_move_from(move) ((square_t)(move & 0b000000000000000000000111111))

/*
 * 32 bits to represent a move.
 * old en_passant square  capture  castle   en passant  promotion  to        from
 * [26-21]                [20-18]  [17-16]  [15]        [14-12]    [11 - 6]  [5 - 0]
 *
 * use capture bits for undoing a move
 * use old en passant square for undoing a move
 */
typedef uint32_t move_t;

#endif
