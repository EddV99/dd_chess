#include "perft.h"

#include "board.h"
#include "move.h"
#include "move_generator.h"

#include <stdint.h>
#include <stdio.h>

void perft_report() {
  printf("PERFT Report\n");
  printf("=========================================================================================\n");

  int start = 0;
  int end = 5;
  int depths[] = {0, 1, 2, 3, 4, 5, 6};
  int print_boards = 0;
  for (int i = start; i <= end; i++) {
    board_t board = create_new_board();
    uint64_t captures = 0, ep = 0, castles = 0, promotions = 0, checks = 0;
    uint64_t count = perft(depths[i], &board, print_boards, &captures, &ep, &castles, &promotions, &checks);
    printf("DEPTH: %d, NODES: %ld, CAPTURES: %ld, EP: %ld, CASTLES: %ld, PROMOTIONS: %ld, CHECKS: %ld\n", depths[i],
           count, captures, ep, castles, promotions, checks);
  }
}

uint64_t perft(int depth, board_t *board, int print, uint64_t *captures, uint64_t *ep, uint64_t *castles,
               uint64_t *promotions, uint64_t *checks) {
  uint64_t nodes = 0;

  if (depth == 0)
    return 1ULL;

  move_t move_list[MAX_MOVES] = {0};
  int count = generate_pseudo_legal_moves(board, move_list);
  for (int i = 0; i < count; i++) {
    move_t move = move_list[i];

    board_t old_board = copy_board(board);

    color_t old_color = board->turn_color;
    make_move(board, &move);
    int valid_move = !is_king_in_check(board, old_color);

    if (print)
      print_board(board);

    if (valid_move) {
      if (get_move_en_passant(move))
        (*ep)++;
      if (get_move_castle(move))
        (*castles)++;
      if (get_move_promotion(move))
        (*promotions)++;
      if ((piece_t)get_move_capture(move) != EMPTY)
        (*captures)++;
      if (is_king_in_check(board, !old_color))
        (*checks)++;
      nodes += perft(depth - 1, board, print, captures, ep, castles, promotions, checks);
    }
    unmake_move(board, move);

    if (!board_equals(&old_board, board)) {
      printf("BAD UNMOVE\n");
    }
  }
  return nodes;
}
