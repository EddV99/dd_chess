#ifndef DD_MOVE_GENERATOR_H_
#define DD_MOVE_GENERATOR_H_

#include "bitboard.h"
#include "common.h"

#define NOT_A_FILE (0x7f7f7f7f7f7f7f7fULL)
#define NOT_H_FILE (0xfefefefefefefefeULL)
#define NOT_AB_FILE (0x3f3f3f3f3f3f3f3fULL)
#define NOT_GH_FILE (0xfcfcfcfcfcfcfcfcULL)

/*
 * Hold information about pawn attacks
 * pawn_attacks[color][square];
 */
extern bitboard_t pawn_attacks[2][SQUARE_COUNT];

void generate_pawn_attacks();

/*
 * Hold information about knight attacks
 * knight_attacks[square];
 */
extern bitboard_t knight_attacks[SQUARE_COUNT];

void generate_knight_attacks();

/*
 * Hold information about king attacks
 * king_attacks[square];
 */
extern bitboard_t king_attacks[SQUARE_COUNT];

void generate_king_attacks();

typedef struct {
  bitboard_t mask;
  uint64_t magic_number;
  uint8_t index_bits;
} magic_t;

#define MAGIC_INDEX(magic, blockers) (((blockers & magic.mask) * magic.magic_number) >> (64U - magic.index_bits))

bitboard_t rook_occupancy(square_t square);
bitboard_t generate_rook_attack(square_t square, bitboard_t blockers);
void get_rook_moves(magic_t magic, bitboard_t blockers);

bitboard_t bishop_occupancy(square_t square);
bitboard_t generate_bishop_attack(square_t square, bitboard_t blockers);
void get_bishop_moves(magic_t magic, bitboard_t blockers);
#endif
