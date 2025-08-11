#ifndef DD_MOVE_GENERATOR_H_
#define DD_MOVE_GENERATOR_H_

#include "bitboard.h"
#include "common.h"
#include "prng.h"

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

#endif
