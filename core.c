#include "core.h"
#include "io.h"
#include "helpers.h"
#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#ifdef _WIN32
#include <windows.h>
#endif /* ifdef _WIN32 */
#ifdef __unix__
#include <unistd.h>
#endif /* ifdef __unix__ */

#define ESC         "\033["
#define RED         ESC"38;5;124m"
#define LIGHT_RED   ESC"38;5;196m"
#define GREEN       ESC"38;5;76m"
#define BLUE        ESC"38;5;45m"
#define GRAY        ESC"38;5;251m"
#define BOLD        ESC"1m"
#define EXIT        ESC"0m"

void clrscr(){
    // system("clear");
    printf("\e[1;1H\e[2J");
}

int row(int position){
    int mod = position % 3;
    int row = 2 - (position / 3 + (mod == 0 ? -1 : 0));
    return row;
}

int col(int position){
    int mod = position % 3;
    int col = mod == 0 ? 2 : mod - 1;
    return col;
}

int position(int row, int col){
    return (2 - row) * 3 + 1 + col;
}

void init(char table[3][3]){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            table[i][j] = PLACEHOLDER;
        }
    }
}

void print(const char table[3][3]) {
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%c", table[i][j]);
            if (j < 2) {
                printf("|");
            }
        }
        printf("\n");
    }
}

void highlight(const char table[3][3], size_t len, int positions[]){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (contains(len, positions, position(i, j))){
                printf(BOLD""BLUE"%c"EXIT, table[i][j]);
            } else {
                printf("%c", table[i][j]);
            }
            if (j < 2){
                printf("|");
            }
        }
        printf("\n");
    }
}

void setsqr(char table[3][3], char player, int position){
    table[row(position)][col(position)] = player;
}

bool valid(char table[3][3], int position){
    if (position <= 9 && position >= 1 && table[row(position)][col(position)] == PLACEHOLDER){
        return true;
    }
    printf(RED""BOLD"invalid position: %d\n"EXIT, position);
    sleep(1);
    return false;
}

bool rowAlignment(char table[3][3], char player){
    bool found;
    int positions[3];
    for (int i = 0; i < 3; i++){
        found = true;
        for (int j = 0; j < 3; j++){
            if (table[i][j] != player){
                found = false; break;
            }
            positions[j] = position(i, j);
        }
        if (found){
            clrscr(); highlight(table, 3, positions);
            break;
        }
    } 
    return found;
}

bool colAlignment(char table[3][3], char player){
    bool found;
    int positions[3];
    for (int j = 0; j < 3; j++){
        found = true;
        for (int i = 0; i < 3; i++){
            if (table[i][j] != player){
                found = false; break;;
            }
            positions[i] = position(i, j);
        }
        if (found){
            clrscr(); highlight(table, 3, positions);
            break;
        }
    }
    return found;
}

bool diagonalAlignment(char table[3][3], char player){
    bool found = true;
    int positions[3];
    // diagonal 7-5-3 
    for (int i = 0; i < 3; i++){
        if (table[i][i] != player){
            found = false; break;
        }
        positions[i] = position(i, i);
    }
    if (found){ 
        clrscr(); highlight(table, 3, positions);
        return true;
    }
    // diagonal 1-5-9
    for (int i = 0; i < 3; i++){
        if (table[i][2 - i] != player){
            return false;
        }
        positions[i] = position(i, 2 - i);
    }
    clrscr(); highlight(table, 3, positions);
    return true;
}

bool wins(char table[3][3], char player){
    return rowAlignment(table, player) || colAlignment(table, player) || diagonalAlignment(table, player);
}

bool tie(char table[3][3]){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (table[i][j] == PLACEHOLDER){
                return false;
            }
        }
    }
    return true;
}

void start(char table[3][3]){
    init(table);
    char player = 'x';
    int position = -1;
    while (true){
        clrscr();
        print(table);
        printf("%s%c"EXIT" chooses: ", player == 'x' ? LIGHT_RED: GREEN, player); position = readint("");
        if (!valid(table, position)){
            continue;
        }

        setsqr(table, player, position);
        if (wins(table, player)){
            printf(BOLD"player ""%s%c"EXIT""BOLD" wins.\n"EXIT, player == 'x' ? LIGHT_RED : GREEN, player); break;
        }

        if (tie(table)){
            clrscr(); printf(BOLD""GRAY"tie.\n"EXIT); break;
        }
        player = player == 'x' ? 'o': 'x';
    }
}
