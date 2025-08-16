#ifndef DD_COMMON_H_
#define DD_COMMON_H_

#define SQUARE_COUNT 64
#define DARK_MODE 1
#define file_rank_to_square(file, rank) ((rank * 8) + file)
#define INDEX_COLOR_PIECE(color, piece) (piece) + ((color) * 6)

typedef enum {
  EMPTY = -1,
  PAWN,
  KNIGHT,
  BISHOP,
  ROOK,
  QUEEN,
  KING,
} pieces_t;

extern const char *piece_to_utf8[];

// clang-format off
// IMPORTANT NOTE: Values are in this particular order because of layout 
// of bitboard. Bit board LSB is at H1 and MSB at A8.
typedef enum {
  H1, G1, F1, E1, D1, C1, B1, A1,
  H2, G2, F2, E2, D2, C2, B2, A2,
  H3, G3, F3, E3, D3, C3, B3, A3,
  H4, G4, F4, E4, D4, C4, B4, A4,
  H5, G5, F5, E5, D5, C5, B5, A5,
  H6, G6, F6, E6, D6, C6, B6, A6,
  H7, G7, F7, E7, D7, C7, B7, A7,
  H8, G8, F8, E8, D8, C8, B8, A8,
} square_t;
// clang-format on

typedef enum { WHITE, BLACK } piece_color_t;

typedef enum { H, G, F, E, D, C, B, A } file_t;

typedef enum { ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT } rank_t;

#define RANK_8 0xff00000000000000ULL
#define RANK_7 0x00ff000000000000ULL
#define RANK_6 0x0000ff0000000000ULL
#define RANK_5 0x000000ff00000000ULL
#define RANK_4 0x00000000ff000000ULL
#define RANK_3 0x0000000000ff0000ULL
#define RANK_2 0x000000000000ff00ULL
#define RANK_1 0x00000000000000ffULL

#define FILE_H 0x0101010101010101ULL
#define FILE_G 0x0202020202020202ULL
#define FILE_F 0x0404040404040404ULL
#define FILE_E 0x0808080808080808ULL
#define FILE_D 0x1010101010101010ULL
#define FILE_C 0x2020202020202020ULL
#define FILE_B 0x4040404040404040ULL
#define FILE_A 0x8080808080808080ULL

typedef enum { EAST = 1, WEST, NORTH, SOUTH } direction_t;

#define CASTLE_NORTH_EAST_MASK 0x0600000000000000ULL
#define CASTLE_NORTH_WEST_MASK 0x8000000000000000ULL
#define CASTLE_SOUTH_EAST_MASK 0x0000000000000006ULL
#define CASTLE_SOUTH_WEST_MASK 0x0000000000000080ULL

#endif
