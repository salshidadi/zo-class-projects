#include <stdio.h>
#include <stdlib.h>

typedef struct point point;

struct point {
    int x;
    int y;
    point *next;
};

point* create_point(int x, int y){
    point *p = malloc(sizeof(point));
    if(p == NULL) return NULL;

    p->x = x;
    p->y = y;
    p->next = NULL;
    return p;
}

void free_point(point *p){
    if(p != NULL){
        free(p);
    }
}

void insert_point(point *head, point *p){
    if(head != NULL && p != NULL){
        point *ptr = head;
        while(ptr->next != NULL){
            ptr = ptr->next;
        }

        ptr->next = p;
    }
}

void print_point(point *head){
    if(head != NULL){
        point *ptr = head;
        while(ptr != NULL){
            printf("%p -> (x: %d, y: %d)\n",
            ptr, ptr->x, ptr->y);
            ptr = ptr->next;
        }
    }
}

void delete_points(point *head){
    if(head == NULL) return;
    point *target = NULL, *ptr = head;
    while(ptr != NULL){
        target = ptr;
        ptr = ptr->next;
        free_point(target);
    }
}

int main(void){
    point *head = create_point(10, 20);
    // head->next = create_point(15, 33);
    // head->next->next = create_point(44, 18);

    insert_point(head, create_point(15, 33));
    insert_point(head, create_point(44, 18));

    print_point(head);

    // free_point(head->next->next);
    // free_point(head->next);
    // free_point(head);

    delete_points(head);
    return 0;
}
