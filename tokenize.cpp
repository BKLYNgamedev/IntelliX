#include "tokenize.h"
#include <regex>
#include <iostream>
#include <stdexcept>
#include "error_messages.h"

std::vector<Token> tokenize(const std::string &input)
{
    std::vector<Token> tokens;
    std::regex int_pattern(R"(\bint\b)");
    std::regex float_pattern(R"(\bfloat\b)");
    std::regex string_pattern(R"(\bstring\b)");
    std::regex identifier_pattern(R"([a-zA-Z_]\w*)");
    std::regex assign_pattern(R"(=)");
    std::regex number_pattern(R"(-?\d+(\.\d+)?)");
    std::regex string_literal_pattern(R"(([""][^"]*["]|[']?[^']+\'?))");
    std::regex semicolon_pattern(R"(;)");
    std::regex left_paren_pattern(R"(\()");
    std::regex right_paren_pattern(R"(\))");
    std::regex print_pattern(R"(\bprint\b)");
    std::regex bool_pattern(R"(\bbool\b)");
    std::regex boolean_pattern(R"(true|false)");
    std::regex math_operation_pattern(R"(\+|-|\*|/)");

    size_t pos = 0;
    while (pos < input.size())
    {

        if (isspace(input[pos]))
        {
            pos++;
            continue;
        }

        std::smatch match;
        std::string_view input_view(input.c_str() + pos, input.size() - pos);

        if (std::regex_search(input.begin() + pos, input.end(), match, print_pattern) && match.position() == 0)
        {
            tokens.push_back({TokenType::PRINT_KEYWORD, "print"});
            pos += match.length();
            continue;
        }

        if (std::regex_search(input.begin() + pos, input.end(), match, int_pattern) && match.position() == 0)
        {
            // Check if the next token is an identifier without parentheses
            if (pos + match.length() < input.size() && input[pos + match.length()] == ' ')
            {
                tokens.push_back({TokenType::INT_KEYWORD, "int"});
                pos += match.length();
                continue;
            }
            else if (pos + match.length() < input.size() && input[pos + match.length()] == ')')
            {
                tokens.push_back({TokenType::INT_CAST, "int"});
                pos += match.length();
                continue;
            }
        }

        if (std::regex_search(input.begin() + pos, input.end(), match, float_pattern) && match.position() == 0)
        {
            // Check if the next token is an identifier without parentheses
            if (pos + match.length() < input.size() && input[pos + match.length()] == ' ')
            {
                tokens.push_back({TokenType::FLOAT_KEYWORD, "float"});
                pos += match.length();
                continue;
            }
            else if (pos + match.length() < input.size() && input[pos + match.length()] == ')')
            {
                tokens.push_back({TokenType::FLOAT_CAST, "float"});
                pos += match.length();
                continue;
            }
        }

        if (std::regex_search(input.begin() + pos, input.end(), match, left_paren_pattern) && match.position() == 0)
        {
            tokens.push_back({TokenType::LEFT_PAREN, "("});
            pos += match.length();
            continue;
        }

        if (std::regex_search(input.begin() + pos, input.end(), match, right_paren_pattern) && match.position() == 0)
        {
            tokens.push_back({TokenType::RIGHT_PAREN, ")"});
            pos += match.length();
            continue;
        }



        if (std::regex_search(input.begin() + pos, input.end(), match, math_operation_pattern) && match.position() == 0)
        {
            tokens.push_back({static_cast<TokenType>(match.str()[0]), match.str()});
            pos += match.length();
            continue;
        }

        if (std::regex_search(input.begin() + pos, input.end(), match, string_pattern) && match.position() == 0)
        {

            // Check if the next token is an identifier without parentheses
            if (pos + match.length() < input.size() && input[pos + match.length()] == ' ')
            {
                tokens.push_back({TokenType::STRING_KEYWORD, "string"});
                pos += match.length();
                continue;
            }
            else if (pos + match.length() < input.size() && input[pos + match.length()] == ')')
            {
                tokens.push_back({TokenType::STRING_CAST, "string"});
                pos += match.length();
                continue;
            }
        }

        if (std::regex_search(input.begin() + pos, input.end(), match, bool_pattern) && match.position() == 0)
        {
            tokens.push_back({TokenType::BOOL_KEYWORD, "bool"});
            pos += match.length();
            continue;
        }

        if (std::regex_search(input.begin() + pos, input.end(), match, boolean_pattern) && match.position() == 0)
        {
            tokens.push_back({TokenType::BOOLEAN, match.str()});
            pos += match.length();
            continue;
        }

        if (std::regex_search(input.begin() + pos, input.end(), match, identifier_pattern) && match.position() == 0)
        {
            tokens.push_back({TokenType::IDENTIFIER, match.str()});
            pos += match.length();
            continue;
        }

        if (std::regex_search(input.begin() + pos, input.end(), match, assign_pattern) && match.position() == 0)
        {
            tokens.push_back({TokenType::ASSIGN, "="});
            pos += match.length();
            continue;
        }

        if (std::regex_search(input.begin() + pos, input.end(), match, number_pattern) && match.position() == 0)
        {
            tokens.push_back({TokenType::NUMBER, match.str()});
            pos += match.length();
            continue;
        }

        if (std::regex_search(input.begin() + pos, input.end(), match, semicolon_pattern) && match.position() == 0)
        {
            tokens.push_back({TokenType::SEMICOLON, ";"});
            pos += match.length();
            continue;
        }

        if (std::regex_search(input.begin() + pos, input.end(), match, string_literal_pattern) && match.position() == 0)
        {
            std::string literal = match.str();
            if (literal.front() == '\'' || literal.front() == '\"')
            {
                literal = literal.substr(1, literal.size() - 2);
            }
            tokens.push_back({TokenType::STRING, literal});
            pos += literal.size() + 2;
            continue;
        }

        throw std::runtime_error("Unexpected character: " + std::string(1, input[pos]));
    }

    if (!tokens.empty() && tokens.back().type == TokenType::SEMICOLON)
    {
        tokens.push_back({TokenType::END_OF_FILE, ""});
    }
    else
    {
        throw std::runtime_error("Unexpected end of file");
    }

    for (Token t : tokens)
    {
        std::cout << "{" << token_to_string(t.type) << "," << t.value << "}" << std::endl;
    }

    return tokens;
}

