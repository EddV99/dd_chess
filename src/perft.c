#include "perft.h"

#include "board.h"
#include "move.h"
#include "move_generator.h"

#include <stdio.h>

uint64_t perft(int depth, board_t *board, int print) {
  uint64_t nodes = 0;

  if (depth == 0)
    return 1ULL;

  move_t move_list[MAX_MOVES] = {0};
  int count = generate_pseudo_legal_moves(board, move_list);
  for (int i = 0; i < count; i++) {
    move_t move = move_list[i];
    piece_color_t old_color = board->is_white_turn ? WHITE : BLACK;
    make_move(board, move);
    if(print){
      printf("%d:\n", i);
      print_board(board);
    }
    if (!is_king_in_check(board, old_color))
      nodes += perft(depth - 1, board, print);
    unmake_move(board, move);
  }
  return nodes;
}
