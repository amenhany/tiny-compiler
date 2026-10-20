#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "scanner.hpp"

namespace tcmp
{

    const std::unordered_map<std::string, TokenType> RESERVED_WORDS = {
        {"if", TokenType::IF},
        {"then", TokenType::THEN},
        {"else", TokenType::ELSE},
        {"end", TokenType::END},
        {"repeat", TokenType::REPEAT},
        {"until", TokenType::UNTIL},
        {"read", TokenType::READ},
        {"write", TokenType::WRITE},
    };

    const std::unordered_map<std::string, TokenType> SYMBOLIC_TOKENS = {
        {":=", TokenType::ASSIGN},
        {"=", TokenType::EQUAL},
        {"<", TokenType::LESS_THAN},
        {"+", TokenType::PLUS},
        {"-", TokenType::MINUS},
        {"*", TokenType::TIMES},
        {"/", TokenType::DIVIDE},
        {"^", TokenType::POWER},
        {";", TokenType::SEMI_COLON},
        {"(", TokenType::LEFT_PAREN},
        {")", TokenType::RIGHT_PAREN},
        {"{", TokenType::LEFT_BRACE},
        {"}", TokenType::RIGHT_BRACE},
    };

    Scanner::Scanner(const std::string &fname) : m_fname(fname) {}

    std::vector<Token> Scanner::scan()
    {
        std::ifstream file(m_fname);

        if (!file.is_open())
        {
            std::cerr << "Error opening file!" << std::endl;
        }

        std::string line;
        int line_number = 0;
        std::vector<Token> res;

        while (std::getline(file, line))
        {
            line_number++;

            std::string token;

            for (int i = 0; i < line.length(); i++)
            {
                token += line[i];
                if (RESERVED_WORDS.find(token) != RESERVED_WORDS.end())
                {
                }
            }
        }

        file.close();
        return res;
    }
}
