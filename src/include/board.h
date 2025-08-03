#ifndef DD_BOARD_H_
#define DD_BOARD_H_

#include <stdint.h>

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
  uint32_t rule50;
  // keep track of castle rights
  // bit 7: castle rights for white king side
  // bit 6: castle rights for white queen side
  // bit 5: castle rights for black king side
  // bit 4: castle rights for black queen side
  uint8_t castle_rights;
  // 64 bits represents the whole board.
  // bit 56-63: rank 8
  // bit 48-55: rank 7
  // bit 40-47: rank 6
  // bit 32-39: rank 5
  // bit 24-31: rank 4
  // bit 16-23: rank 3
  // bit 8-15:  rank 2
  // bit 0-7:   rank 1
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
} board_t;

board_t create_new_board();

#endif
