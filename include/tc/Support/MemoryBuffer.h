#ifndef TC_SUPPORT_MEMORYBUFFER_H
#define TC_SUPPORT_MEMORYBUFFER_H

#include "StringRef.h"

namespace tc {
class MemoryBuffer {
  const char *BufferStart;
  const char *BufferEnd;
  const char *Filepath;

public:
  MemoryBuffer() = default;
  ~MemoryBuffer();

  MemoryBuffer(const MemoryBuffer &) = delete;
  MemoryBuffer &operator=(const MemoryBuffer &) = delete;
  MemoryBuffer(MemoryBuffer &&) = delete;
  MemoryBuffer &operator=(MemoryBuffer &&) = delete;

  const char *getBufferStart() const { return BufferStart; }
  const char *getBufferEnd() const { return BufferEnd; }
  size_t getBufferSize() const { return BufferEnd - BufferStart; }

  StringRef getBuffer() const {
    return StringRef(BufferStart, getBufferSize());
  }
  const char *getBufferIdentifier() const { return Filepath; }

  bool loadFile(const char *filepath);
};
} // namespace tc

#endif