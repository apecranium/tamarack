#include <stdbool.h>
#include <stdio.h>
#include "interpreter.h"
#include "lexer.h"

void interpret(const char *src)
{
    Lexer lexer = { src, src, 1 };
    int line = -1;
    while (true)
    {
        Token token = lexer_scan(&lexer);
        if (token.line != line)
        {
            printf("%4d ", token.line);
            line = token.line;
        }
        else
        {
            printf("   | ");
        }
        printf("%2d '%.*s'\n", token.type, token.len, token.start);
        if (token.type == TOKEN_EOF) break;
    }
}
