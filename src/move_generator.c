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
  moves += generate_pseudo_legal_pawn_moves(board, moves, WHITE);
  moves += generate_pseudo_legal_knight_moves(board, moves, WHITE, ~board->white_pieces);
  moves += generate_pseudo_legal_bishop_moves(board, moves, WHITE);
  moves += generate_pseudo_legal_rook_moves(board, moves, WHITE);
  moves += generate_pseudo_legal_queen_moves(board, moves, WHITE);
  return moves - tmp;
}

int generate_pseudo_legal_black_moves(board_t *board, move_t *moves) {
  move_t *tmp = moves;
  moves += generate_pseudo_legal_pawn_moves(board, moves, BLACK);
  moves += generate_pseudo_legal_knight_moves(board, moves, BLACK, ~board->black_pieces);
  moves += generate_pseudo_legal_bishop_moves(board, moves, BLACK);
  moves += generate_pseudo_legal_rook_moves(board, moves, BLACK);
  moves += generate_pseudo_legal_queen_moves(board, moves, BLACK);
  return moves - tmp;
}

int generate_pseudo_legal_pawn_moves(board_t *board, move_t *moves, piece_color_t color) {
  move_t *tmp = moves;

  bitboard_t pawns = board->piece_bitboards[INDEX_BITBOARD(color, PAWN)];
  bitboard_t other_pieces = board->all_pieces & ~pawns;
  int dir = color == WHITE ? SHIFT_LEFT : SHIFT_RIGHT;
  bitboard_t promotion_rank = color == WHITE ? RANK_8 : RANK_1;

  bitboard_t move_up_one = shift(dir, pawns, 8) & ~other_pieces;
  bitboard_t move_up_two =
      shift(dir, color == WHITE ? (move_up_one & RANK_3) : (move_up_one & RANK_6), 8) & ~other_pieces;

  while (move_up_one) {
    move_t move = 0;
    square_t to = (square_t)least_significant_one_bit(move_up_one);
    unset_least_significant_one_bit(move_up_one);

    set_move_from(move, to + (8 * dir));
    set_move_to(move, to);

    if (square_mask(to) & promotion_rank) {
      add_move_promotion(moves, move);
    } else {
      add_move(moves, move);
    }
  }

  while (move_up_two) {
    move_t move = 0;
    square_t to = (square_t)least_significant_one_bit(move_up_two);
    set_move_from(move, to + (16 * dir));
    set_move_to(move, to);
    unset_least_significant_one_bit(move_up_two);
    add_move(moves, move);
  }

  while (pawns) {
    square_t from = (square_t)least_significant_one_bit(pawns);
    unset_least_significant_one_bit(pawns);
    // TODO: implement en passant
    bitboard_t attacks =
        pawn_attacks[color][from] & ((color == WHITE ? board->black_pieces : board->white_pieces) | board->en_passant);

    if (!attacks)
      continue;
    square_t attack_to = (square_t)least_significant_one_bit(attacks);
    unset_least_significant_one_bit(attacks);
    move_t move = 0;
    set_move_from(move, from);
    set_move_to(move, attack_to);
    if (square_mask(attack_to) & promotion_rank) {
      add_move_promotion(moves, move);
    } else {
      add_move(moves, move);
    }

    if (!attacks)
      continue;
    attack_to = (square_t)least_significant_one_bit(attacks);
    move = 0;
    set_move_from(move, from);
    set_move_to(move, attack_to);
    if (square_mask(attack_to) & promotion_rank) {
      add_move_promotion(moves, move);
    } else {
      add_move(moves, move);
    }
  }

  return moves - tmp;
}

int generate_pseudo_legal_knight_moves(board_t *board, move_t *moves, piece_color_t color,
                                       bitboard_t can_move_to_mask) {
  move_t *tmp = moves;

  bitboard_t knights = board->piece_bitboards[INDEX_BITBOARD(color, KNIGHT)];

  while (knights) {
    square_t from = (square_t)least_significant_one_bit(knights);
    unset_least_significant_one_bit(knights);

    bitboard_t attacks = knight_attacks[from] & can_move_to_mask;
    while (attacks) {
      square_t to = (square_t)least_significant_one_bit(attacks);
      unset_least_significant_one_bit(attacks);
      move_t move = 0;
      set_move_from(move, from);
      set_move_to(move, to);
      add_move(moves, move);
    }
  }

  return moves - tmp;
}

int generate_pseudo_legal_slider_moves(board_t *board, move_t *moves, piece_color_t color, pieces_t piece,
                                       bitboard_t occupancy_mask) {
  move_t *tmp = moves;

  bitboard_t pieces = board->piece_bitboards[INDEX_BITBOARD(color, piece)];

  while (pieces) {
    square_t from = (square_t)least_significant_one_bit(pieces);
    unset_least_significant_one_bit(pieces);

    bitboard_t attacks = 0ULL;
    bitboard_t can_attack_mask = (color == WHITE ? ~board->white_pieces : ~board->black_pieces);
    switch (piece) {
    case BISHOP:
      attacks = get_bishop_attacks(from, occupancy_mask) & can_attack_mask;
      break;
    case ROOK:
      attacks = get_rook_attacks(from, occupancy_mask) & can_attack_mask;
      break;
    case QUEEN:
      attacks = get_queen_attacks(from, occupancy_mask) & can_attack_mask;
      break;
    default:
    }
    while (attacks) {
      square_t to = (square_t)least_significant_one_bit(attacks);
      unset_least_significant_one_bit(attacks);

      if (color == WHITE && (board->white_pieces & square_mask(to))) {
        continue;
      }
      if (color == BLACK && (board->black_pieces & square_mask(to))) {
        continue;
      }

      move_t move = 0;
      set_move_from(move, from);
      set_move_to(move, to);
      add_move(moves, move);
    }
  }

  return moves - tmp;
}

int generate_pseudo_legal_bishop_moves(board_t *board, move_t *moves, piece_color_t color) {
  return generate_pseudo_legal_slider_moves(board, moves, color, BISHOP, board->all_pieces);
}

int generate_pseudo_legal_rook_moves(board_t *board, move_t *moves, piece_color_t color) {
  return generate_pseudo_legal_slider_moves(board, moves, color, ROOK, board->all_pieces);
}

int generate_pseudo_legal_queen_moves(board_t *board, move_t *moves, piece_color_t color) {
  return generate_pseudo_legal_slider_moves(board, moves, color, QUEEN, board->all_pieces);
}

int generate_pseudo_legal_king_moves(board_t *board, move_t *moves) {
  move_t *tmp = moves;
  print_board(board->piece_bitboards[INDEX_BITBOARD(WHITE, KING)]);
  return moves - tmp;
}
