#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#ifndef COMPUTER
#define COMPUTER
typedef struct position {
    int pos;
    struct position *next;
} Position;

/* returns a new list node containing pos, and next set to NULL
 *
 * @param pos node->pos
 * @return (Position*) created node
 * */
Position *create(int pos);

/* return null if list is empty, else appends node with position as its value to list end 
 *
 * @param head list head
 * @param position value to append
 * @return (Position*) appended node
 * */
Position *append(Position *head, int position);

/* checks if list contains position
 *
 * @param haystack list to check in
 * @param needle value to check for
 * @return bool contains position?
 * */
bool containsPos(Position *haystack, int needle);

/* returns the first position that when filled would complete a line for player
 *
 * @param table playing table
 * @param player x/o
 * @return int found position
 * */
int complete(char table[3][3], char player);

/* prints list
 *
 * @param head list head
 * @return void
 * */
void printPositionList(Position *head);

/* frees list
 ** Note: head is not set to null
 *
 * @param head list head
 * @return void
 * */
void freePositionList(Position *head);

/* returns a list containing unique positions sorted in ascending order, the positions are provided
 * by the arguments
 *
 * @param num number of arguments
 * @param ... position lists
 * @return (Position*) merged list
 * */
Position *merge(size_t num, ...);

/* checks if table is empty
 *
 * @param table to check
 * @return bool is empty?
 * */
bool empty(char table[3][3]);

/* copies table to copy
 *
 * @param table to copy
 * @param copy to copy to
 * @return void
 * */
void cpy(char table[3][3], char copy[3][3]);

/* return diagonal associated with position:
 * * 1 diagonal: 7-5-3
 * * 0 diagonal: no diagonal
 * * -1 diagonal: 9-5-1
 *
 * @param position desired position
 * @return int diagonal
 * */
int diagonal(int position);

/* checks if a column is filled by player
 *
 * @param table playing table 
 * @param col column to check
 * @param player x/o
 * @return bool is filled?
 * */
bool lineAtCol(char table[3][3], int col, char player);

/* checks if a row is filled by player
 *
 * @param table playing table
 * @param row row to check
 * @param player x/o
 * @return bool is filled?
 * */
bool lineAtRow(char table[3][3], int row, char player);

/* checks if a diagonal is filled by player
 *
 * @param table playing table
 * @param diagonal diagonal to check
 * @param player x/o
 * @return bool is filled?
 * */
bool lineAtDiag(char table[3][3], int diagonal, char player);

/* checks if position is part of any line filled by player
 *
 * @param table playing table
 * @param position position to check
 * @param player x/o
 * @return bool has passing line?
 * */
bool lineAt(char table[3][3], int position, char player);

/* next position to be chosen for player
 *
 * @param table playing table
 * @param player x/o
 * @return int next position
 * */
int next(char table[3][3], char player);
#endif // !COMPUTER
