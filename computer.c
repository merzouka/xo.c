#include "common.h"
#include "core.h"
#include "computer.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>

/* Macro: sets var to value if table[row][col] should be filled
 *
 * @param row cell row
 * @param col cell row
 * @param value value to use
 * @param var variable to be set
 * */
#define FILL_EMPTY(row, col, value, var) \
            if (table[row][col] == PLACEHOLDER){\
                if (var != -1){\
                    var = -1; break;\
                }\
                var = value; continue;\
            }\
            if (table[row][col] != player){\
                var = -1; break;\
            }

Position *create(int pos){
    Position *result = malloc(sizeof(Position));
    *result = (Position){.pos = pos, .next = NULL};
    return result;
}

Position *append(Position *head, int pos){
    if (head == NULL){
        return NULL;
    }
    if (head->next == NULL){
        head->next = create(pos);
        return head->next;
    }
    return append(head->next, pos);
}

Position *completeRow(char table[3][3], char player){
    Position *head = create(-1);
    Position *x = head;
    for (int i = 0; i < 3; i++){
        int empty = -1;
        for (int j = 0; j < 3; j++){
            FILL_EMPTY(i, j, j, empty);
        }
        if (empty != -1){
            x = append(x, position(i, empty));
        }
    }
    x = head->next; free(head); 
    return x;
}

Position *completeCol(char table[3][3], char player){
    Position *head = create(-1); Position *x = head;
    for (int j = 0; j < 3; j++){
        int empty = -1;
        for (int i = 0; i < 3; i++){
            FILL_EMPTY(i, j, i, empty);
        }
        if (empty != -1){
            x = append(x, position(empty, j));
        }
    }
    x = head->next; free(head);
    return x;
}

Position *completeDiag(char table[3][3], char player){
    // diagonal 7-5-3
    Position *head = create(-1); Position *x = head;
    int empty = -1;
    for (int i = 0; i < 3; i++){
        FILL_EMPTY(i, i, i, empty);
    }
    if (empty != -1){
        x = append(x, position(empty, empty));
    }

    // diagonal 1-5-9
    for (int i = 0; i < 3; i++){
        FILL_EMPTY(i, 2 - i, i, empty)
    }
    if (empty != -1){
        x = append(x, position(empty, 2 - empty));
    }
    x = head->next; free(head);
    return x;
}

// add complete function

bool containsPos(Position *haystack, int needle){
    for (Position *x = haystack; x != NULL; x = x->next){
        if (x->pos == needle){
            return true;
        }
    }
    return false;
}

void printPositionList(Position *head){
    for (Position *x = head; x != NULL; x = x->next){
        printf("%d ", x->pos);
    }
    printf("\n");
}

void freePositionList(Position *head){
    if (head != NULL){
        freePositionList(head->next);
        free(head);
    }
}

Position *merge(size_t num, ...){
    va_list lists;
    va_start(lists, num);
    // -1 is not a valid position and all positions > -1
    Position *result = create(-1);
    for (size_t i = 0; i < num; i++){
        Position *head = va_arg(lists, Position *);
        for (Position *p1= head; p1!= NULL; p1= p1->next){
            Position *p2= result;
            for (;p2->next != NULL && p1->pos >= p2->next->pos; p2= p2->next){}
            if (p2->pos == p1->pos){
                continue; 
            }
            Position *p3 = p2->next;
            p2->next = create(p1->pos); p2 = p2->next; p2->next = p3;
        }
    }
    va_end(lists);
    Position *p = result->next; free(result);
    return p;
}

int main(){
    char table[][3] = {
        {'x', 'x', 'x'},
        {' ', 'x', ' '},
        {'x', ' ', ' '},
    };

    return 0;
}


