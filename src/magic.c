#include "magic.h"
#include "common.h"
#include "prng.h"

#include <stdio.h>
#include <string.h>

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

bitboard_t find_magic_number(square_t square, int bit_count, pieces_t piece, prng_t *prng) {
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
    printf("0x%016lxULL\n", find_magic_number(i, rook_occupancy_count[i], ROOK, &prng));
  }
  printf("\n============== Bishop Magic Numbers ==============\n");
  for (int i = 0; i < SQUARE_COUNT; i++) {
    printf("0x%016lxULL\n", find_magic_number(i, bishop_occupancy_count[i], BISHOP, &prng));
  }
}

const bitboard_t ROOK_MAGICS[SQUARE_COUNT] = {
    0x8a80104000800020ULL, 0x0140002000100040ULL, 0x02801880a0017001ULL, 0x0100081001000420ULL, 0x0200020010080420ULL,
    0x03001c0002010008ULL, 0x8480008002000100ULL, 0x2080088004402900ULL, 0x0000800098204000ULL, 0x2024401000200040ULL,
    0x0100802000801000ULL, 0x0120800800801000ULL, 0x0208808088000400ULL, 0x0002802200800400ULL, 0x2200800100020080ULL,
    0x0801000060821100ULL, 0x0080044006422000ULL, 0x0100808020004000ULL, 0x12108a0010204200ULL, 0x0140848010000802ULL,
    0x0481828014002800ULL, 0x8094004002004100ULL, 0x4010040010010802ULL, 0x0000020008806104ULL, 0x0100400080208000ULL,
    0x2040002120081000ULL, 0x0021200680100081ULL, 0x0020100080080080ULL, 0x0002000a00200410ULL, 0x0000020080800400ULL,
    0x0080088400100102ULL, 0x0080004600042881ULL, 0x4040008040800020ULL, 0x0440003000200801ULL, 0x0004200011004500ULL,
    0x0188020010100100ULL, 0x0014800401802800ULL, 0x2080040080800200ULL, 0x0124080204001001ULL, 0x0200046502000484ULL,
    0x0480400080088020ULL, 0x1000422010034000ULL, 0x0030200100110040ULL, 0x0000100021010009ULL, 0x2002080100110004ULL,
    0x0202008004008002ULL, 0x0020020004010100ULL, 0x2048440040820001ULL, 0x0101002200408200ULL, 0x0040802000401080ULL,
    0x4008142004410100ULL, 0x02060820c0120200ULL, 0x0001001004080100ULL, 0x020c020080040080ULL, 0x2935610830022400ULL,
    0x0044440041009200ULL, 0x0280001040802101ULL, 0x2100190040002085ULL, 0x80c0084100102001ULL, 0x4024081001000421ULL,
    0x00020030a0244872ULL, 0x0012001008414402ULL, 0x02006104900a0804ULL, 0x0001004081002402ULL

};
const bitboard_t BISHOP_MAGICS[SQUARE_COUNT] = {
    0x0040040844404084ULL, 0x002004208a004208ULL, 0x0010190041080202ULL, 0x0108060845042010ULL, 0x0581104180800210ULL,
    0x2112080446200010ULL, 0x1080820820060210ULL, 0x03c0808410220200ULL, 0x0004050404440404ULL, 0x0000021001420088ULL,
    0x24d0080801082102ULL, 0x0001020a0a020400ULL, 0x0000040308200402ULL, 0x0004011002100800ULL, 0x0401484104104005ULL,
    0x0801010402020200ULL, 0x00400210c3880100ULL, 0x0404022024108200ULL, 0x0810018200204102ULL, 0x0004002801a02003ULL,
    0x0085040820080400ULL, 0x810102c808880400ULL, 0x000e900410884800ULL, 0x8002020480840102ULL, 0x0220200865090201ULL,
    0x2010100a02021202ULL, 0x0152048408022401ULL, 0x0020080002081110ULL, 0x4001001021004000ULL, 0x800040400a011002ULL,
    0x00e4004081011002ULL, 0x001c004001012080ULL, 0x8004200962a00220ULL, 0x8422100208500202ULL, 0x2000402200300c08ULL,
    0x8646020080080080ULL, 0x80020a0200100808ULL, 0x2010004880111000ULL, 0x623000a080011400ULL, 0x42008c0340209202ULL,
    0x0209188240001000ULL, 0x400408a884001800ULL, 0x00110400a6080400ULL, 0x1840060a44020800ULL, 0x0090080104000041ULL,
    0x0201011000808101ULL, 0x1a2208080504f080ULL, 0x8012020600211212ULL, 0x0500861011240000ULL, 0x0180806108200800ULL,
    0x4000020e01040044ULL, 0x300000261044000aULL, 0x0802241102020002ULL, 0x0020906061210001ULL, 0x5a84841004010310ULL,
    0x0004010801011c04ULL, 0x000a010109502200ULL, 0x0000004a02012000ULL, 0x500201010098b028ULL, 0x8040002811040900ULL,
    0x0028000010020204ULL, 0x06000020202d0240ULL, 0x8918844842082200ULL, 0x4010011029020020ULL};
