#include "zvm_block.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

zvm_block_t * zvm_block_new(zvm_block_count_t elements_count, uint8_t element_size){
    if(!zvm_block_is_valid_size(element_size * elements_count)){
        return NULL;
    }

    zvm_block_t *block = (zvm_block_t*)malloc(sizeof(zvm_block_t));
    if(block){
        block->base = (uint8_t*)malloc((element_size) * (elements_count));
        if(!block->base){
            free(block);
            return NULL;
        }
    }else return NULL;
    
    block->flags = ZVM_BLOCK_FLAG_IS_ALLOCATED | ZVM_BLOCK_FLAG_IS_ALLOCATED_BASE;
    zvm_block_init(block, element_size, elements_count);
    return block;
}

bool zvm_block_delete(zvm_block_t *block){
    if(!block) return false;

    if(block->base && ((block->flags & ZVM_BLOCK_FLAG_IS_ALLOCATED_BASE)))
        free(block->base);

    if((block->flags & ZVM_BLOCK_FLAG_IS_ALLOCATED)) free(block);
}

static uint8_t values[4] = {1, 2, 3, 4};

int main(void){
    zvm_block_t blk, *ptr;
    blk.base = &values;
    blk.element_count = 4;
    blk.element_size = 1;
    blk.offset = -1;

    zvm_block_delete(&blk);

    return 0;
}