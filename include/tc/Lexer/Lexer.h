#ifndef TC_PARSER_LEXER_H
#define TC_PARSER_LEXER_H

#include "tc/Support/SourceMgr.h"
#include "tc/Support/StringRef.h"

namespace tc {
struct Token {
public:
  enum TokenType {
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
    MULT,
    DIV,
    SEMI_COLON,
    LEFT_PAREN,
    RIGHT_PAREN,
    // Literals & Specials
    ID,
    NUM,
    ENDFILE,
    ERROR
  };
  Token(TokenType type, StringRef spelling) : type(type), spelling(spelling) {}

  TokenType type;
  StringRef spelling;

  static constexpr const char *getTokenName(TokenType type) {
    switch (type) {
    case IF:
      return "IF";
    case THEN:
      return "THEN";
    case ELSE:
      return "ELSE";
    case END:
      return "END";
    case REPEAT:
      return "REPEAT";
    case UNTIL:
      return "UNTIL";
    case READ:
      return "READ";
    case WRITE:
      return "WRITE";

    case ASSIGN:
      return "ASSIGN";
    case EQUAL:
      return "EQUAL";
    case LESS_THAN:
      return "LESSTHAN";
    case PLUS:
      return "PLUS";
    case MINUS:
      return "MINUS";
    case MULT:
      return "MULT";
    case DIV:
      return "DIV";
    case SEMI_COLON:
      return "SEMICOLON";
    case LEFT_PAREN:
      return "OPENBRACKET";
    case RIGHT_PAREN:
      return "CLOSEDBRACKET";

    case ID:
      return "IDENTIFIER";
    case NUM:
      return "NUMBER";
    case ENDFILE:
      return "ENDFILE";
    case ERROR:
      return "ERROR";
    }
    return "UNKNOWN";
  }
};

class Lexer {
public:
  Lexer(SourceMgr &srcMgr);

  Token getToken();

private:
  Token formToken(Token::TokenType type, const char *start) {
    return Token(type, StringRef(start, curPtr - start));
  }

  Token emitError(const char *loc, const char *message);

  int getNextChar();

  void lexComment();
  Token lexIdentifier(const char *start);
  Token lexNumber(const char *start);

  SourceMgr &srcMgr;
  StringRef curBuffer;
  const char *curPtr;
  bool hasErrors = false;
};
} // namespace tc
#endif