#ifndef DD_MOVE_GENERATOR_H_
#define DD_MOVE_GENERATOR_H_

#include "bitboard.h"
#include "common.h"

/*
 * Hold information about pawn attacks
 * pawn_attacks[color][square];
 */
extern bitboard_t pawn_attacks[2][SQUARE_COUNT];

void generate_pawn_attacks();

#endif
