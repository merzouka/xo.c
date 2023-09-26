#include <string.h>
#include <stdbool.h>
#include "helpers.h"

bool contains(size_t len, int haystack[], int needle){
    for (size_t i = 0; i < len; i++){
        if (haystack[i] == needle){
            return true;
        }
    }
    return false;
}
