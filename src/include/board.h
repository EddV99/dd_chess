#ifndef DD_BOARD_H_
#define DD_BOARD_H_

#include "bitboard.h"
#include "move.h"

#include <stdint.h>

#define move_piece(bitboard, from, to)                                                                                 \
  unset_bit(bitboard, from);                                                                                           \
  set_bit(bitboard, to);

#define move_piece_sync(board, from, to, piece, color)                                                                 \
  bitboard_t *move_color_board = color == WHITE ? &board->white_pieces : &board->black_pieces;                         \
  bitboard_t *move_piece_board = &board->piece_bitboards[index_color_piece(color, piece)];                             \
  move_piece(*move_color_board, from, to);                                                                             \
  move_piece(board->all_pieces, from, to);                                                                             \
  move_piece(*move_piece_board, from, to);                                                                             \
  board->pieces[from] = EMPTY;                                                                                         \
  board->pieces[to] = piece;

#define remove_piece_sync(board, square, piece, color)                                                                 \
  bitboard_t *remove_color_board = color == WHITE ? &board->white_pieces : &board->black_pieces;                       \
  bitboard_t *remove_piece_board = &board->piece_bitboards[index_color_piece(color, piece)];                           \
  unset_bit(*remove_color_board, square);                                                                              \
  unset_bit(board->all_pieces, square);                                                                                \
  unset_bit(*remove_piece_board, square);                                                                              \
  board->pieces[square] = EMPTY;

#define add_piece_sync(board, square, piece, color)                                                                    \
  bitboard_t *add_color_board = color == WHITE ? &board->white_pieces : &board->black_pieces;                          \
  bitboard_t *add_piece_board = &board->piece_bitboards[index_color_piece(color, piece)];                              \
  set_bit(*add_color_board, square);                                                                                   \
  set_bit(board->all_pieces, square);                                                                                  \
  set_bit(*add_piece_board, square);                                                                                   \
  board->pieces[square] = piece;

#define set_castle_rights_nw(rights) ((rights) |= (1 << 0))
#define set_castle_rights_ne(rights) ((rights) |= (1 << 1))
#define set_castle_rights_sw(rights) ((rights) |= (1 << 2))
#define set_castle_rights_se(rights) ((rights) |= (1 << 3))
#define unset_castle_rights_nw(rights) ((rights) &= 0b11111110)
#define unset_castle_rights_ne(rights) ((rights) &= 0b11111101)
#define unset_castle_rights_sw(rights) ((rights) &= 0b11111011)
#define unset_castle_rights_se(rights) ((rights) &= 0b11110111)
#define get_castle_rights_nw(rights) (rights & 0b00000001)
#define get_castle_rights_ne(rights) (rights & 0b00000010)
#define get_castle_rights_sw(rights) (rights & 0b00000100)
#define get_castle_rights_se(rights) (rights & 0b00001000)

typedef struct {
  color_t turn_color;
  uint32_t rule50;
  // keep track of castle rights
  // bit 3: castle rights for white king side (South East)
  // bit 2: castle rights for white queen side (South West)
  // bit 1: castle rights for black king side (North East)
  // bit 0: castle rights for black queen side (North West)
  uint8_t castle_rights;

  piece_t pieces[SQUARE_COUNT];
  bitboard_t piece_bitboards[12];
  bitboard_t all_pieces;
  bitboard_t en_passant;
  bitboard_t black_pieces;
  bitboard_t white_pieces;
} board_t;

board_t create_new_board();
board_t load_fen(const char *fen);
void make_move(board_t *board, move_t *move);
void unmake_move(board_t *board, move_t move);
void print_board(board_t *board);

board_t copy_board(const board_t *board);
int board_equals(board_t *b1, board_t *b2);

#endif