std::string token_to_string(TokenType type)
{
    switch (type)
    {
    case TokenType::INT_KEYWORD:
        return "INT_KEYWORD";
    case TokenType::INT_CAST:
        return "INT_CAST";
    case TokenType::FLOAT_KEYWORD:
        return "FLOAT_KEYWORD";
    case TokenType::FLOAT_CAST:
        return "FLOAT_CAST";
    case TokenType::STRING_KEYWORD:
        return "STRING_KEYWORD";
    case TokenType::STRING_CAST:
        return "STRING_CAST";
    case TokenType::IDENTIFIER:
        return "IDENTIFIER";
    case TokenType::ASSIGN:
        return "ASSIGN";
    case TokenType::NUMBER:
        return "NUMBER";
    case TokenType::STRING:
        return "STRING";
    case TokenType::SEMICOLON:
        return "SEMICOLON";
    case TokenType::LEFT_PAREN:
        return "LEFT_PAREN";
    case TokenType::RIGHT_PAREN:
        return "RIGHT_PAREN";
    case TokenType::LEFT_QUOTE:
        return "LEFT_QUOTE";
    case TokenType::RIGHT_QUOTE:
        return "RIGHT_QUOTE";
    case TokenType::PRINT_KEYWORD:
        return "PRINT_KEYWORD";
    case TokenType::BOOL_KEYWORD:
        return "BOOL_KEYWORD";
    case TokenType::BOOLEAN:
        return "BOOLEAN";
    case TokenType::END_OF_FILE:
        return "END_OF_FILE";
    // Add other cases as needed
    default:
        return "UNKNOWN";
    }
};