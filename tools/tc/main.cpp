#include "tc/Lexer/Lexer.h"
#include "tc/Support/SourceMgr.h"
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: tiny-scanner <input-file>\n";
    return 1;
  }

  tc::SourceMgr srcMgr;
  if (!srcMgr.loadFile(argv[1])) {
    std::cerr << "Error: Could not open source file: " << argv[1] << "\n";
    return 1;
  }

  tc::Lexer lexer(srcMgr);
  tc::Token token = lexer.getToken();

  std::vector<tc::Token> result;

  while (token.type != tc::Token::ENDFILE) {
    result.push_back(token);
    token = lexer.getToken();
  }

  if (argc < 4 || strcmp(argv[2], "-o") != 0)
    return 0;

  std::ofstream outputFile(argv[3]);

  if (!outputFile.is_open()) {
    std::cerr << "Error: Could not open the file!" << std::endl;
    return 1;
  }

  for (const auto &t : result) {
    outputFile << std::string_view(t.spelling.data(), t.spelling.size()) << ", "
               << tc::Token::getTokenName(t.type) << '\n';
  }

  outputFile.close();
  std::cout << "Successful output at " << argv[3] << '\n';

  return 0;
}