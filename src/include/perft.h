#ifndef DD_PERFT_H_
#define DD_PERFT_H_

#include "board.h"

#include <stdint.h>

void perft_report();
uint64_t perft(int depth, board_t *board, int print, uint64_t *captures, uint64_t *ep, uint64_t *castles,
               uint64_t *promotions, uint64_t *checks);

#endif
