#include "tc/Lexer/Lexer.h"
#include <cassert>

namespace tc {
Lexer::Lexer(SourceMgr &srcMgr) : srcMgr(srcMgr) {
  curBuffer = srcMgr.getBuffer();
  curPtr = curBuffer.begin();
}

int Lexer::getNextChar() {
  char curChar = *curPtr++;
  switch (curChar) {
  default:
    return static_cast<unsigned char>(curChar);
  case 0: {
    // A nul character in the stream is either the end of the current buffer
    // or a random nul in the file. Disambiguate that here.
    if (curPtr - 1 != curBuffer.end())
      return 0;

    // Otherwise, return end of file.
    --curPtr;
    return EOF;
  }
  case '\n':
  case '\r':
    // Handle the newline character by ignoring it and incrementing the line
    // count. However, be careful about 'dos style' files with \n\r in them.
    // Only treat a \n\r or \r\n as a single line.
    if ((*curPtr == '\n' || (*curPtr == '\r')) && *curPtr != curChar)
      ++curPtr;
    return '\n';
  }
}

Token Lexer::getToken() {
  while (true) {
    const char *tokStart = curPtr;

    int curChar = getNextChar();
    switch (curChar) {
    default:
      // Handle identifiers: [a-zA-Z]
      if (isalpha(curChar))
        return lexIdentifier(tokStart);

      // Unknown character, emit an error.
      return emitError(tokStart, "unexpected character");
    case EOF:
      // Return EOF denoting the end of lexing.
      return formToken(Token::ENDFILE, tokStart);
    case ' ':
    case '\t':
    case '\n':
    case '\r':
      continue;
    case ';':
      return formToken(Token::SEMI_COLON, tokStart);
    case ':':
      if (*curPtr == '=') {
        ++curPtr;
        return formToken(Token::ASSIGN, tokStart);
      }
      return emitError(tokStart, "unexpected character");
    case '=':
      return formToken(Token::EQUAL, tokStart);
    case '+':
      return formToken(Token::PLUS, tokStart);
    case '-':
      return formToken(Token::MINUS, tokStart);
    case '*':
      return formToken(Token::MULT, tokStart);
    case '/':
      return formToken(Token::DIV, tokStart);
    case '<':
      return formToken(Token::LESS_THAN, tokStart);
    case '(':
      return formToken(Token::LEFT_PAREN, tokStart);
    case ')':
      return formToken(Token::RIGHT_PAREN, tokStart);
    case '{':
      lexComment();
      continue;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return lexNumber(tokStart);
    }
  }
}

void Lexer::lexComment() {
  // assert(*curPtr == '{');

  while (true) {
    switch (*curPtr++) {
    case '}':
      // Closing brace is end of comment.
      return;
    case 0:
      // If this is the end of the buffer, emit error.
      if (curPtr - 1 == curBuffer.end()) {
        --curPtr;
        emitError(curPtr, "expected }");
        return;
      }
      [[fallthrough]];
    default:
      // Skip over other characters.
      break;
    }
  }
}

Token Lexer::lexIdentifier(const char *tokStart) {
  // Match the rest of the identifier regex: [a-zA-Z]*
  while (isalpha(*curPtr))
    ++curPtr;

  StringRef str(tokStart, curPtr - tokStart);
  if (str.equals_insensitive("if"))
    return Token(Token::IF, str);
  else if (str.equals_insensitive("then"))
    return Token(Token::THEN, str);
  else if (str.equals_insensitive("else"))
    return Token(Token::ELSE, str);
  else if (str.equals_insensitive("end"))
    return Token(Token::END, str);
  else if (str.equals_insensitive("repeat"))
    return Token(Token::REPEAT, str);
  else if (str.equals_insensitive("until"))
    return Token(Token::UNTIL, str);
  else if (str.equals_insensitive("read"))
    return Token(Token::READ, str);
  else if (str.equals_insensitive("write"))
    return Token(Token::WRITE, str);
  else
    return Token(Token::ID, str);
}

Token Lexer::lexNumber(const char *tokStart) {
  assert(isdigit(curPtr[-1]));

  // Handle the normal decimal case.
  while (isdigit(*curPtr))
    ++curPtr;

  return formToken(Token::NUM, tokStart);
}

Token Lexer::emitError(const char *loc, const char *message) {
  hasErrors = true;
  srcMgr.printMessage(loc, "error", message);
  return formToken(Token::ERROR, loc);
}
} // namespace tc