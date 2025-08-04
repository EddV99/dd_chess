#include "bitboard.h"

#include <stdio.h>

void print_board(bitboard_t bitboard) {
  for (int rank = 7; rank >= 0; rank--) {
    if (rank == 7)
      printf("%d  ", rank + 1);
    else
      printf("\n%d  ", rank + 1);
    for (int file = 0; file < 8; file++) {
      printf("%d ", (bitboard & (1ULL << ((rank * 8) + file))) ? 1 : 0);
    }
  }
  printf("\n\n   A B C D E F G H \n");
}
