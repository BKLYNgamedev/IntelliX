#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

enum TokenType
{
    INT_KEYWORD,
    FLOAT_KEYWORD,
    STRING_KEYWORD,
    IDENTIFIER,
    ASSIGN,
    NUMBER,
    STRING,
    SEMICOLON,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_QUOTE,
    RIGHT_QUOTE,
    PRINT_KEYWORD,
    BOOL_KEYWORD,
    BOOLEAN,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    END_OF_FILE
};

struct Token
{
    TokenType type;
    string value;
};

#endif // TOKEN_H