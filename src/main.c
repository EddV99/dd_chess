#include "attack.h"
#include "bitboard.h"
#include "board.h"
#include "common.h"
#include "magic.h"
#include "move_generator.h"
#include "perft.h"
#include "prng.h"

#include <stdint.h>
#include <stdio.h>

int main() {
  printf("dd_chess\n");
  init_attacks();
  // perft_report();
  board_t board = load_fen("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");
  print_board(&board);

  return 0;
}
