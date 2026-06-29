#ifndef __BLOBIFY_H__
#define __BLOBIFY_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct blb_t blb_t;
typedef struct blb_cursor_t blb_cursor_t;
typedef struct blb_range_t blb_range_t;

typedef int32_t blb_offset_t;


#define BLB_CURSOR_PRE      -1
#define BLB_CURSOR_IN        0
#define BLB_CURSOR_POST      1

struct blb_cursor_t{
    blb_offset_t offset;
    blb_range_t *range;
    int8_t state;
    bool fixed;
};

blb_cursor_t *blb_cursor_create_ex(blb_range_t *range, bool fixed);
#define blb_cursor_create(step, range, fixed)  blb_cursor_create_ex(step, range, fixed)
void blb_cursor_delete(blb_cursor_t *cursor);

bool blb_cursor_step(blb_cursor_t *cursor);
bool blb_cursor_back(blb_cursor_t *cursor);


struct blb_range_t{
    blb_offset_t start;
    blb_offset_t size;
    blb_offset_t step;
};

struct zvm_block_t{
   uint8_t *base;
   uint32_t size;
   
   blb_range_t range;
   blb_cursor_t cursor;

//    zvm_block_count_t element_count;
//    uint8_t element_size;
};


#endif
