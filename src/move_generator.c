#include "move_generator.h"

#include "attack.h"
#include "bitboard.h"
#include "board.h"
#include <stdio.h>

int generate_pseudo_legal_moves(board_t *board, move_t *moves) {
  if (board->turn_color == WHITE)
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
  moves += generate_pseudo_legal_king_moves(board, moves, WHITE, ~board->white_pieces);
  return moves - tmp;
}

int generate_pseudo_legal_black_moves(board_t *board, move_t *moves) {
  move_t *tmp = moves;
  moves += generate_pseudo_legal_pawn_moves(board, moves, BLACK);
  moves += generate_pseudo_legal_knight_moves(board, moves, BLACK, ~board->black_pieces);
  moves += generate_pseudo_legal_bishop_moves(board, moves, BLACK);
  moves += generate_pseudo_legal_rook_moves(board, moves, BLACK);
  moves += generate_pseudo_legal_queen_moves(board, moves, BLACK);
  moves += generate_pseudo_legal_king_moves(board, moves, BLACK, ~board->black_pieces);
  return moves - tmp;
}

int generate_pseudo_legal_pawn_moves(board_t *board, move_t *moves, color_t color) {
  move_t *tmp = moves;

  bitboard_t pawns = board->piece_bitboards[index_color_piece(color, PAWN)];
  bitboard_t other_pieces = board->all_pieces;
  int dir = color == WHITE ? SHIFT_LEFT : SHIFT_RIGHT;
  bitboard_t promotion_rank = color == WHITE ? RANK_8 : RANK_1;

  bitboard_t move_up_one = 0ULL;
  bitboard_t move_up_two = 0ULL;

  if (color == WHITE) {
    move_up_one = (pawns << 8) & ~other_pieces;
    move_up_two = ((move_up_one & RANK_3) << 8) & ~other_pieces;
  } else {
    move_up_one = (pawns >> 8) & ~other_pieces;
    move_up_two = ((move_up_one & RANK_6) >> 8) & ~other_pieces;
  }

  while (move_up_one) {
    move_t move = 0;
    square_t to = (square_t)least_significant_one_bit(move_up_one);
    unset_least_significant_one_bit(move_up_one);

    set_move_from(move, to + (8 * dir));
    set_move_to(move, to);
    set_move_capture(move, EMPTY);

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
    set_move_capture(move, EMPTY);
    unset_least_significant_one_bit(move_up_two);
    add_move(moves, move);
  }

  while (pawns) {
    square_t from = (square_t)least_significant_one_bit(pawns);
    unset_least_significant_one_bit(pawns);
    // TODO: implement en passant
    bitboard_t attacks = pawn_attacks[color][from] & (color == WHITE ? board->black_pieces : board->white_pieces);
    bitboard_t en_passant_attack =
        (pawn_attacks[color][from] & (board->en_passant) & (color == WHITE ? ~RANK_3 : ~RANK_6));

    if (en_passant_attack) {
      square_t attack_to = (square_t)least_significant_one_bit(en_passant_attack);
      move_t move = 0;
      set_move_en_passant(move);
      set_move_from(move, from);
      set_move_to(move, attack_to);
      set_move_capture(move, EMPTY);
      add_move(moves, move);
    }

    if (!attacks)
      continue;
    square_t attack_to = (square_t)least_significant_one_bit(attacks);
    unset_least_significant_one_bit(attacks);
    move_t move = 0;
    set_move_capture(move, board->pieces[attack_to]);
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
    set_move_capture(move, board->pieces[attack_to]);
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

int generate_pseudo_legal_knight_moves(board_t *board, move_t *moves, color_t color, bitboard_t can_move_to_mask) {
  move_t *tmp = moves;

  bitboard_t knights = board->piece_bitboards[index_color_piece(color, KNIGHT)];

  while (knights) {
    square_t from = (square_t)least_significant_one_bit(knights);
    unset_least_significant_one_bit(knights);

    bitboard_t attacks = knight_attacks[from] & can_move_to_mask;
    while (attacks) {
      square_t to = (square_t)least_significant_one_bit(attacks);
      unset_least_significant_one_bit(attacks);
      move_t move = 0;
      if (board->pieces[to] != EMPTY) {
        set_move_capture(move, board->pieces[to]);
      } else {
        set_move_capture(move, EMPTY);
      }
      set_move_from(move, from);
      set_move_to(move, to);
      add_move(moves, move);
    }
  }

  return moves - tmp;
}

int generate_pseudo_legal_slider_moves(board_t *board, move_t *moves, color_t color, piece_t piece,
                                       bitboard_t occupancy_mask) {
  move_t *tmp = moves;

  bitboard_t pieces = board->piece_bitboards[index_color_piece(color, piece)];

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

      move_t move = 0;
      if (board->pieces[to] != EMPTY) {
        set_move_capture(move, board->pieces[to]);
      } else {
        set_move_capture(move, EMPTY);
      }
      set_move_from(move, from);
      set_move_to(move, to);
      add_move(moves, move);
    }
  }

  return moves - tmp;
}

int generate_pseudo_legal_bishop_moves(board_t *board, move_t *moves, color_t color) {
  return generate_pseudo_legal_slider_moves(board, moves, color, BISHOP, board->all_pieces);
}

int generate_pseudo_legal_rook_moves(board_t *board, move_t *moves, color_t color) {
  return generate_pseudo_legal_slider_moves(board, moves, color, ROOK, board->all_pieces);
}

int generate_pseudo_legal_queen_moves(board_t *board, move_t *moves, color_t color) {
  return generate_pseudo_legal_slider_moves(board, moves, color, QUEEN, board->all_pieces);
}

