#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

static bool is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

static char advance(Lexer *lexer)
{
    lexer->current++;
    return lexer->current[-1];
}

static Token new_token(Lexer *lexer, TokenType type)
{
    Token token =
    {
        type,
        lexer->start,
        (lexer->current - lexer->start),
        lexer->line
    };
    return token;
}

static Token new_error_token(Lexer *lexer, const char *msg)
{
    Token token = { TOKEN_ERR, msg, strlen(msg), lexer->line };
    return token;
}

Token lexer_scan(Lexer *lexer)
{
    lexer->start = lexer->current;
    if (*lexer->current == '\0')
    {
        return new_token(lexer, TOKEN_EOF);
    }
    char c = advance(lexer);
    if (is_alpha(c))
    {
        return new_token(lexer, TOKEN_SYMBOL);
    }
    return new_error_token(lexer, "unexpected character");
}
