#ifndef DD_MOVE_GENERATOR_H_
#define DD_MOVE_GENERATOR_H_
#include "move.h"

#include "board.h"

#define MAX_MOVES 254
#define add_move(moves, move)                                                                                          \
  *moves = move;                                                                                                       \
  (moves)++;
#define add_move_promotion(moves, move)                                                                                \
  set_move_promotion_knight(move);                                                                                     \
  add_move(moves, move);                                                                                               \
  set_move_promotion_bishop(move);                                                                                     \
  add_move(moves, move);                                                                                               \
  set_move_promotion_rook(move);                                                                                       \
  add_move(moves, move);                                                                                               \
  set_move_promotion_queen(move);                                                                                      \
  add_move(moves, move);

int generate_pseudo_legal_moves(board_t *board, move_t *moves);
int generate_pseudo_legal_white_moves(board_t *board, move_t *moves);
int generate_pseudo_legal_black_moves(board_t *board, move_t *moves);

int generate_pseudo_legal_pawn_moves(board_t *board, move_t *moves, color_t color);
int generate_pseudo_legal_knight_moves(board_t *board, move_t *moves, color_t color, bitboard_t can_move_to_mask);
int generate_pseudo_legal_slider_moves(board_t *board, move_t *moves, color_t color, pieces_t piece,
                                       bitboard_t occupancy_mask);
int generate_pseudo_legal_bishop_moves(board_t *board, move_t *moves, color_t color);
int generate_pseudo_legal_rook_moves(board_t *board, move_t *moves, color_t color);
int generate_pseudo_legal_queen_moves(board_t *board, move_t *moves, color_t color);
int generate_pseudo_legal_king_moves(board_t *board, move_t *moves, color_t color, bitboard_t can_move_to_mask);

int is_square_attacked(board_t *board, square_t square, color_t attacker_color);
int is_king_in_check(board_t *board, color_t color);

#endif
