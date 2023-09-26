#include <string.h>
#include <stdarg.h>

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

/* returns a list of positions that when filled would complete a line for player
 *
 * @param table playing table
 * @param player x/o
 * @return (Position*) list of positions
 * */
Position *complete(char table[3][3], char player);

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
#endif // !COMPUTER
