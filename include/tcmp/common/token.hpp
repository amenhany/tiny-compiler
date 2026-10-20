#pragma once

#include <string>

namespace tcmp
{
    enum class TokenType
    {
        // Keywords
        IF,
        THEN,
        ELSE,
        END,
        REPEAT,
        UNTIL,
        READ,
        WRITE,
        // Symbols
        ASSIGN,
        EQUAL,
        LESS_THAN,
        PLUS,
        MINUS,
        TIMES,
        DIVIDE,
        POWER,
        SEMI_COLON,
        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        // Literals & Specials
        ID,
        NUM,
        ENDFILE,
        ERROR
    };

    struct Token
    {
        TokenType type;
        std::string lexeme;
        int lineNumber;
    };
}
