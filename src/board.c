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

void make_move(board_t *board, move_t move) {}

void unmake_move(board_t *board, move_t move) {}

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
