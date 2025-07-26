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

#define MAILBOX_A1 ((uint8_t)0x00)
#define MAILBOX_A2 ((uint8_t)0x10)
#define MAILBOX_A3 ((uint8_t)0x20)
#define MAILBOX_A4 ((uint8_t)0x30)
#define MAILBOX_A5 ((uint8_t)0x40)
#define MAILBOX_A6 ((uint8_t)0x50)
#define MAILBOX_A7 ((uint8_t)0x60)
#define MAILBOX_A8 ((uint8_t)0x70)
#define MAILBOX_B1 ((uint8_t)0x01)
#define MAILBOX_B2 ((uint8_t)0x11)
#define MAILBOX_B3 ((uint8_t)0x21)
#define MAILBOX_B4 ((uint8_t)0x31)
#define MAILBOX_B5 ((uint8_t)0x41)
#define MAILBOX_B6 ((uint8_t)0x51)
#define MAILBOX_B7 ((uint8_t)0x61)
#define MAILBOX_B8 ((uint8_t)0x71)
#define MAILBOX_C1 ((uint8_t)0x02)
#define MAILBOX_C2 ((uint8_t)0x12)
#define MAILBOX_C3 ((uint8_t)0x22)
#define MAILBOX_C4 ((uint8_t)0x32)
#define MAILBOX_C5 ((uint8_t)0x42)
#define MAILBOX_C6 ((uint8_t)0x52)
#define MAILBOX_C7 ((uint8_t)0x62)
#define MAILBOX_C8 ((uint8_t)0x72)
#define MAILBOX_D1 ((uint8_t)0x03)
#define MAILBOX_D2 ((uint8_t)0x13)
#define MAILBOX_D3 ((uint8_t)0x23)
#define MAILBOX_D4 ((uint8_t)0x33)
#define MAILBOX_D5 ((uint8_t)0x43)
#define MAILBOX_D6 ((uint8_t)0x53)
#define MAILBOX_D7 ((uint8_t)0x63)
#define MAILBOX_D8 ((uint8_t)0x73)
#define MAILBOX_E1 ((uint8_t)0x04)
#define MAILBOX_E2 ((uint8_t)0x14)
#define MAILBOX_E3 ((uint8_t)0x24)
#define MAILBOX_E4 ((uint8_t)0x34)
#define MAILBOX_E5 ((uint8_t)0x44)
#define MAILBOX_E6 ((uint8_t)0x54)
#define MAILBOX_E7 ((uint8_t)0x64)
#define MAILBOX_E8 ((uint8_t)0x74)
#define MAILBOX_F1 ((uint8_t)0x05)
#define MAILBOX_F2 ((uint8_t)0x15)
#define MAILBOX_F3 ((uint8_t)0x25)
#define MAILBOX_F4 ((uint8_t)0x35)
#define MAILBOX_F5 ((uint8_t)0x45)
#define MAILBOX_F6 ((uint8_t)0x55)
#define MAILBOX_F7 ((uint8_t)0x65)
#define MAILBOX_F8 ((uint8_t)0x75)
#define MAILBOX_G1 ((uint8_t)0x06)
#define MAILBOX_G2 ((uint8_t)0x16)
#define MAILBOX_G3 ((uint8_t)0x26)
#define MAILBOX_G4 ((uint8_t)0x36)
#define MAILBOX_G5 ((uint8_t)0x46)
#define MAILBOX_G6 ((uint8_t)0x56)
#define MAILBOX_G7 ((uint8_t)0x66)
#define MAILBOX_G8 ((uint8_t)0x76)
#define MAILBOX_H1 ((uint8_t)0x07)
#define MAILBOX_H2 ((uint8_t)0x17)
#define MAILBOX_H3 ((uint8_t)0x27)
#define MAILBOX_H4 ((uint8_t)0x37)
#define MAILBOX_H5 ((uint8_t)0x47)
#define MAILBOX_H6 ((uint8_t)0x57)
#define MAILBOX_H7 ((uint8_t)0x67)
#define MAILBOX_H8 ((uint8_t)0x77)

