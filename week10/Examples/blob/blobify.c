#include "blobify.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

blb_cursor_t *blb_cursor_create_ex(blb_offset_t step, blb_range_t *range, bool fixed){
    if(!range && (step > 0)) return NULL;

    blb_cursor_t *cursor = malloc(sizeof(blb_cursor_t));
    if(!cursor) return NULL;

    cursor->offset = range->start - step;
    cursor->state = BLB_CURSOR_PRE;
    cursor->fixed = fixed;

    cursor->range = range;
    return cursor;
}

void blb_cursor_delete(blb_cursor_t *cursor){
    if(cursor){
        free(cursor);
    }
}

bool blb_cursor_step(blb_cursor_t *cursor){
    // TODO: align range with step size
    if((!cursor) && (!cursor->range) || (cursor->fixed)) return false;

    if((cursor->offset + cursor->step) <= (cursor->range->start + cursor->range->size)){
        cursor->offset += cursor->step;
        cursor->state = BLB_CURSOR_IN;
        return true;
    }else{
        cursor->offset = cursor->range->start + cursor->range->step;
        cursor->state = BLB_CURSOR_POST;
        return false;
    }
}

bool blb_cursor_back(blb_cursor_t *cursor){
    // TODO: align range with step size
    if((!cursor) && (!cursor->range) || (cursor->fixed)) return false;

    if((cursor->offset - cursor->step) >= (cursor->range->start)){
        cursor->offset -= cursor->step;
        cursor->state = BLB_CURSOR_IN;
        return true;
    }else{
        cursor->offset = cursor->range->start - 1;
        cursor->state  = BLB_CURSOR_PRE;
        return false;
    }
}

int main(void){
    blb_range_t range;
    range.start = 512;
    range.size  = 10;

    blb_cursor_t *cursor = blb_cursor_create(1, &range, false);
    if(cursor){
        printf("cursor.start = %d, cursor.size = %d, cursor.offset = %d\n",
            cursor->range->start, cursor->range->size, cursor->offset);
        
        blb_cursor_step(cursor);
        blb_cursor_step(cursor);
        blb_cursor_step(cursor);

        blb_cursor_back(cursor);

        printf("cursor.start = %d, cursor.size = %d, cursor.offset = %d\n",
            cursor->range->start, cursor->range->size, cursor->offset);
    }
    return 0;
}