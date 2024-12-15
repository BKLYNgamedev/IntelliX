#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <string>
#include <vector>
#pragma once

enum class TokenType
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
    INT_CAST,
    FLOAT_CAST,
    STRING_CAST,
    END_OF_FILE
};

struct Token
{
    TokenType type;
    std::string value;
};

std::string token_to_string(TokenType type);
 

std::vector<Token> tokenize(const std::string &input);

#endif // TOKENIZE_H