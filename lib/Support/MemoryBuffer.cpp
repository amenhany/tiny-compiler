#include "tc/Support/MemoryBuffer.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace tc {
MemoryBuffer::~MemoryBuffer() {
  if (BufferStart) {
#ifdef _WIN32
    UnmapViewOfFile(static_cast<LPCVOID>(BufferStart));
#else
    size_t size = BufferEnd - BufferStart;
    if (size > 0) {
      munmap(const_cast<char *>(BufferStart), size);
    }
#endif
  }
}

bool MemoryBuffer::loadFile(const char *filepath) {
  Filepath = filepath;
#ifdef _WIN32
  HANDLE hFile;
  HANDLE hMap;
  LPVOID lpBasePtr;
  LARGE_INTEGER liFileSize;

  hFile = CreateFileA(filepath,
                      GENERIC_READ,          // dwDesiredAccess
                      0,                     // dwShareMode
                      NULL,                  // lpSecurityAttributes
                      OPEN_EXISTING,         // dwCreationDisposition
                      FILE_ATTRIBUTE_NORMAL, // dwFlagsAndAttributes
                      0);                    // hTemplateFile
  if (hFile == INVALID_HANDLE_VALUE) {
    std::cerr << "CreateFile failed with error" << GetLastError() << '\n';
    return false;
  }

  if (!GetFileSizeEx(hFile, &liFileSize)) {
    std::cerr << "GetFileSize failed with error" << GetLastError() << '\n';
    CloseHandle(hFile);
    return false;
  }

  if (liFileSize.QuadPart == 0) {
    std::cerr << "File is empty\n";
    CloseHandle(hFile);
    return false;
  }

  hMap = CreateFileMapping(hFile,
                           NULL,          // Mapping attributes
                           PAGE_READONLY, // Protection flags
                           0,             // MaximumSizeHigh
                           0,             // MaximumSizeLow
                           NULL);         // Name
  if (hMap == 0) {
    std::cerr << "CreateFileMapping failed with error" << GetLastError()
              << '\n';
    CloseHandle(hFile);
    return false;
  }

  lpBasePtr = MapViewOfFile(hMap,
                            FILE_MAP_READ, // dwDesiredAccess
                            0,             // dwFileOffsetHigh
                            0,             // dwFileOffsetLow
                            0);            // dwNumberOfBytesToMap

  CloseHandle(hMap);
  CloseHandle(hFile);

  if (lpBasePtr == NULL) {
    std::cerr << "MapViewOfFile failed with error" << GetLastError() << '\n';
    return false;
  }

  BufferStart = static_cast<const char *>(lpBasePtr);
  BufferEnd = BufferStart + liFileSize.QuadPart;

  return true;
#else
  int fd = open(filepath, O_RDONLY);
  if (fd == -1) {
    std::cerr << "Error: Failed to open file: " << filepath << '\n';
    return false;
  }

  struct stat filestat;
  if (fstat(fd, &filestat) == -1) {
    std::cerr << "Error: Failed to stat file.\n";
    close(fd);
    return false;
  }

  size_t size = filestat.st_size;

  void *ptr = mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0);

  close(fd);

  if (ptr == MAP_FAILED) {
    std::cerr << "Error: mmap failed.\n";
    return false;
  }

  BufferStart = static_cast<const char *>(ptr);
  BufferEnd = BufferStart + size;

  return true;
#endif
}
} // namespace tc
