#ifndef TC_SUPPORT_SOURCEMGR_H
#define TC_SUPPORT_SOURCEMGR_H

#include "MemoryBuffer.h"

namespace tc {
class SourceMgr {
private:
  MemoryBuffer buffer;

public:
  bool loadFile(const char *path) { return buffer.loadFile(path); }
  StringRef getBuffer() const { return buffer.getBuffer(); }

  // Translates raw character pointer to Line/Column
  std::pair<size_t, size_t> getLineAndCol(const char *ptr) const;
  void printMessage(const char *loc, const char *severity, const char *message);
};
} // namespace tc

#endif