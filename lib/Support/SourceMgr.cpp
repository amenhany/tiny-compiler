#include "tc/Support/SourceMgr.h"
#include <iostream>
#include <utility>

namespace tc {
// Hands out a non-owning StringRef view to the Lexer/Parser
std::pair<size_t, size_t> SourceMgr::getLineAndCol(const char *ptr) const {
  size_t line = 1, col = 1;
  const char *bufStart = buffer.getBufferStart();

  for (const char *p = bufStart; p < ptr; ++p) {
    if (*p == '\n') {
      line++;
      col = 1;
    } else {
      col++;
    }
  }
  return {line, col};
}

void SourceMgr::printMessage(const char *loc, const char *severity,
                             const char *message) {
  auto [line, col] = getLineAndCol(loc);
  const char *filepath = buffer.getBufferIdentifier();
  std::cerr << filepath << ":" << line << ":" << col << ": " << severity << ": "
            << message << "\n";
}
} // namespace tc