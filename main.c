#include "core.h"
#include "computer.h"
#include "common.h"
#include "io.h"

#include <stdio.h>

int main(void) {
    char table[3][3];
    int mode;
    do {
        printf("choose mode %sP%sv%sP%s[1]/%sP%sv%sE%s[2]: ",
                BOLD""GREEN, EXIT, BOLD""GREEN, EXIT, BOLD""GREEN, EXIT, BOLD""LIGHT_RED, EXIT);
        mode = readint("");
    } while (mode != 1 && mode != 2);
    if (mode == 1){
        startPvP(table);
    } else {
        startPvE(table);
    }

    return 0;
}
