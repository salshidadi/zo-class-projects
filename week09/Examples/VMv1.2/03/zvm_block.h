#ifndef __ZVM_BLOCK_H__
#define __ZVM_BLOCK_H__

#define ZVM_BLOCK_MAX_SIZE   ((1024 * 1024 * 1024) / 4)
#define zvm_block_is_valid_size(b) ((b) > 0 && ((b) <= ZVM_BLOCK_MAX_SIZE))

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define zvm_block_init(b, es, ec) \
    (b)->offset = -1; \
    (b)->element_size = (es); \
    (b)->element_count = (ec); \
    memset((b)->base, 0, zvm_block_size((b)));

#define zvm_block_get(b)     ((b)->base[(b)->offset])
#define zvm_block_set(b, v)  ((b)->base[(b)->offset]) = (v)

#define zvm_block_size(b)              ((b)->element_size * (b)->element_count)
#define zvm_block_elements_count(b)    ((b)->element_count)

#define zvm_block_is_offset(b)  (((b)->offset < zvm_block_size((b))) && ((b)->offset >= 0))


typedef struct zvm_block_t zvm_block_t;
typedef int32_t zvm_block_offset_t;
typedef uint16_t zvm_block_count_t;

#define ZVM_BLOCK_FLAG_IS_ALLOCATED      1
#define ZVM_BLOCK_FLAG_IS_ALLOCATED_BASE 2


struct zvm_block_t{
   uint8_t *base;
   zvm_block_count_t element_count;
   uint8_t element_size;
   zvm_block_offset_t offset;
   uint8_t flags;
};

zvm_block_t * zvm_block_new(zvm_block_count_t size, uint8_t element_size);
void zvm_block_delete(zvm_block_t *block);

bool zvm_block_step(zvm_block_t *block);

#endif