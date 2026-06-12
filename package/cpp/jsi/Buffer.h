#pragma once

#include <jsi/jsi.h>

namespace facebook::jsi {

// Probably bad name and usage.
// I have to instantiate this class every onDataV2 call to create JSI Array Buffer.
// I've tried to instantiate once, and just append the string inside with custom public append method,
// but the app was crashed. I don't know why.
class StringMutableBuffer : public MutableBuffer {

private:
  std::string *s;

public:
  StringMutableBuffer(std::string *s) {
    this->s = s;
  };

  size_t size() const override {
    return this->s->size();
  }

  uint8_t *data() override {
    return reinterpret_cast<uint8_t *>(this->s->data());
  }

}; // StringMutableBuffer

class StringViewBuffer : public Buffer {

private:
  std::string_view sv;

public:
  StringViewBuffer(std::string_view s) : sv(s) {}

  size_t size() const override {
    return this->sv.size();
  }

  const uint8_t *data() const override {
    return reinterpret_cast<const uint8_t *>(this->sv.data());
  }

}; // StringViewBuffer

} // namespace facebook::jsi
