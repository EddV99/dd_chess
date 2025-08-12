#ifndef DD_BOARD_H_
#define DD_BOARD_H_

#include "bitboard.h"

#include <stdint.h>

#define INDEX_BITBOARD(color, piece) piece + (color * 6)

typedef struct {
  uint8_t is_white_turn;
  uint32_t rule50;
  // keep track of castle rights
  // bit 7: castle rights for white king side
  // bit 6: castle rights for white queen side
  // bit 5: castle rights for black king side
  // bit 4: castle rights for black queen side
  uint8_t castle_rights;

  bitboard_t piece_bitboards[12];
  bitboard_t black_pieces;
  bitboard_t white_pieces;
} board_t;

board_t create_new_board();

#endif
