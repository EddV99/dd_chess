#include "board.h"
#include "common.h"
#include "move.h"

#include <stdio.h>

board_t create_new_board() {
  board_t new_board = {
      .turn_color = WHITE,
      .castle_rights = 0b00001111,
      .piece_bitboards[index_color_piece(WHITE, KING)] = square_mask(E1),
      .piece_bitboards[index_color_piece(WHITE, QUEEN)] = square_mask(D1),
      .piece_bitboards[index_color_piece(WHITE, ROOK)] = square_mask(A1) | square_mask(H1),
      .piece_bitboards[index_color_piece(WHITE, BISHOP)] = square_mask(C1) | square_mask(F1),
      .piece_bitboards[index_color_piece(WHITE, KNIGHT)] = square_mask(B1) | square_mask(G1),
      .piece_bitboards[index_color_piece(WHITE, PAWN)] = square_mask(A2) | square_mask(B2) | square_mask(C2) |
                                                         square_mask(D2) | square_mask(E2) | square_mask(F2) |
                                                         square_mask(G2) | square_mask(H2),
      .white_pieces = square_mask(A1) | square_mask(B1) | square_mask(C1) | square_mask(D1) | square_mask(E1) |
                      square_mask(F1) | square_mask(G1) | square_mask(H1) | square_mask(A2) | square_mask(B2) |
                      square_mask(C2) | square_mask(D2) | square_mask(E2) | square_mask(F2) | square_mask(G2) |
                      square_mask(H2),

      .piece_bitboards[index_color_piece(BLACK, KING)] = square_mask(E8),
      .piece_bitboards[index_color_piece(BLACK, QUEEN)] = square_mask(D8),
      .piece_bitboards[index_color_piece(BLACK, ROOK)] = square_mask(A8) | square_mask(H8),
      .piece_bitboards[index_color_piece(BLACK, BISHOP)] = square_mask(C8) | square_mask(F8),
      .piece_bitboards[index_color_piece(BLACK, KNIGHT)] = square_mask(B8) | square_mask(G8),
      .piece_bitboards[index_color_piece(BLACK, PAWN)] = square_mask(A7) | square_mask(B7) | square_mask(C7) |
                                                         square_mask(D7) | square_mask(E7) | square_mask(F7) |
                                                         square_mask(G7) | square_mask(H7),
      .black_pieces = square_mask(A8) | square_mask(B8) | square_mask(C8) | square_mask(D8) | square_mask(E8) |
                      square_mask(F8) | square_mask(G8) | square_mask(H8) | square_mask(A7) | square_mask(B7) |
                      square_mask(C7) | square_mask(D7) | square_mask(E7) | square_mask(F7) | square_mask(G7) |
                      square_mask(H7),
      .all_pieces = 0ULL,
      .en_passant = 0ULL,
      .pieces = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                 EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                 EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                 EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                 EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
  };

  new_board.pieces[A1] = ROOK;
  new_board.pieces[B1] = KNIGHT;
  new_board.pieces[C1] = BISHOP;
  new_board.pieces[D1] = QUEEN;
  new_board.pieces[E1] = KING;
  new_board.pieces[F1] = BISHOP;
  new_board.pieces[G1] = KNIGHT;
  new_board.pieces[H1] = ROOK;

  new_board.pieces[A2] = PAWN;
  new_board.pieces[B2] = PAWN;
  new_board.pieces[C2] = PAWN;
  new_board.pieces[D2] = PAWN;
  new_board.pieces[E2] = PAWN;
  new_board.pieces[F2] = PAWN;
  new_board.pieces[G2] = PAWN;
  new_board.pieces[H2] = PAWN;

  new_board.pieces[A7] = PAWN;
  new_board.pieces[B7] = PAWN;
  new_board.pieces[C7] = PAWN;
  new_board.pieces[D7] = PAWN;
  new_board.pieces[E7] = PAWN;
  new_board.pieces[F7] = PAWN;
  new_board.pieces[G7] = PAWN;
  new_board.pieces[H7] = PAWN;

  new_board.pieces[A8] = ROOK;
  new_board.pieces[B8] = KNIGHT;
  new_board.pieces[C8] = BISHOP;
  new_board.pieces[D8] = QUEEN;
  new_board.pieces[E8] = KING;
  new_board.pieces[F8] = BISHOP;
  new_board.pieces[G8] = KNIGHT;
  new_board.pieces[H8] = ROOK;

  new_board.all_pieces = new_board.white_pieces | new_board.black_pieces;
  return new_board;
}

