#ifndef DD_BOARD_H_
#define DD_BOARD_H_

#include <stdint.h>

#define EMPTY ((uint8_t)0x0)

#define WHITE_PAWN ((uint8_t)0x1)
#define WHITE_KNIGHT ((uint8_t)0x2)
#define WHITE_BISHOP ((uint8_t)0x3)
#define WHITE_ROOK ((uint8_t)0x4)
#define WHITE_QUEEN ((uint8_t)0x5)
#define WHITE_KING ((uint8_t)0x6)

#define BLACK_PAWN ((uint8_t)0x7)
#define BLACK_KNIGHT ((uint8_t)0x8)
#define BLACK_BISHOP ((uint8_t)0x9)
#define BLACK_ROOK ((uint8_t)0xa)
#define BLACK_QUEEN ((uint8_t)0xb)
#define BLACK_KING ((uint8_t)0xc)

typedef struct {
  uint8_t is_white_turn;
  uint64_t sequential_reversible_moves;
  // First two bits are white side.
  //
  // Next two bits are black side.
  //
  // First bit in pair is for queen side.
  // Second bit in pair is king side.
  //
  // TAKE NOTE OF ORIENTATION FOR BLACK
  uint8_t castle_rights;

  // 64 bits represents the whole board.
  // First 8 bits represent rank 8.
  // Second 8 bits represent rank 7 and so on.
  uint64_t white_king;
  uint64_t white_queen;
  uint64_t white_rooks;
  uint64_t white_bishops;
  uint64_t white_knights;
  uint64_t white_pawns;

  uint64_t black_king;
  uint64_t black_queen;
  uint64_t black_rooks;
  uint64_t black_bishops;
  uint64_t black_knights;
  uint64_t black_pawns;

  // Mailbox (x88) representation
  uint8_t squares[128];
} Board;

#define rank_file_to_x88_coord(rank, file) 16 * rank + file
#define is_invalid_move(rank, file) rank_file_to_x88_coord(rank, file) & 0x88

#endif
