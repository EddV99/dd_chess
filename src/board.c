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

void make_move(board_t *board, move_t *move) {
  square_t from = get_move_from(*move);
  square_t to = get_move_to(*move);
  piece_t promotion = get_move_promotion(*move);
  int is_en_passant = get_move_en_passant(*move);
  int castle = get_move_castle(*move);

  piece_t captured_piece = get_move_capture(*move);
  int is_capture = captured_piece != EMPTY;

  if (is_capture) {
    remove_piece_sync(board, to, captured_piece, !board->turn_color);
    set_move_capture((*move), captured_piece);
  }

  if (is_en_passant) {
    square_t captured_pawn_sq = 0;
    if (board->turn_color == WHITE) {
      captured_pawn_sq = to - 8;
    } else {
      captured_pawn_sq = to + 8;
    }
    remove_piece_sync(board, captured_pawn_sq, PAWN, !board->turn_color);
  }

  if (castle) {
    if (castle == EAST) {
      if (board->turn_color == WHITE) {
        move_piece_sync(board, H1, F1, ROOK, board->turn_color);
      } else {
        move_piece_sync(board, H8, F8, ROOK, board->turn_color);
      }
    } else {
      if (board->turn_color == WHITE) {
        move_piece_sync(board, A1, D1, ROOK, board->turn_color);
      } else {
        move_piece_sync(board, A8, D8, ROOK, board->turn_color);
      }
    }
  }

  piece_t from_piece = board->pieces[from];
  if (promotion) {
    remove_piece_sync(board, from, from_piece, board->turn_color);
    add_piece_sync(board, to, promotion, board->turn_color);
  } else {
    move_piece_sync(board, from, to, from_piece, board->turn_color);
  }

  uint8_t en_sq = board->en_passant ? least_significant_one_bit(board->en_passant) : 0;
  set_move_en_passant_mask(*move, en_sq);

  board->en_passant = 0ULL;
  if (from_piece == PAWN) {
    if (board->turn_color == WHITE) {
      if ((from + 16) == to) {
        board->en_passant = square_mask((from + 8));
      }
    } else {
      if ((from - 16) == to) {
        board->en_passant = square_mask((from - 8));
      }
    }
  }

  uint8_t rights = board->castle_rights;
  set_move_castle_rights(*move, rights);

  board->turn_color = !board->turn_color;
}

void unmake_move(board_t *board, move_t move) {
  square_t from = get_move_from(move);
  square_t to = get_move_to(move);
  piece_t promotion = get_move_promotion(move);
  int is_en_passant = get_move_en_passant(move);
  int castle = get_move_castle(move);

  piece_t captured_piece = get_move_capture(move);
  int is_capture = captured_piece != EMPTY;

  board->turn_color = !board->turn_color;
  board->castle_rights = get_move_castle_rights(move);
  uint8_t en_sq = get_move_en_passant_mask(move);
  board->en_passant = en_sq ? square_mask(en_sq) : 0;

  piece_t piece = board->pieces[to];
  if (promotion) {
    remove_piece_sync(board, to, promotion, board->turn_color);
    add_piece_sync(board, from, PAWN, board->turn_color);
  } else {
    move_piece_sync(board, to, from, piece, board->turn_color);
  }

  if (castle) {
    if (castle == EAST) {
      if (board->turn_color == WHITE) {
        move_piece_sync(board, F1, H1, ROOK, board->turn_color);
      } else {
        move_piece_sync(board, F8, H8, ROOK, board->turn_color);
      }
    } else {
      if (board->turn_color == WHITE) {
        move_piece_sync(board, D1, A1, ROOK, board->turn_color);
      } else {
        move_piece_sync(board, D8, A8, ROOK, board->turn_color);
      }
    }
  }

  if (is_en_passant) {
    square_t captured_pawn_sq = 0;
    if (board->turn_color == WHITE) {
      captured_pawn_sq = to - 8;
    } else {
      captured_pawn_sq = to + 8;
    }
    add_piece_sync(board, captured_pawn_sq, PAWN, !board->turn_color);
  }

  if (is_capture) {
    add_piece_sync(board, to, captured_piece, !board->turn_color);
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

board_t copy_board(const board_t *board) {
  board_t result = create_new_board();

  result.turn_color = board->turn_color;
  result.rule50 = board->rule50;
  result.castle_rights = board->castle_rights;
  for (int i = 0; i < SQUARE_COUNT; i++)
    result.pieces[i] = board->pieces[i];
  for (int i = 0; i < 12; i++)
    result.piece_bitboards[i] = board->piece_bitboards[i];
  result.all_pieces = board->all_pieces;
  result.en_passant = board->en_passant;
  result.black_pieces = board->black_pieces;
  result.white_pieces = board->white_pieces;

  return result;
}

int board_equals(board_t *b1, board_t *b2) {
  if (b1->turn_color != b2->turn_color) {
    printf("color not equal\n");
    return 0;
  }
  if (b1->rule50 != b2->rule50) {
    printf("rule50 not equal\n");
    return 0;
  }
  if (b1->castle_rights != b2->castle_rights) {
    printf("castle rights not equal\n");
    printf("%x != %x\n", b1->castle_rights, b2->castle_rights);
    return 0;
  }
  for (int i = 0; i < SQUARE_COUNT; i++) {
    if (b1->pieces[i] != b2->pieces[i]) {
      printf("pieces not equal\n");
      return 0;
    }
  }
  for (int i = 0; i < 12; i++) {
    if (b1->piece_bitboards[i] != b2->piece_bitboards[i]) {
      printf("piece bitboard not equal\n");
      return 0;
    }
  }
  if (b1->all_pieces != b2->all_pieces) {
    printf("all pieces not equal\n");
    return 0;
  }
  if ((b1->en_passant) != (b2->en_passant)) {
    printf("en passant not equal\n");
    printf("%lx != %lx\n", b1->en_passant, b2->en_passant);
    return 0;
  }
  if (b1->black_pieces != b2->black_pieces) {
    printf("black pieces not equal\n");
    return 0;
  }
  if (b1->white_pieces != b2->white_pieces) {
    printf("white pieces not equal\n");
    return 0;
  }

  return 1;
}
