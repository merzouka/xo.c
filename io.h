
#ifndef IO
#define IO
typedef struct chr {
    char c;
    struct chr *next;
} Char;

/* read integer from stdin using prompt as user prompt, if no input is present
 * returns 0
 *
 * @param prompt text to prompt user with
 * @return int read integer
 * */
int readint(const char *prompt);
#endif // !IO
