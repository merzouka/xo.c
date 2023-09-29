#include "common.h"
#include "core.h"
#include "computer.h"
#include "helpers.h"
#include "io.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <threads.h>
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

PositionAlignments *create(int pos, int aligns){
    PositionAlignments *result = malloc(sizeof(PositionAlignments));
    *result = (PositionAlignments){.pos = pos, .aligns = aligns, .next = NULL};
    return result;
}

PositionAlignments *append(PositionAlignments *head, int pos, int aligns){
    if (head == NULL){
        return NULL;
    }

    if (head->next == NULL){
        head->next = create(pos, aligns);
        return head->next;
    }
    return append(head->next, aligns, pos);
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

bool containsPos(PositionAlignments *haystack, int needle){
    for (PositionAlignments *x = haystack; x != NULL; x = x->next){
        if (x->pos == needle){
            return true;
        }
    }
    return false;
}

void printList(PositionAlignments *head){
    for (PositionAlignments *x = head; x != NULL; x = x->next){
        printf("(%d, %d) ", x->pos, x->aligns);
    }
    printf("\n");
}

void freeList(PositionAlignments *head){
    if (head != NULL){
        freeList(head->next);
        free(head);
    }
}

PositionAlignments *merge(size_t num, ...){
    va_list lists;
    va_start(lists, num);
    // -1 is not a valid position and all positions > -1
    PositionAlignments *result = create(-1, 0);
    for (size_t i = 0; i < num; i++){
        PositionAlignments *head = va_arg(lists, PositionAlignments *);
        for (PositionAlignments *p1= head; p1!= NULL; p1= p1->next){
            PositionAlignments *p2= result;
            for (;p2->next != NULL && p1->pos >= p2->next->pos; p2= p2->next){}
            if (p2->pos == p1->pos){
                continue; 
            }
            PositionAlignments *p3 = p2->next;
            p2->next = create(p1->pos, p1->aligns); p2 = p2->next; p2->next = p3;
        }
    }
    va_end(lists);
    PositionAlignments *p = result->next; free(result);
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

bool firstMove(char table[3][3]){
    // search starts from both table ends
    int xCount = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (table[i][j] == 'o'){
                return false;
            }
            if (table[i][j] == 'x'){
                xCount++;
                if (xCount > 1){
                    return false;
                }
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

bool colFilled(char table[3][3], int col, char player){
    for (int i = 0; i < 3; i++){
        if (table[i][col] != player){
            return false;
        }
    }
    return true;
}

bool rowFilled(char table[3][3], int row, char player){
    for (int j = 0; j < 3; j++){
        if (table[row][j] != player){
            return false;
        }
    }
    return true;
}

bool diagFilled(char table[3][3], int diagonal, char player){
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

bool hasFilled(char table[3][3], int position, char player){
    return 
        colFilled(table, col(position), player) ||
        rowFilled(table, row(position), player) ||
        diagFilled(table, diagonal(position), player) ||
        // check the diagonal 1-5-9
        (position == 5 ? diagFilled(table, -1, player) : 0);
}

char other(char player){
    return player == 'x' ? 'o' : (player == 'o' ? 'x' : ' ');
}

bool hasRowAlignment(char table[3][3], int pos, char player){
    bool has = false;
    int c = col(pos); int r = row(pos);
    for (int j = 0; j < 3; j++){
        if (j != c){
            if (table[r][j] == player){
                has = true; continue;
            }
            if (table[r][j] == other(player)){
                return false;
            }
        }
    }
    return has;
}

bool hasColAlignment(char table[3][3], int pos, char player){
    bool has = false;
    int c = col(pos); int r = row(pos);
    for (int i = 0; i < 3; i++){
        if (i != r){
            if (table[i][c] == player){
                has = true; continue;
            }
            if (table[i][c] == other(player)){
                return false;
            }
        }
    }
    return has;
}

int diagAlignments(char table[3][3], int pos, char player){
    bool hasMainAlignment = false;
    bool hasSecondAlignment = false;
    int d = diagonal(pos);
    if (d == 1){
        for (int i = 0; i < 3; i++){
            if (position(i, i) != pos){
                if (table[i][i] == player){
                    hasMainAlignment = true; continue;
                }
                if (table[i][i] == other(player)){
                    hasMainAlignment = false; break;
                }
            }
        }
    }
    
    d = pos == 5 ? -1 : d;
    if (d == -1){
        for (int i = 0; i < 3; i++){
            if (position(i, 2 - i) != pos){
                if (table[i][2 - i] == player){
                    hasSecondAlignment = true; continue;
                }
                if (table[i][2 - i] == other(player)){
                    hasSecondAlignment = false; break;
                }
            }
        }
    }

    return (hasMainAlignment ? 1 : 0) + (hasSecondAlignment ? 1 : 0); 
}

int alignments(char table[3][3], int position, char player){
    return 
        (hasRowAlignment(table, position, player) ? 1 : 0) +
        (hasColAlignment(table, position, player) ? 1 : 0) +
        diagAlignments(table, position, player);
}

size_t len(PositionAlignments *head){
    size_t len = 0;
    for (PositionAlignments *x = head; x != NULL; x = x->next, len++);
    return len;
}

PositionAlignments *max(PositionAlignments *head){
    PositionAlignments *m = head;
    for (PositionAlignments *x = head; x != NULL; x = x->next){
        if (m->aligns < x->aligns){
            m = x; 
        }
    }
    return m;
}

PositionAlignments *allAlignments(char table[3][3], char player){
    PositionAlignments *x, *head = NULL;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (table[i][j] == PLACEHOLDER){
                int p = position(i, j);
                if (head == NULL){
                    head = create(p, alignments(table, p, player)); x = head; continue;
                }
                x = append(x, p, alignments(table, p, player));
            }
        }
    }
    return head;
}

PositionAlignments *getDoubleAlignment(PositionAlignments *head){
    for (PositionAlignments *x = head; x != NULL; x = x->next){
        if (x->aligns == 2){
            return x;
        }
    }
    return NULL;
}

void getListPositions(PositionAlignments *head, int arr[]){
    int i = 0;
    for (PositionAlignments *x = head; x != NULL; x = x->next, i++){
        arr[i] = x->pos;
    }
}

PositionAlignments *maxoccurs(PositionAlignments *head){
    if (head == NULL){
        return NULL;
    }
    int maxAligns = max(head)->aligns;
    PositionAlignments *result = NULL;
    for (PositionAlignments *x = head; x != NULL; x = x->next){
        PositionAlignments *last;
        if (x->aligns == maxAligns){
            if (result == NULL){
                result = create(x->pos, x->aligns); last = result; continue;
            }
            last = append(last, x->pos, x->aligns);
        }
    }
    return result;
}

bool rowBlock(char table[3][3], int pos, char player){
    int c = col(pos); int r = row(pos);
    for (int j = 0; j < 3; j++){
        if (j != c){
            if (table[r][j] != other(player)){
                return false;
            }
        }
    }
    return true;
}

bool colBlock(char table[3][3], int pos, char player){
    int c = col(pos); int r = row(pos);
    for (int i = 0; i < 3; i++){
        if (i != r){
            if (table[i][c] != other(player)){
                return false;
            }
        }
    }
    return true;
}

bool diagBlock(char table[3][3], int pos, char player){
    int d = diagonal(pos); bool mainDiagBlock = d == 1;
    if (d == 1){
        for (int i = 0; i < 3; i++){
            if (position(i, i) != pos){
                if (table[i][i] != other(player)){
                    mainDiagBlock = false; break;
                }
            }
        }
        if (mainDiagBlock){
            return true;
        }
    }

    d = pos == 5 ? -1 : d;
    bool secondDiagBlock = d == -1;
    if (d == -1){
        for (int i = 0; i < 3; i++){
            if (position(i, 2 - i) != pos){
                if (table[i][2 - i] != other(player)){
                    secondDiagBlock = false; break;
                }
            }
        }
    }

    return mainDiagBlock || secondDiagBlock;
}

bool block(char table[3][3], int pos, char player){
    return 
        rowBlock(table, pos, player) ||
        colBlock(table, pos, player) ||
        diagBlock(table, pos, player);
}

int arrmaxind(int arr[], size_t len){
    int maxind = 0;
    for (int i = 0; i < len; i++){
        if (arr[maxind] < arr[i]){
            maxind = i;
        }
    }
    return maxind;
}

int arrminind(int arr[], size_t len){
    int minind = 0;
    for (int i = 0; i < len; i++){
        if (arr[minind] > arr[i]){
            minind = i;
        }
    }
    return minind;
}

int next(char table[3][3], char player){
    // at start
    if (firstMove(table)){
        if (player == 'o' && table[1][1] == PLACEHOLDER){
            return 5;
        }
        int corners[] = {1, 3, 7, 9};
        srand(time(NULL));
        return corners[rand() % 4];
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

    PositionAlignments *alignsListHead = allAlignments(table, player);
    if (alignsListHead == NULL){
        return -1;
    }

    // move has double alignments, i.e certain win
    PositionAlignments *doubleAlign = getDoubleAlignment(alignsListHead);
    if (doubleAlign != NULL){
        int pos = doubleAlign->pos; freeList(alignsListHead); 
        return pos;
    }

    // only consider options with max alignments
    PositionAlignments *tmp = maxoccurs(alignsListHead);
    freeList(alignsListHead); alignsListHead = tmp;

    // only one move
    if (len(alignsListHead) == 1){
        int pos = alignsListHead->aligns; freeList(alignsListHead); 
        return pos;
    }

    // all positions lead to a tie
    if (alignsListHead->aligns == 0){
        int pos = alignsListHead->pos; freeList(alignsListHead);
        return pos;
    }

    int l = len(alignsListHead);
    int positions[l];
    getListPositions(alignsListHead, positions);
    freeList(alignsListHead);

    int positionMovesToWin[l];
    int freeMovesAfterPosition[l];

    for (int i = 0; i < 3; i++){
        char decoy[3][3]; cpy(table, decoy); setsqr(decoy, positions[i], player);
        char virtual = other(player); int movesToWin = 0, freeMoves = 0;
        while (true){
            int nextPosition = next(decoy, virtual); setsqr(decoy, nextPosition, virtual);
            if (virtual == player){
                movesToWin++;
                if (hasFilled(decoy, nextPosition, player)){
                    positionMovesToWin[i] = movesToWin; freeMovesAfterPosition[i] = freeMoves;
                    break;
                }
                if (block(decoy, nextPosition, player)){
                    freeMovesAfterPosition[i] = freeMoves;
                    // there can only be 9 moves total
                    positionMovesToWin[i] = 10; break;
                }
                freeMoves++;
            }
            if (hasFilled(table, nextPosition, other(player))){
                positionMovesToWin[i] = 10; freeMovesAfterPosition[i] = -1;
                break;
            }
            if (tie(decoy)){
                freeMovesAfterPosition[i] = freeMoves; positionMovesToWin[i] = movesToWin;
                break;
            }
            virtual = other(virtual);
        }
    }

    // get most optimal position index by most free moves
    int optimalIndexByFreeMoves = arrmaxind(freeMovesAfterPosition, l);
    if (positionMovesToWin[optimalIndexByFreeMoves] != -1){
        return positions[optimalIndexByFreeMoves];
    }

    int optimalIndexByWins = arrminind(positionMovesToWin, l);
    return positions[optimalIndexByWins];
}

void startPvE(char table[3][3]){
    init(table);
    char player;
    do {
        printf(BOLD"choose player (%sx%s/%so"EXIT"): ", LIGHT_RED, EXIT, BOLD""GREEN);
        player = getchar(); 
        // break line
        getchar();
    } while (player != 'x' && player != 'o');
    char env = other(player);
    char current = 'x';
    while (true){
        clrscr(); print(table);
        if (current == env){
            setsqr(table, next(table, env), env);
        } else {
            printf("%s%c"EXIT" chooses: ", player == 'x' ? LIGHT_RED : GREEN, player);
            int position = readint("");
            if (!valid(table, position)){
                continue;
            }
            setsqr(table, position, player);
        }

        if (wins(table, current)){
            printf(BOLD"%s"EXIT""BOLD" wins.\n"EXIT, current == env ? LIGHT_RED"computer" : GREEN"player");
            break;
        }

        if (tie(table)){
            clrscr(); printf(BOLD""GRAY"tie.\n"EXIT);
            break;
        }
        current = other(current);
    }
}

