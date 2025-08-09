#include "bitboard.h"

#include <stdio.h>

void print_board(bitboard_t bitboard) {
  for (int rank = 7; rank >= 0; rank--) {
    if (rank == 7)
      printf("%d  ", rank + 1);
    else
      printf("\n%d  ", rank + 1);
    for (int file = 7; file >= 0; file--) {
      printf("%d ", (bitboard & (1ULL << ((rank * 8) + file))) ? 1 : 0);
    }
  }
  printf("\n\n   A B C D E F G H \n\n");
}

int population_count(bitboard_t bitboard) {
  int count = 0;
  while (bitboard) {
    count++;
    bitboard &= bitboard - 1;
  }
  return count;
}

int least_significant_one_bit(uint64_t bitboard) {
  if (!bitboard)
    return -1;
  const uint64_t debruijn = 0x03f79d71b4cb0a89;
  return lsb_index[((bitboard ^ (bitboard - 1)) * debruijn) >> 58];
}