#define BIT_A1 ((uint64_t)0x0000000000000080)
#define BIT_A2 ((uint64_t)0x0000000000008000)
#define BIT_A3 ((uint64_t)0x0000000000800000)
#define BIT_A4 ((uint64_t)0x0000000080000000)
#define BIT_A5 ((uint64_t)0x0000008000000000)
#define BIT_A6 ((uint64_t)0x0000800000000000)
#define BIT_A7 ((uint64_t)0x0080000000000000)
#define BIT_A8 ((uint64_t)0x8000000000000000)
#define BIT_B1 ((uint64_t)0x0000000000000040)
#define BIT_B2 ((uint64_t)0x0000000000004000)
#define BIT_B3 ((uint64_t)0x0000000000400000)
#define BIT_B4 ((uint64_t)0x0000000040000000)
#define BIT_B5 ((uint64_t)0x0000004000000000)
#define BIT_B6 ((uint64_t)0x0000400000000000)
#define BIT_B7 ((uint64_t)0x0040000000000000)
#define BIT_B8 ((uint64_t)0x4000000000000000)
#define BIT_C1 ((uint64_t)0x0000000000000020)
#define BIT_C2 ((uint64_t)0x0000000000002000)
#define BIT_C3 ((uint64_t)0x0000000000200000)
#define BIT_C4 ((uint64_t)0x0000000020000000)
#define BIT_C5 ((uint64_t)0x0000002000000000)
#define BIT_C6 ((uint64_t)0x0000200000000000)
#define BIT_C7 ((uint64_t)0x0020000000000000)
#define BIT_C8 ((uint64_t)0x2000000000000000)
#define BIT_D1 ((uint64_t)0x0000000000000010)
#define BIT_D2 ((uint64_t)0x0000000000001000)
#define BIT_D3 ((uint64_t)0x0000000000100000)
#define BIT_D4 ((uint64_t)0x0000000010000000)
#define BIT_D5 ((uint64_t)0x0000001000000000)
#define BIT_D6 ((uint64_t)0x0000100000000000)
#define BIT_D7 ((uint64_t)0x0010000000000000)
#define BIT_D8 ((uint64_t)0x1000000000000000)
#define BIT_E1 ((uint64_t)0x0000000000000008)
#define BIT_E2 ((uint64_t)0x0000000000000800)
#define BIT_E3 ((uint64_t)0x0000000000080000)
#define BIT_E4 ((uint64_t)0x0000000008000000)
#define BIT_E5 ((uint64_t)0x0000000800000000)
#define BIT_E6 ((uint64_t)0x0000080000000000)
#define BIT_E7 ((uint64_t)0x0008000000000000)
#define BIT_E8 ((uint64_t)0x0800000000000000)
#define BIT_F1 ((uint64_t)0x0000000000000004)
#define BIT_F2 ((uint64_t)0x0000000000000400)
#define BIT_F3 ((uint64_t)0x0000000000040000)
#define BIT_F4 ((uint64_t)0x0000000004000000)
#define BIT_F5 ((uint64_t)0x0000000400000000)
#define BIT_F6 ((uint64_t)0x0000040000000000)
#define BIT_F7 ((uint64_t)0x0004000000000000)
#define BIT_F8 ((uint64_t)0x0400000000000000)
#define BIT_G1 ((uint64_t)0x0000000000000002)
#define BIT_G2 ((uint64_t)0x0000000000000200)
#define BIT_G3 ((uint64_t)0x0000000000020000)
#define BIT_G4 ((uint64_t)0x0000000002000000)
#define BIT_G5 ((uint64_t)0x0000000200000000)
#define BIT_G6 ((uint64_t)0x0000020000000000)
#define BIT_G7 ((uint64_t)0x0002000000000000)
#define BIT_G8 ((uint64_t)0x0200000000000000)
#define BIT_H1 ((uint64_t)0x0000000000000001)
#define BIT_H2 ((uint64_t)0x0000000000000100)
#define BIT_H3 ((uint64_t)0x0000000000010000)
#define BIT_H4 ((uint64_t)0x0000000001000000)
#define BIT_H5 ((uint64_t)0x0000000100000000)
#define BIT_H6 ((uint64_t)0x0000010000000000)
#define BIT_H7 ((uint64_t)0x0001000000000000)
#define BIT_H8 ((uint64_t)0x0100000000000000)

typedef struct {
  uint8_t is_white_turn;
  uint32_t sequential_reversible_moves;
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

Board create_new_board();

#endif
