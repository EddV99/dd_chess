#ifndef DD_MOVE_H_
#define DD_MOVE_H_

#include "common.h"
#include <stdint.h>

#define MOVE_CAPTURE_FLAG ((uint16_t)0x0001)
#define MOVE_PROMOTION_KNIGHT_FLAG ((uint16_t)0x0002)
#define MOVE_PROMOTION_BISHOP_FLAG ((uint16_t)0x0004)
#define MOVE_PROMOTION_ROOK_FLAG ((uint16_t)0x0008)
#define MOVE_PROMOTION_QUEEN_FLAG ((uint16_t)0x0010)
#define MOVE_EN_PASSANT_FLAG ((uint16_t)0x0020)

typedef struct {
  square_t from;
  square_t target;
  uint8_t flags;
} move_t;

#endif
