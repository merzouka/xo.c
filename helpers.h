#include <string.h>
#include <stdbool.h>

#ifndef HELPERS
#define HELPERS
/* checks if haystack contains needle
 *
 * @param len array length
 * @param haystack array to look in
 * @param needle value to look for
 * @return bool contains needle?
 * */
bool contains(size_t len, int haystack[], int needle);

#endif // !HELPERS 
