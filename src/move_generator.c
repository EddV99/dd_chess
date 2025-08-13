#include "move_generator.h"

#include "attack.h"
#include "bitboard.h"
#include "board.h"
#include <stdio.h>

int generate_pseudo_legal_moves(board_t *board, move_t *moves) {
  if (board->is_white_turn)
    return generate_pseudo_legal_white_moves(board, moves);
  else
    return generate_pseudo_legal_black_moves(board, moves);
}

int generate_pseudo_legal_white_moves(board_t *board, move_t *moves) {
  move_t *tmp = moves;
  moves += generate_pseudo_legal_white_pawn_moves(board, moves);
  return moves - tmp;
}

int generate_pseudo_legal_black_moves(board_t *board, move_t *moves) {
  move_t *tmp = moves;
  moves += generate_pseudo_legal_black_pawn_moves(board, moves);
  return moves - tmp;
}

int generate_pseudo_legal_white_pawn_moves(board_t *board, move_t *moves) {
  move_t *tmp = moves;

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
    add_move(moves, move);
  }

  while (move_up_two) {
    move_t move = 0;
    square_t to = (square_t)least_significant_one_bit(move_up_two);
    set_move_from(move, to - 16);
    set_move_to(move, to);
    unset_least_significant_one_bit(move_up_two);
    add_move(moves, move);
  }

  while (white_pawns) {
    square_t from = (square_t)least_significant_one_bit(white_pawns);
    unset_least_significant_one_bit(white_pawns);
    // TODO: implement en passant
    bitboard_t attacks = pawn_attacks[WHITE][from] & (board->black_pieces | board->en_passant);

    if (!attacks)
      continue;
    square_t attack_to = (square_t)least_significant_one_bit(attacks);
    unset_least_significant_one_bit(attacks);
    move_t move = 0;
    set_move_from(move, from);
    set_move_to(move, attack_to);
    if (attack_to & RANK_8) {
      set_move_promotion(move);
    }
    add_move(moves, move);

    if (!attacks)
      continue;
    attack_to = (square_t)least_significant_one_bit(attacks);
    move = 0;
    set_move_from(move, from);
    set_move_to(move, attack_to);
    if (attack_to & RANK_8) {
      set_move_promotion(move);
    }
    add_move(moves, move);
  }

  return moves - tmp;
}

int generate_pseudo_legal_black_pawn_moves(board_t *board, move_t *moves) {
  move_t *tmp = moves;

  bitboard_t black_pawns = board->piece_bitboards[INDEX_BITBOARD(BLACK, PAWN)];
  bitboard_t other_pieces = board->all_pieces & ~black_pawns;

  bitboard_t move_up_one = (black_pawns >> 8) & ~other_pieces;
  bitboard_t move_up_two = ((move_up_one & RANK_6) >> 8) & ~other_pieces;

  while (move_up_one) {
    move_t move = 0;
    square_t to = (square_t)least_significant_one_bit(move_up_one);
    set_move_from(move, to + 8);
    set_move_to(move, to);

    if (to & RANK_1) {
      set_move_promotion(move);
    }

    unset_least_significant_one_bit(move_up_one);
    add_move(moves, move);
  }

  while (move_up_two) {
    move_t move = 0;
    square_t to = (square_t)least_significant_one_bit(move_up_two);
    set_move_from(move, to + 16);
    set_move_to(move, to);
    unset_least_significant_one_bit(move_up_two);
    add_move(moves, move);
  }

  while (black_pawns) {
    square_t from = (square_t)least_significant_one_bit(black_pawns);
    unset_least_significant_one_bit(black_pawns);
    // TODO: implement en passant
    bitboard_t attacks = pawn_attacks[BLACK][from] & (board->black_pieces | board->en_passant);

    if (!attacks)
      continue;
    square_t attack_to = (square_t)least_significant_one_bit(attacks);
    unset_least_significant_one_bit(attacks);
    move_t move = 0;
    set_move_from(move, from);
    set_move_to(move, attack_to);
    if (attack_to & RANK_1) {
      set_move_promotion(move);
    }
    add_move(moves, move);

    if (!attacks)
      continue;
    attack_to = (square_t)least_significant_one_bit(attacks);
    move = 0;
    set_move_from(move, from);
    set_move_to(move, attack_to);
    if (attack_to & RANK_1) {
      set_move_promotion(move);
    }
    add_move(moves, move);
  }

  return moves - tmp;
}

int generate_pseudo_legal_knight_moves(board_t *board, move_t *moves) {
  move_t *tmp = moves;
  print_board(board->piece_bitboards[INDEX_BITBOARD(WHITE, KNIGHT)]);
  return moves - tmp;
}

int generate_pseudo_legal_bishop_moves(board_t *board, move_t *moves) {
  move_t *tmp = moves;
  print_board(board->piece_bitboards[INDEX_BITBOARD(WHITE, BISHOP)]);
  return moves - tmp;
}

int generate_pseudo_legal_rook_moves(board_t *board, move_t *moves) {
  move_t *tmp = moves;
  print_board(board->piece_bitboards[INDEX_BITBOARD(WHITE, ROOK)]);
  return moves - tmp;
}

int generate_pseudo_legal_queen_moves(board_t *board, move_t *moves) {
  move_t *tmp = moves;
  print_board(board->piece_bitboards[INDEX_BITBOARD(WHITE, QUEEN)]);
  return moves - tmp;
}

int generate_pseudo_legal_king_moves(board_t *board, move_t *moves) {
  move_t *tmp = moves;
  print_board(board->piece_bitboards[INDEX_BITBOARD(WHITE, KING)]);
  return moves - tmp;
}
