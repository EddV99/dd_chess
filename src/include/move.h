#ifndef DD_MOVE_H_
#define DD_MOVE_H_

#include "common.h"
#include <stdint.h>

#define unset_move_capture(move) (move = (move & 0b1111111111000111111111111111111))

#define set_move_castle_rights(move, rights) ((move) = ((move) & 0b0000111111111111111111111111111) | ((rights) << 27))
#define set_move_en_passant_mask(move, square)                                                                         \
  ((move) = ((move) & 0b1111000000111111111111111111111) | ((square) << 21))
#define set_move_capture(move, piece) ((move) = ((move) & 0b1111111111000111111111111111111) | (((piece) + 1) << 18))
#define set_move_castle_east(move) ((move) = ((move) & 0b1111111111111001111111111111111) | (EAST << 16))
#define set_move_castle_west(move) ((move) = ((move) & 0b1111111111111001111111111111111) | (WEST << 16))
#define set_move_en_passant(move) ((move) |= (1 << 15))
#define set_move_promotion_knight(move) ((move) = ((move) & 0b1111111111111111000111111111111) | (KNIGHT << 12))
#define set_move_promotion_bishop(move) ((move) = ((move) & 0b1111111111111111000111111111111) | (BISHOP << 12))
#define set_move_promotion_rook(move) ((move) = ((move) & 0b1111111111111111000111111111111) | (ROOK << 12))
#define set_move_promotion_queen(move) ((move) = ((move) & 0b1111111111111111000111111111111) | (QUEEN << 12))
#define set_move_to(move, square) ((move) = ((move) & 0b1111111111111111111000000111111) | (square) << 6)
#define set_move_from(move, square) ((move) = ((move) & 0b1111111111111111111111111000000) | (square))

#define get_move_castle_rights(move) (((move) & 0b1111000000000000000000000000000) >> 27)
#define get_move_en_passant_mask(move) (((move) & 0b0000111111000000000000000000000) >> 21)
#define get_move_capture(move) ((((move) & 0b0000000000111000000000000000000) >> 18) - 1)
#define get_move_castle(move) (((move) & 0b0000000000000110000000000000000) >> 16)
#define get_move_en_passant(move) (((move) & 0b0000000000000001000000000000000) >> 15)
#define get_move_promotion(move) (((move) & 0b0000000000000000111000000000000) >> 12)
#define get_move_to(move) ((square_t)(((move) & 0b0000000000000000000111111000000) >> 6))
#define get_move_from(move) ((square_t)((move) & 0b0000000000000000000000000111111))

/*
 * 32 bits to represent a move.
 * castle rights  en_passant mask  capture  castle   en passant  promotion  to        from
 * [30-27]        [26-21]          [20-18]  [17-16]  [15]        [14-12]    [11 - 6]  [5 - 0]
 *
 * Also save castle rights, en_passant mask, and capture info for undo purposes
 */
typedef uint32_t move_t;

#endif
