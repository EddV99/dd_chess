#ifndef DD_MOVE_GENERATOR_H_
#define DD_MOVE_GENERATOR_H_
#include "move.h"

#include "board.h"

#define MAX_MOVES 254
#define add_move(moves, move)                                                                                          \
  *moves = move;                                                                                                       \
  (moves)++;

int generate_pseudo_legal_moves(board_t *board, move_t *moves);
int generate_pseudo_legal_white_moves(board_t *board, move_t *moves);
int generate_pseudo_legal_black_moves(board_t *board, move_t *moves);

int generate_pseudo_legal_white_pawn_moves(board_t *board, move_t *moves);
int generate_pseudo_legal_black_pawn_moves(board_t *board, move_t *moves);

int generate_pseudo_legal_knight_moves(board_t *board, move_t *moves);
int generate_pseudo_legal_bishop_moves(board_t *board, move_t *moves);
int generate_pseudo_legal_rook_moves(board_t *board, move_t *moves);
int generate_pseudo_legal_queen_moves(board_t *board, move_t *moves);
int generate_pseudo_legal_king_moves(board_t *board, move_t *moves);

#endif
