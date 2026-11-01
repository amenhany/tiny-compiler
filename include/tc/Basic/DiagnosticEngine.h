#ifndef TC_BASIC_DIAGNOSTICENGINE_H
#define TC_BASIC_DIAGNOSTICENGINE_H

#include "tc/Support/SourceMgr.h"

namespace tc {
class DiagnosticEngine {
private:
  SourceMgr &srcMgr;
  unsigned int errorCount = 0;
  unsigned int maxErrors = 20;

public:
  explicit DiagnosticEngine(SourceMgr &srcMgr, unsigned int limit = 20)
      : srcMgr(srcMgr), maxErrors(limit) {}

  //   void emitError(const char* loc, const )

  bool hasErrors() const { return errorCount > 0; }
  unsigned getErrorCount() const { return errorCount; }

  void setMaxErrors(unsigned limit) { maxErrors = limit; }
};
} // namespace tc

#endif