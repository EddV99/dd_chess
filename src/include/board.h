#ifndef DD_BOARD_H_
#define DD_BOARD_H_

#include "bitboard.h"
#include "move.h"

#include <stdint.h>

#define INDEX_BITBOARD(color, piece) (piece) + ((color) * 6)
#define move_piece(bitboard, from, to)                                                                                 \
  unset_bit(bitboard, from);                                                                                           \
  set_bit(bitboard, to);

#define set_castle_rights_nw(rights) (rights |= 1 << 0)
#define set_castle_rights_ne(rights) (rights |= 1 << 1)
#define set_castle_rights_sw(rights) (rights |= 1 << 2)
#define set_castle_rights_se(rights) (rights |= 1 << 3)
#define unset_castle_rights_nw(rights) (rights &= 0b11111110)
#define unset_castle_rights_ne(rights) (rights &= 0b11111101)
#define unset_castle_rights_sw(rights) (rights &= 0b11111011)
#define unset_castle_rights_se(rights) (rights &= 0b11110111)
#define get_castle_rights_nw(rights) (rights & 0b00000001)
#define get_castle_rights_ne(rights) (rights & 0b00000010)
#define get_castle_rights_sw(rights) (rights & 0b00000100)
#define get_castle_rights_se(rights) (rights & 0b00001000)

typedef struct {
  uint8_t is_white_turn;
  uint32_t rule50;
  // keep track of castle rights
  // bit 3: castle rights for white king side (South East)
  // bit 2: castle rights for white queen side (South West)
  // bit 1: castle rights for black king side (North East)
  // bit 0: castle rights for black queen side (North West)
  uint8_t castle_rights;

  int pieces[SQUARE_COUNT];
  bitboard_t piece_bitboards[12];
  bitboard_t all_pieces;
  bitboard_t en_passant;
  bitboard_t black_pieces;
  bitboard_t white_pieces;
} board_t;

board_t create_new_board();
void make_move(board_t *board, move_t move);
void unmake_move(board_t *board, move_t move);

#endif
