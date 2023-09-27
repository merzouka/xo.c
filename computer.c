#include "common.h"
#include "core.h"
#include "computer.h"
#include "helpers.h"

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

int completeRow(char table[3][3], char player){
    for (int i = 0; i < 3; i++){
        int empty = -1;
        for (int j = 0; j < 3; j++){
            FILL_EMPTY(i, j, j, empty);
        }
        if (empty != -1){
            return position(i, empty);
        }
    }
    return -1;
}

int completeCol(char table[3][3], char player){
    for (int j = 0; j < 3; j++){
        int empty = -1;
        for (int i = 0; i < 3; i++){
            FILL_EMPTY(i, j, i, empty);
        }
        if (empty != -1){
            return position(empty, j);
        }
    }
    return -1;
}

int completeDiag(char table[3][3], char player){
    // diagonal 7-5-3
    int empty = -1;
    for (int i = 0; i < 3; i++){
        FILL_EMPTY(i, i, i, empty);
    }
    if (empty != -1){
        return position(empty, empty);
    }

    // diagonal 1-5-9
    empty = -1;
    for (int i = 0; i < 3; i++){
        FILL_EMPTY(i, 2 - i, i, empty)
    }
    if (empty != -1){
        return position(empty, 2 - empty);
    }
    return -1;
}

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

int complete(char table[3][3], char player){
    int positions[] = {
        completeRow(table, player), completeCol(table, player), completeDiag(table, player)
    };
    for (int i = 0; i < 3; i++){
        if (positions[i] != -1){
            return positions[i];
        }
    }
    return -1;
}

bool empty(char table[3][3]){
    // search starts from both table ends
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 3 && !(position(i, j) == 5); j++){
            if (table[i][j] != PLACEHOLDER || table[2 - i][2 - j] != PLACEHOLDER){
                return false;
            }
        }
    }
    return true;
}

void cpy(char table[3][3], char copy[3][3]){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            copy[i][j] = table[i][j];
        }
    }
}

int diagonal(int position){
    if (contains(3, (int[]){7, 5, 3}, position)){
        return 1;
    }
    return contains(3, (int[]){1, 5, 9}, position) ? -1 : 0;
}

bool lineAtCol(char table[3][3], int col, char player){
    for (int i = 0; i < 3; i++){
        if (table[i][col] != player){
            return false;
        }
    }
    return true;
}

bool lineAtRow(char table[3][3], int row, char player){
    for (int j = 0; j < 3; j++){
        if (table[row][j] != player){
            return false;
        }
    }
    return true;
}

bool lineAtDiag(char table[3][3], int diagonal, char player){
    if (diagonal == 0){
        return false;
    }
    for (int i = 0; i < 3; i++){
        if (table[i][diagonal == 1 ? i : 2 - i] != player){
            return false;
        }
    }
    return true;
}

bool lineAt(char table[3][3], int position, char player){
    return 
        lineAtCol(table, col(position), player) ||
        lineAtRow(table, row(position), player) ||
        lineAtDiag(table, diagonal(position), player) ||
        // check the diagonal 1-5-9
        (position == 5 ? lineAtDiag(table, -1, player) : 0);
}

bool other(char player){
    return player == 'x' ? 'o' : 'o';
}

int connections(char table[3][3], int position, char player){
    return 0;    
}

int next(char table[3][3], char player){
    // start
    if (empty(table)){
        if (player == 'o'){
            return 5;
        }
        if (player == 'x'){
            int corners[] = {1, 3, 7, 9};
            srand(time(NULL));
            return corners[rand() % 4];
        }
    }

    // finish
    int finish = complete(table, player);
    if (finish != -1){
        return finish;
    }

    // defense
    finish = complete(table, other(player));
    if (finish != -1){
        return finish;
    }

    int emptyPosition = -1;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (table[i][j] == PLACEHOLDER){
                char decoy[3][3]; cpy(table, decoy); decoy[i][j] = player;
                char virtual = other(player);
                emptyPosition = position(i, j);
                while (true){
                    int pos = next(decoy, virtual); setsqr(decoy, pos, virtual);
                    if (lineAt(decoy, pos, virtual) || tie(decoy)){
                        if (virtual == player){
                            return position(i, j);
                        }
                        break;
                    }
                    virtual = other(virtual);
                }
            }
        }
    }
    return emptyPosition;
}

int main(){
    char table[][3] = {
        {'x', 'o', ' '},
        {'o', ' ', ' '},
        {'x', ' ', ' '},
    };
    printf("next: %d\n", next(table, 'x'));

    return 0;
}