void make_move(board_t *board, move_t move) {
  square_t from = get_move_from(move);
  square_t to = get_move_to(move);
  piece_t promotion = get_move_promotion(move);

  int castle = get_move_castle(move);
  int en_passant = get_move_en_passant(move);

  piece_t capture = get_move_capture(move);
  int captured = capture != EMPTY;

  piece_t from_piece = board->pieces[from];
  piece_t to_piece = board->pieces[to];
  color_t color = board->turn_color;

  if (castle) {
    square_t rook_square_before =
        color == WHITE ? ((direction_t)castle == EAST ? H1 : A1) : ((direction_t)castle == EAST ? H8 : A8);
    square_t rook_square_after =
        color == WHITE ? ((direction_t)castle == EAST ? F1 : D1) : ((direction_t)castle == EAST ? F8 : D8);
    move_piece_sync(board, rook_square_before, rook_square_after, ROOK, color);
  } else if (en_passant) {
    square_t captured_pawn_square = to + (8 * (color == WHITE ? 1 : -1));
    remove_piece_sync(board, captured_pawn_square, PAWN, !color);
  } else if (captured) {
    remove_piece_sync(board, to, capture, !color);
  }

  move_piece_sync(board, from, to, (promotion ? promotion : from_piece), color);
  set_move_old_en_passant_square(move, (square_t)least_significant_one_bit(board->en_passant));
  board->en_passant = 0ULL;
  if (from_piece == PAWN) {
    if ((from & RANK_2) && (to & RANK_4)) {
      board->en_passant = square_mask(to - 8);
    } else if ((from & RANK_7) && (to & RANK_5)) {
      board->en_passant = square_mask(to + 8);
    }
  }
  board->turn_color = !board->turn_color;
}

void unmake_move(board_t *board, move_t move) {
  board->turn_color = !board->turn_color;
  board->en_passant = square_mask(get_move_old_en_passant_square(move));

  square_t from = get_move_from(move);
  square_t to = get_move_to(move);
  piece_t promotion = get_move_promotion(move);

  int castle = get_move_castle(move);
  int en_passant = get_move_en_passant(move);

  piece_t capture = get_move_capture(move);
  int captured = capture != EMPTY;

  piece_t piece = board->pieces[to];
  color_t color = board->turn_color;

  if (promotion) {
    remove_piece_sync(board, to, promotion, color);
    add_piece_sync(board, from, PAWN, color);
  } else {
    move_piece_sync(board, to, from, piece, color);
  }

  if (castle) {
    square_t rook_square_before =
        color == WHITE ? ((direction_t)castle == EAST ? H1 : A1) : ((direction_t)castle == EAST ? H8 : A8);
    square_t rook_square_after =
        color == WHITE ? ((direction_t)castle == EAST ? F1 : D1) : ((direction_t)castle == EAST ? F8 : D8);
    move_piece_sync(board, rook_square_after, rook_square_before, ROOK, color);
  } else if (en_passant) {
    square_t captured_pawn_square = to + (8 * (color == WHITE ? 1 : -1));
    add_piece_sync(board, captured_pawn_square, PAWN, !color);
  } else if (captured) {
    add_piece_sync(board, to, capture, !color);
  }
}

void print_board(board_t *board) {
  for (int rank = 7; rank >= 0; rank--) {
    if (rank == 7)
      printf("%d  ", rank + 1);
    else
      printf("\n%d  ", rank + 1);
    for (int file = 7; file >= 0; file--) {
      square_t sq = file_rank_to_square(file, rank);
      if (board->pieces[sq] == EMPTY) {
        printf(". ");
      } else {
        color_t color =
            board->white_pieces & square_mask(sq) ? (DARK_MODE ? BLACK : WHITE) : (DARK_MODE ? WHITE : BLACK);
        printf("%s ", piece_to_utf8[index_color_piece(color, board->pieces[sq])]);
      }
    }
  }
  printf("\n\n   A B C D E F G H \n\n");
}
