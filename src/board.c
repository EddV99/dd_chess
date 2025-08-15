#include "board.h"
#include "common.h"
#include "move.h"

board_t create_new_board() {
  board_t new_board = {
      .is_white_turn = true,
      .castle_rights = 0b00001111,
      .piece_bitboards[INDEX_BITBOARD(WHITE, KING)] = square_mask(E1),
      .piece_bitboards[INDEX_BITBOARD(WHITE, QUEEN)] = square_mask(D1),
      .piece_bitboards[INDEX_BITBOARD(WHITE, ROOK)] = square_mask(A1) | square_mask(H1),
      .piece_bitboards[INDEX_BITBOARD(WHITE, BISHOP)] = square_mask(C1) | square_mask(F1),
      .piece_bitboards[INDEX_BITBOARD(WHITE, KNIGHT)] = square_mask(B1) | square_mask(G1),
      .piece_bitboards[INDEX_BITBOARD(WHITE, PAWN)] = square_mask(A2) | square_mask(B2) | square_mask(C2) |
                                                      square_mask(D2) | square_mask(E2) | square_mask(F2) |
                                                      square_mask(G2) | square_mask(H2),
      .white_pieces = square_mask(A1) | square_mask(B1) | square_mask(C1) | square_mask(D1) | square_mask(E1) |
                      square_mask(F1) | square_mask(G1) | square_mask(H1) | square_mask(A2) | square_mask(B2) |
                      square_mask(C2) | square_mask(D2) | square_mask(E2) | square_mask(F2) | square_mask(G2) |
                      square_mask(H2),

      .piece_bitboards[INDEX_BITBOARD(BLACK, KING)] = square_mask(E8),
      .piece_bitboards[INDEX_BITBOARD(BLACK, QUEEN)] = square_mask(D8),
      .piece_bitboards[INDEX_BITBOARD(BLACK, ROOK)] = square_mask(A8) | square_mask(H8),
      .piece_bitboards[INDEX_BITBOARD(BLACK, BISHOP)] = square_mask(C8) | square_mask(F8),
      .piece_bitboards[INDEX_BITBOARD(BLACK, KNIGHT)] = square_mask(B8) | square_mask(G8),
      .piece_bitboards[INDEX_BITBOARD(BLACK, PAWN)] = square_mask(A7) | square_mask(B7) | square_mask(C7) |
                                                      square_mask(D7) | square_mask(E7) | square_mask(F7) |
                                                      square_mask(G7) | square_mask(H7),
      .black_pieces = square_mask(A8) | square_mask(B8) | square_mask(C8) | square_mask(D8) | square_mask(E8) |
                      square_mask(F8) | square_mask(G8) | square_mask(H8) | square_mask(A7) | square_mask(B7) |
                      square_mask(C7) | square_mask(D7) | square_mask(E7) | square_mask(F7) | square_mask(G7) |
                      square_mask(H7),
      .all_pieces = 0ULL,
      .en_passant = 0ULL,
      .pieces = {EMPTY},
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
  pieces_t promotion = get_move_promotion(move);
  int castle = get_move_castle(move);

  pieces_t from_piece = board->pieces[from];
  pieces_t to_piece = board->pieces[to];
  piece_color_t color = board->is_white_turn ? WHITE : BLACK;

  move_piece(board->all_pieces, from, to);
  board->pieces[from] = EMPTY;
  unset_bit(board->piece_bitboards[INDEX_BITBOARD(color, from_piece)], from);

  if (promotion) {
    board->pieces[to] = promotion;
    set_bit(board->piece_bitboards[INDEX_BITBOARD(color, promotion)], to);
  } else {
    board->pieces[to] = from_piece;
    set_bit(board->piece_bitboards[INDEX_BITBOARD(color, from_piece)], to);
  }

  // TODO: castle stuff

  if (to_piece != EMPTY) {
    if (color == WHITE) {
      unset_bit(board->black_pieces, to);
      unset_bit(board->piece_bitboards[INDEX_BITBOARD(BLACK, to_piece)], to);
    } else {
      unset_bit(board->white_pieces, to);
      unset_bit(board->piece_bitboards[INDEX_BITBOARD(WHITE, to_piece)], to);
    }
  } else if (get_move_en_passant(move)) {
    if (color == WHITE) {
      unset_bit(board->black_pieces, to - 8);
      unset_bit(board->piece_bitboards[INDEX_BITBOARD(BLACK, PAWN)], to - 8);
    } else {
      unset_bit(board->white_pieces, to + 8);
      unset_bit(board->piece_bitboards[INDEX_BITBOARD(WHITE, PAWN)], to + 8);
    }
  }

  if (color == WHITE) {
    move_piece(board->white_pieces, from, to);
  } else {
    move_piece(board->black_pieces, from, to);
  }

  board->en_passant = 0;
  board->is_white_turn = !board->is_white_turn;
}

