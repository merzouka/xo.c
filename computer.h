#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#ifndef COMPUTER
#define COMPUTER
typedef struct posaligns {
    int pos;
    int aligns;
    struct posaligns *next;
} PositionAlignments;

/* returns a new list node containing pos, and next set to NULL
 *
 * @param pos node->pos
 * @param aligns node->aligns
 * @return (Position*) created node
 * */
PositionAlignments *create(int pos, int aligns);

/* return null if list is empty, else appends node with position as its value to list end 
 *
 * @param head list head
 * @param pos node->pos
 * @param aligns node->aligns
 * @return (Position*) appended node
 * */
PositionAlignments *append(PositionAlignments *head, int pos, int aligns);

/* checks if list contains position
 *
 * @param haystack list to check in
 * @param needle value to check for
 * @return bool contains position?
 * */
bool containsPos(PositionAlignments *haystack, int needle);

/* returns the first position that when filled would complete a line for player
 *
 * @param table playing table
 * @param player x/o
 * @return int found position
 * */
int complete(char table[3][3], char player);

/* prints list 
 * * format: (position, alignments)
 *
 * @param head list head
 * @return void
 * */
void printList(PositionAlignments *head);

/* frees list
 ** Note: head is not set to null
 *
 * @param head list head
 * @return void
 * */
void freeList(PositionAlignments *head);

/* returns a list containing unique positions sorted in ascending order, the positions are provided
 * by the arguments
 *
 * @param num number of arguments
 * @param ... position lists
 * @return (Position*) merged list
 * */
PositionAlignments *merge(size_t num, ...);

/* checks if current move is first move by either x or o
 *
 * @param table to check
 * @return bool is first move?
 * */
bool firstMove(char table[3][3]);

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
 * * Note: in the case of '5' 1 is returned
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
bool colFinish(char table[3][3], int col, char player);

/* checks if a row is filled by player
 *
 * @param table playing table
 * @param row row to check
 * @param player x/o
 * @return bool is filled?
 * */
bool rowFinish(char table[3][3], int row, char player);

/* checks if a diagonal is filled by player
 *
 * @param table playing table
 * @param diagonal diagonal to check
 * @param player x/o
 * @return bool is filled?
 * */
bool diagFinish(char table[3][3], int diagonal, char player);

/* checks if position is part of any line filled by player
 *
 * @param table playing table
 * @param position position to check
 * @param player x/o
 * @return bool has passing line?
 * */
bool hasFilled(char table[3][3], int position, char player);

/* returns the number of alignments with position for player
 * * a position is in alignment with another if you can draw a line between them, 
 * without being cut off by the other player, i.e only empty cells are allowed in the line 
 * connecting them
 *
 * @param table playing table
 * @param position to check
 * @param player x/o
 * */
int alignments(char table[3][3], int position, char player);

/* returns a list of empty table positions and the number of alignments of each one for player
 *
 * @param table playing table
 * @param player x/o
 * @return (PositionAlignments *) list
 * */
PositionAlignments *allAlignments(char table[3][3], char player);

/* returns the first node with node->aligns == 2
 *
 * @param head list to look in
 * @return (PositionAlignments *) node
 * */
PositionAlignments *getDoubleAlignment(PositionAlignments *head);

/* fills arr with positions from list
 *
 * @param head list head
 * @param arr array to fill
 * @return void
 * */
void getListPositions(PositionAlignments *head, int arr[]);

/* returns a sub list of positions which have aligns == maximum alignments
 *
 * @param head main list
 * @return (PositionAlignments *) sub list
 * */
PositionAlignments *maxoccurs(PositionAlignments *head);

/* checks if position block other player's line
 *
 * @param table playing table
 * @param pos to check 
 * @param player x/o
 * @return bool blocks?
 * */
bool block(char table[3][3], int pos, char player);

/* returns index of arr cell with maximum value
 *
 * @param arr array
 * @param len array length
 * @return int found index 
 * */
int arrmaxind(int arr[], size_t len);

/* returns index of arr cell with minimum value
 *
 * @param arr array
 * @param len array length
 * @return int found index 
 * */
int arrminind(int arr[], size_t len);

/* next position to be chosen for player
 *
 * @param table playing table
 * @param player x/o
 * @return int next position
 * */
int next(char table[3][3], char player);

/* starts PvE game
 *
 * @param table playing table
 * @return void
 * */
void startPvE(char table[3][3]);
#endif // !COMPUTER
