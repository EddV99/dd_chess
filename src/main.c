#include "bitboard.h"
#include "board.h"

#include <stdio.h>

int main() {
  printf("dd_chess\n");

  board_t board = create_new_board();

  print_board(board.black_pawns);

  return 0;
}
