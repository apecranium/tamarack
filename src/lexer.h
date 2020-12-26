#ifndef __LEXER_H
#define __LEXER_H

typedef struct Lexer
{
    const char *start;
    const char *current;
    int line;
} Lexer;

typedef enum TokenType
{
    TOKEN_SYMBOL,
    TOKEN_ERR,
    TOKEN_EOF
} TokenType;

typedef struct Token
{
    TokenType type;
    const char *start;
    int len;
    int line;
} Token;

Token lexer_scan(Lexer *lexer);

#endif
