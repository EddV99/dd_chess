#include "magic.h"
#include "prng.h"

#include <string.h>
#include <stdio.h>

const int rook_occupancy_count[SQUARE_COUNT] = {12, 11, 11, 11, 11, 11, 11, 12, 11, 10, 10, 10, 10, 10, 10, 11,
                                                11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
                                                11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
                                                11, 10, 10, 10, 10, 10, 10, 11, 12, 11, 11, 11, 11, 11, 11, 12};

bitboard_t rook_occupancy(square_t square) {
  bitboard_t result = 0ULL;
  int rank = square / 8;
  int file = square % 8;
  int r, f;
  for (r = rank + 1; r < 7; r++)
    set_bit(result, file_rank_to_square(file, r));
  for (r = rank - 1; r > 0; r--)
    set_bit(result, file_rank_to_square(file, r));
  for (f = file + 1; f < 7; f++)
    set_bit(result, file_rank_to_square(f, rank));
  for (f = file - 1; f > 0; f--)
    set_bit(result, file_rank_to_square(f, rank));
  return result;
}

const int bishop_occupancy_count[SQUARE_COUNT] = {6, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7,
                                                  5, 5, 5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 7,
                                                  7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 6};

bitboard_t bishop_occupancy(square_t square) {
  bitboard_t result = 0ULL;
  int rank = square / 8;
  int file = square % 8;
  int r, f;
  for (r = rank + 1, f = file + 1; r < 7 && f < 7; r++, f++)
    set_bit(result, file_rank_to_square(f, r));
  for (r = rank + 1, f = file - 1; r < 7 && f > 0; r++, f--)
    set_bit(result, file_rank_to_square(f, r));
  for (r = rank - 1, f = file + 1; r > 0 && f < 7; r--, f++)
    set_bit(result, file_rank_to_square(f, r));
  for (r = rank - 1, f = file - 1; r > 0 && f > 0; r--, f--)
    set_bit(result, file_rank_to_square(f, r));
  return result;
}

bitboard_t generate_bishop_attack(square_t square, bitboard_t blockers) {
  bitboard_t result = 0ULL;
  int rank = square / 8;
  int file = square % 8;
  int r, f;
  for (r = rank + 1, f = file + 1; r <= 7 && f <= 7; r++, f++) {
    set_bit(result, file_rank_to_square(f, r));
    if (square_mask(file_rank_to_square(f, r)) & blockers)
      break;
  }
  for (r = rank + 1, f = file - 1; r <= 7 && f >= 0; r++, f--) {
    set_bit(result, file_rank_to_square(f, r));
    if (square_mask(file_rank_to_square(f, r)) & blockers)
      break;
  }
  for (r = rank - 1, f = file + 1; r >= 0 && f <= 7; r--, f++) {
    set_bit(result, file_rank_to_square(f, r));
    if (square_mask(file_rank_to_square(f, r)) & blockers)
      break;
  }
  for (r = rank - 1, f = file - 1; r >= 0 && f >= 0; r--, f--) {
    set_bit(result, file_rank_to_square(f, r));
    if (square_mask(file_rank_to_square(f, r)) & blockers)
      break;
  }
  return result;
}

bitboard_t generate_rook_attack(square_t square, bitboard_t blockers) {
  bitboard_t result = 0ULL;
  int rank = square / 8;
  int file = square % 8;
  int r, f;
  for (r = rank + 1; r <= 7; r++) {
    set_bit(result, file_rank_to_square(file, r));
    if (square_mask(file_rank_to_square(file, r)) & blockers)
      break;
  }
  for (r = rank - 1; r >= 0; r--) {
    set_bit(result, file_rank_to_square(file, r));
    if (square_mask(file_rank_to_square(file, r)) & blockers)
      break;
  }
  for (f = file + 1; f <= 7; f++) {
    set_bit(result, file_rank_to_square(f, rank));
    if (square_mask(file_rank_to_square(f, rank)) & blockers)
      break;
  }
  for (f = file - 1; f >= 0; f--) {
    set_bit(result, file_rank_to_square(f, rank));
    if (square_mask(file_rank_to_square(f, rank)) & blockers)
      break;
  }
  return result;
}

bitboard_t set_occupancy(int index, int bit_count, bitboard_t attack_mask) {
  bitboard_t occupancy = 0ULL;

  for (int i = 0; i < bit_count; i++) {
    square_t square = least_significant_one_bit(attack_mask);
    unset_bit(attack_mask, square);

    if (index & (1 << i)) {
      occupancy |= (1ULL << square);
    }
  }

  return occupancy;
}

bitboard_t generate_magic_number(prng_t *prng) {
  return get_random_number_u64(prng) & get_random_number_u64(prng) & get_random_number_u64(prng);
}

bitboard_t find_magic_number(square_t square, int bit_count, pieces_t piece, prng_t* prng) {
  if (piece != ROOK && piece != BISHOP)
    return -1;
  int is_bishop = piece == BISHOP;
  uint64_t occupancies[4096];
  uint64_t attacks[4096];
  uint64_t used_attacks[4096];
  uint64_t attack_mask = is_bishop ? bishop_occupancy(square) : rook_occupancy(square);

  int occupancy_indices = 1 << bit_count;
  for (int i = 0; i < occupancy_indices; i++) {
    occupancies[i] = set_occupancy(i, bit_count, attack_mask);
    attacks[i] =
        is_bishop ? generate_bishop_attack(square, occupancies[i]) : generate_rook_attack(square, occupancies[i]);
  }

  for (int i = 0; i < 100000000; i++) {
    bitboard_t magic_number = generate_magic_number(prng);
    if (population_count((attack_mask * magic_number) & 0xFF00000000000000) < 6)
      continue;
    memset(used_attacks, 0ULL, sizeof(used_attacks));

    int fail = 0;
    for (int i = 0; !fail && i < occupancy_indices; i++) {
      int magic_index = (int)((occupancies[i] * magic_number) >> (64 - bit_count));
      if (used_attacks[magic_index] == 0ULL) {
        used_attacks[magic_index] = attacks[i];
      } else if (used_attacks[magic_index] != attacks[i]) {
        fail = 1;
      }
    }
    if (!fail) {
      return magic_number;
    }
  }
  return 0ULL;
}

void init_magic() {
  prng_t prng = create_random_generator();
  printf("\n============== Rook Magic Numbers ==============\n");
  for (int i = 0; i < SQUARE_COUNT; i++) {
    printf("0x%llxULL\n", find_magic_number(i, rook_occupancy_count[i], ROOK, &prng));
  }
  printf("\n============== Bishop Magic Numbers ==============\n");
  for (int i = 0; i < SQUARE_COUNT; i++) {
    printf("0x%llxULL\n", find_magic_number(i, bishop_occupancy_count[i], BISHOP, &prng));
  }

}
