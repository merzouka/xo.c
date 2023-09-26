#include <stdbool.h>
#include <string.h>
#ifndef CORE
#define CORE
/* clears console screen
 *
 * @return void
 * */
void clrscr();

/* returns the row in table linked to position
 *
 * @param position number 1-9
 * @return int row in table
 * */
int row(int position);

/* returns the col in table linked to position
 *
 * @param position number 1-9
 * @return int col in table
 * */
int col(int position);

/* initializes the table with an empty space
 *
 * @param table the table to initialize
 * */
void init(char table[3][3]);

/* prints table to console
 *
 * @return void
 * */
void print(const char table[3][3]);

/* prints table highlighting positions
 *
 * @param table playing table
 * @param len number of positions to highlight
 * @param positions to highlight
 * @return void
 * */
void highlight(const char table[3][3], size_t len, int positions[]);

/* set square at position if not taken (according to num-pad (top right is 7)) to player
 *
 * @param table playing table
 * @param player x/o 
 * @param position chosen position
 * @return void
 * */
void setsqr(char table[3][3], char player, int position);

/* checks if position is valid, and prints message if not
 *
 * @param position the inputted position
 * @return bool position valid?
 * */
bool valid(char table[3][3], int position);

/* checks if player has filled a row
 *
 * @param table playing table
 * @param player x/o
 * @return bool has filled a row?
 * */
bool rowAlignment(char table[3][3], char player);

/* checks if player has filled a col
 *
 * @param table playing table
 * @param player x/o
 * @return bool has filled a col?
 * */
bool colAlignment(char table[3][3], char player);

/* checks if player has filled a diagonal
 *
 * @param table playing table
 * @param player x/o
 * @return bool has filled a diagonal?
 * */
bool diagonalAlignment(char table[3][3], char player);

/* checks if player wins 
 *
 * @param table playing table
 * @param player x/o
 * @return bool player wins?
 * */
bool wins(char table[3][3], char player);

/* checks for a tie
 *
 * @param table playing table
 * @return bool tie?
 * */
bool tie(char table[3][3]);

/* starts the game
 *
 * @param table playing table
 * */
void start(char table[3][3]);
#endif // !CORE