int castle_squares_attacked(board_t *board, direction_t dir) {
  color_t color = board->turn_color;

  if (dir == EAST) {
    if (color == WHITE) {
      return is_square_attacked(board, F1, !color) || is_square_attacked(board, G1, !color) ||
             is_square_attacked(board, E1, !color);
    } else {
      return is_square_attacked(board, F8, !color) || is_square_attacked(board, G8, !color) ||
             is_square_attacked(board, E8, !color);
    }
  } else if (dir == WEST) {
    if (color == WHITE) {
      return is_square_attacked(board, B1, !color) || is_square_attacked(board, C1, !color) ||
             is_square_attacked(board, D1, !color) || is_square_attacked(board, E1, !color);
    } else {
      return is_square_attacked(board, B8, !color) || is_square_attacked(board, C8, !color) ||
             is_square_attacked(board, D8, !color) || is_square_attacked(board, E8, !color);
    }
  }
  return 0;
}

int generate_pseudo_legal_king_moves(board_t *board, move_t *moves, color_t color, bitboard_t can_move_to_mask) {
  move_t *tmp = moves;

  bitboard_t king = board->piece_bitboards[index_color_piece(color, KING)];

  square_t from = (square_t)least_significant_one_bit(king);
  unset_least_significant_one_bit(king);

  bitboard_t attacks = king_attacks[from] & can_move_to_mask;
  while (attacks) {
    square_t to = (square_t)least_significant_one_bit(attacks);
    unset_least_significant_one_bit(attacks);
    move_t move = 0;
    if (board->pieces[to] != EMPTY) {
      set_move_capture(move, board->pieces[to]);
    } else {
      set_move_capture(move, EMPTY);
    }
    set_move_from(move, from);
    set_move_to(move, to);
    add_move(moves, move);
  }

  bitboard_t empty_space = ~board->all_pieces;
  if (color == WHITE) {
    if (((CASTLE_SOUTH_EAST_MASK & empty_space) == CASTLE_SOUTH_EAST_MASK) &&
        get_castle_rights_se(board->castle_rights) && !castle_squares_attacked(board, EAST)) {
      move_t move = 0;
      set_move_from(move, from);
      set_move_to(move, G1);
      set_move_capture(move, EMPTY);
      set_move_castle_east(move);
      add_move(moves, move);
    }
    if (((CASTLE_SOUTH_WEST_MASK & empty_space) == CASTLE_SOUTH_WEST_MASK) &&
        get_castle_rights_sw(board->castle_rights) && !castle_squares_attacked(board, WEST)) {
      move_t move = 0;
      set_move_from(move, from);
      set_move_to(move, C1);
      set_move_capture(move, EMPTY);
      set_move_castle_west(move);
      add_move(moves, move);
    }
  } else {
    if (((CASTLE_NORTH_EAST_MASK & empty_space) == CASTLE_NORTH_EAST_MASK) &&
        get_castle_rights_ne(board->castle_rights) && !castle_squares_attacked(board, EAST)) {
      move_t move = 0;
      set_move_from(move, from);
      set_move_to(move, G8);
      set_move_capture(move, EMPTY);
      set_move_castle_east(move);
      add_move(moves, move);
    }
    if (((CASTLE_NORTH_WEST_MASK & empty_space) == CASTLE_NORTH_WEST_MASK) &&
        get_castle_rights_nw(board->castle_rights) && !castle_squares_attacked(board, WEST)) {
      move_t move = 0;
      set_move_from(move, from);
      set_move_to(move, C8);
      set_move_capture(move, EMPTY);
      set_move_castle_west(move);
      add_move(moves, move);
    }
  }

  return moves - tmp;
}

int is_square_attacked(board_t *board, square_t square, color_t attacker_color) {
  if ((attacker_color == WHITE) &&
      (pawn_attacks[BLACK][square] & board->piece_bitboards[index_color_piece(WHITE, PAWN)]))
    return 1;
  if ((attacker_color == BLACK) &&
      (pawn_attacks[WHITE][square] & board->piece_bitboards[index_color_piece(BLACK, PAWN)]))
    return 1;
  if (knight_attacks[square] & ((attacker_color == WHITE) ? board->piece_bitboards[index_color_piece(WHITE, KNIGHT)]
                                                          : board->piece_bitboards[index_color_piece(BLACK, KNIGHT)]))
    return 1;
  if (get_bishop_attacks(square, board->all_pieces) &
      ((attacker_color == WHITE) ? board->piece_bitboards[index_color_piece(WHITE, BISHOP)]
                                 : board->piece_bitboards[index_color_piece(BLACK, BISHOP)]))
    return 1;
  if (get_rook_attacks(square, board->all_pieces) &
      ((attacker_color == WHITE) ? board->piece_bitboards[index_color_piece(WHITE, ROOK)]
                                 : board->piece_bitboards[index_color_piece(BLACK, ROOK)]))
    return 1;
  if (get_queen_attacks(square, board->all_pieces) &
      ((attacker_color == WHITE) ? board->piece_bitboards[index_color_piece(WHITE, QUEEN)]
                                 : board->piece_bitboards[index_color_piece(BLACK, QUEEN)]))
    return 1;
  if (king_attacks[square] & ((attacker_color == WHITE) ? board->piece_bitboards[index_color_piece(WHITE, KING)]
                                                        : board->piece_bitboards[index_color_piece(BLACK, KING)]))
    return 1;

  return 0;
}

int is_king_in_check(board_t *board, color_t color) {
  square_t square = least_significant_one_bit(color == WHITE ? board->piece_bitboards[index_color_piece(WHITE, KING)]
                                                             : board->piece_bitboards[index_color_piece(BLACK, KING)]);
  return is_square_attacked(board, square, color == WHITE ? BLACK : WHITE);
}
