#ifndef __ZVM_BLOCK_H__
#define __ZVM_BLOCK_H__

#define ZVM_BLOCK_MAX_SIZE   ((1024 * 1024 * 1024) / 4)
#define ZVM_BLOCK_OFFSET_INIT_VALUE -1

#define zvm_block_is_valid_size(b) ((b) > 0 && ((b) <= ZVM_BLOCK_MAX_SIZE))

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define zvm_block_init(b, es, ec) \
    (b)->offset = ZVM_BLOCK_OFFSET_INIT_VALUE; \
    (b)->element_size = (es); \
    (b)->element_count = (ec); \
    (b)->size = (es) * (ec); \
    memset((b)->base, 0, (b)->size);

#define zvm_block_get_offset(b)  (b)->offset

// #define zvm_block_get(b)     ((b)->base[(b)->offset])
// #define zvm_block_set(b, v)  ((b)->base[(b)->offset]) = (v)

#define zvm_block_size(b)              ((b)->size)
#define zvm_block_elements_count(b)    ((b)->element_count)

#define zvm_block_is_offset(b, off)  ((off) >= 0 && (off) < (b)->size)
#define zvm_block_is_accessable(b)   \
    (((b)!= NULL) && ((b)->base != NULL) && (zvm_block_is_offset((b), (b)->offset)))

// TODO: check for NULL block
#define zvm_block_rewind(b)  (b)->offset = -1
#define zvm_block_first(b)   (b)->offset = 0
#define zvm_block_last(b)    ((b)->offset = (b)->size - 1)

#define zvm_block_is_overflow(b)   ((b)->offset >= (b)->size)
#define zvm_block_is_underflow(b)  ((b)->offset < 0)


typedef struct zvm_block_t zvm_block_t;
typedef struct zvm_block_range_t zvm_block_range_t;

typedef int32_t zvm_block_offset_t;
typedef uint16_t zvm_block_count_t;

struct zvm_block_range_t {
    char *name;
    zvm_block_offset_t start;
    zvm_block_offset_t size;
};

#define ZVM_BLOCK_MAX_RANGE 32

struct zvm_block_t{
   uint8_t *base;
   uint32_t size;
   zvm_block_offset_t offset;

   zvm_block_count_t element_count;
   uint8_t element_size;
   zvm_block_range_t ranges[ZVM_BLOCK_MAX_RANGE]; 
};

zvm_block_t * zvm_block_new(zvm_block_count_t size, uint8_t element_size);
bool zvm_block_delete(zvm_block_t *block);

bool zvm_block_step(zvm_block_t *block, zvm_block_offset_t to);
bool zvm_block_move(zvm_block_t *block, zvm_block_offset_t to);

bool zvm_block_put(zvm_block_t *block, uint8_t value);
bool zvm_block_get(zvm_block_t *block, uint8_t *value);

bool zvm_block_push(zvm_block_t *block, uint8_t value);
bool zvm_block_pop(zvm_block_t *block, uint8_t *value);

#endif
