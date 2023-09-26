#include "io.h"
#include <stdio.h>
#include <stdlib.h>

int readint(const char *prompt){
    printf("%s", prompt);
    Char *root = malloc(sizeof(Char)); Char *x = root;
    size_t len = 0;
    for (char c; (c = getchar()) != '\n'; x->next = malloc(sizeof(Char)), x = x->next, x->c = c, len++){}
    x->next = NULL;
    x = root->next; free(root); root = x;
    if (root == NULL){
        return 0;
    }

    char *input = malloc(len + 1);
    for (int i = 0; root != NULL; input[i++] = root->c, x = root, root = root->next, free(x)){}
    input[len] = '\0';
    int intval;
    sscanf(input, "%d", &intval);
    free(input);
    return intval;
}
