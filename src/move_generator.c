#include "move_generator.h"

#include "attack.h"
#include "bitboard.h"
#include "board.h"
#include <stdio.h>

int generate_pseudo_legal_white_moves(board_t *board, move_t *moves) { return -1; }

int generate_pseudo_legal_black_moves(board_t *board, move_t *moves) { return -1; }

int generate_pseudo_legal_pawn_moves(board_t *board, move_t *moves) {
  bitboard_t white_pawns = board->piece_bitboards[INDEX_BITBOARD(WHITE, PAWN)];
  bitboard_t other_pieces = board->all_pieces & ~white_pawns;

  bitboard_t move_up_one = (white_pawns << 8) & ~other_pieces;
  bitboard_t move_up_two = ((move_up_one & RANK_3) << 8) & ~other_pieces;

  while (move_up_one) {
    move_t move = 0;
    square_t to = (square_t)least_significant_one_bit(move_up_one);
    set_move_from(move, to - 8);
    set_move_to(move, to);

    if (to & RANK_8) {
      set_move_promotion(move);
    }

    unset_least_significant_one_bit(move_up_one);
    ADD_MOVE(moves, move);
  }

  while (move_up_two) {
    move_t move = 0;
    square_t to = (square_t)least_significant_one_bit(move_up_two);
    set_move_from(move, to - 16);
    set_move_to(move, to);
    unset_least_significant_one_bit(move_up_two);
    ADD_MOVE(moves, move);
  }

  return -1;
}
int generate_pseudo_legal_knight_moves(board_t *board, move_t *moves) { return -1; }
int generate_pseudo_legal_bishop_moves(board_t *board, move_t *moves) { return -1; }
int generate_pseudo_legal_rook_moves(board_t *board, move_t *moves) { return -1; }
int generate_pseudo_legal_queen_moves(board_t *board, move_t *moves) { return -1; }
int generate_pseudo_legal_king_moves(board_t *board, move_t *moves) { return -1; }
