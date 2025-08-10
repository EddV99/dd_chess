#ifndef DD_BOARD_H_
#define DD_BOARD_H_

#include "bitboard.h"

#include <stdint.h>

typedef struct {
  uint8_t is_white_turn;
  uint32_t rule50;
  // keep track of castle rights
  // bit 7: castle rights for white king side
  // bit 6: castle rights for white queen side
  // bit 5: castle rights for black king side
  // bit 4: castle rights for black queen side
  uint8_t castle_rights;
  // 64 bits represents the whole board.
  // bit 56-63: rank 8
  // bit 48-55: rank 7
  // bit 40-47: rank 6
  // bit 32-39: rank 5
  // bit 24-31: rank 4
  // bit 16-23: rank 3
  // bit 8-15:  rank 2
  // bit 0-7:   rank 1
  bitboard_t white_king;
  bitboard_t white_queen;
  bitboard_t white_rooks;
  bitboard_t white_bishops;
  bitboard_t white_knights;
  bitboard_t white_pawns;
  bitboard_t black_king;
  bitboard_t black_queen;
  bitboard_t black_rooks;
  bitboard_t black_bishops;
  bitboard_t black_knights;
  bitboard_t black_pawns;
} board_t;

board_t create_new_board();

#endif
