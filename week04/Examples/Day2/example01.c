#include <stdio.h>

typedef struct node node_t;
struct node{
    void *data;
    unsigned int size;
    struct list *next;
    struct list *previous;
};

typedef struct list list_t;

struct list{
    node_t *first;
    node_t *last;
    unsigned int count;
};

void list_insert_first(list_t* list, node_t *node){
    node->next = list->first;
    list->first = node;
}

node_t* list_copy(node_t* list){
    return NULL;
}


int main(void){
    list_t *lst = malloc(sizeof(list_t));

    node_t *n1 = malloc(sizeof(node_t));
    node_t *n2 = malloc(sizeof(node_t));
    node_t *n3 = malloc(sizeof(node_t));
    node_t *n4 = malloc(sizeof(node_t));


    n1->data = malloc(sizeof(int));
    n2->data = malloc(sizeof(float) * 5);
    n3->data = malloc(sizeof(char) * 15);
    n4->data = malloc(sizeof(node_t));

    return 0;
}
