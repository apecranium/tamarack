#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tamarack.h"
#include "interpreter.h"

static char *get_line(void)
{
    char buf[TAMARACK_MAXLINE];
    printf(TAMARACK_PROMPT);
    fflush(stdout);
    if (fgets(buf, TAMARACK_MAXLINE, stdin) == NULL)
    {
        return NULL;
    }
    size_t len = strlen(buf);
    while (len && (buf[len-1] == '\n' || buf[len-1] == '\r'))
    {
        len--;
        buf[len] = '\0';
    }
    return strdup(buf);
}

static void do_file(const char *path)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "tamarack: can't open %s: %s\n", path, strerror(errno));
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    char *buf = malloc(sizeof(char) * size + 1);
    size_t bytes_read = fread(buf, sizeof(char), size, file);
    buf[bytes_read] = '\0';
    fclose(file);
    interpret(buf);
}

static void do_repl(void)
{
    char *line;
    while ((line = get_line()) != NULL)
    {
        if (strlen(line) > 0)
        {
            interpret(line);
        }
        free(line);
    }
}

int main(int argc, char *argv[])
{
    printf("tamarack 0.1.0-alpha\n");
    switch (argc)
    {
        case 2:
            do_file(argv[1]);
            break;
        case 1:
            do_repl();
            break;
        default:
            fprintf(stderr, "tamarack: too many arguments\n");
            exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
