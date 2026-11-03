#ifndef TC_SUPPORT_STRINGREF_H
#define TC_SUPPORT_STRINGREF_H

#include <cstddef>
#include <cstring>
#include <string>

namespace tc {
class StringRef {
public:
  using iterator = const char *;

  /// Construct an empty string ref.
  /*implicit*/ StringRef() = default;

  /// Disable conversion from nullptr.  This prevents things like
  /// if (S == nullptr)
  StringRef(std::nullptr_t) = delete;

  /// Construct a string ref from a cstring.
  /*implicit*/ constexpr StringRef(const char *Str)
      : StringRef(Str, getStringLength(Str)) {}

  /// Construct a string ref from a pointer and length.
  /*implicit*/ constexpr StringRef(const char *data, size_t length)
      : _data(data), length(length) {}

  /// Construct a string ref from an std::string.
  /*implicit*/ StringRef(const std::string &Str)
      : _data(Str.data()), length(Str.length()) {}

  /// @name StringRef Case-insensitive Comparison Operator
  /// sets the 6th bit which is lowercase for ASCII chars
  bool equals_insensitive(StringRef other) const {
    if (length != other.length)
      return false;

    for (size_t i = 0; i < other.length; ++i) {
      char c1 = _data[i] | 0x20;
      char c2 = other._data[i] | 0x20;

      if (c1 != c2)
        return false;
    }
    return true;
  }

  iterator begin() const { return data(); }
  iterator end() const { return data() + size(); }

  constexpr const char *data() const { return _data; }
  constexpr size_t size() const { return length; }
  constexpr bool empty() const { return length == 0; }

private:
  static constexpr size_t getStringLength(const char *str) {
    if (!str)
      return 0;
    size_t len = 0;
    while (str[len] != '\0') {
      ++len;
    }
    return len;
  }

  const char *_data = nullptr;
  size_t length = 0;
};

/// @name StringRef Comparison Operators
/// @{

inline bool operator==(StringRef LHS, StringRef RHS) {
  if (LHS.size() != RHS.size())
    return false;
  if (LHS.empty())
    return true;
  return std::memcmp(LHS.data(), RHS.data(), LHS.size()) == 0;
}

/// @}
} // namespace tc

#endif