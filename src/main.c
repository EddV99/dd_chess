#include "bitboard.h"
#include "board.h"
#include "common.h"
#include "move_generator.h"

#include <stdio.h>

int main() {
  printf("dd_chess\n");
  
  bitboard_t attack_mask = rook_occupancy(A1);
  print_board(attack_mask);

  int count = population_count(attack_mask);
  bitboard_t key = set_occupancy(4095, count, attack_mask);
  print_board(key);

  bitboard_t magic = 0x0119299CCBA92234;

  printf("magic is %ld", (key * magic)  >> (64 - count));

  return 0;
}
