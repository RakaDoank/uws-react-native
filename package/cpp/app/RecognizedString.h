#pragma once

#include <functional>
#include <jsi/jsi.h>
#include <string_view>
#include <type_traits>
#include <utility>

namespace uws_react_native {

/// Inspired from the uWebSockets.js NativeString
/// but, we don't do the arena allocator magic here.
/// TBH, I have no knowledge about it.
class RecognizedString {

private:
  char *data;
  size_t length;

  bool valid = false;

#ifdef REACT_NATIVE_DEBUG
  void check(facebook::jsi::Runtime &rt) const {
    if(!this->valid) {
      throw facebook::jsi::JSError(rt, "The value is not known by RecognizedString which only recognizes string and ArrayBuffer");
    }
  }
#endif

public:
  RecognizedString(facebook::jsi::Runtime &rt,
                   const facebook::jsi::Value &value) {
    if(value.isString()) {
      std::function<void (bool ascii, const void *pData, size_t num)> handler = [this](bool ascii, const void *pData, size_t num) {
        if(ascii) {
          this->data = (char *)pData;
          this->length = num;
          this->valid = true;
        }
      };
      value.asString(rt).getStringData(rt, handler);
    } else if(value.isObject()) {
      auto obj = value.asObject(rt);
      if(obj.isArrayBuffer(rt)) {
        auto arrayBuffer = obj.getArrayBuffer(rt);
        this->data = reinterpret_cast<char *>(arrayBuffer.data(rt));
        this->length = arrayBuffer.size(rt);
        this->valid = true;
      }
    }

#ifdef REACT_NATIVE_DEBUG
    this->check(rt);
#endif
  }

  // Check if the Value is recognized as string
  [[nodiscard]] bool isValid() const {
    return this->valid;
  }

  std::string_view getStringView() {
    return {this->data, this->length};
  }

  std::string getString() {
    return {this->data, this->length};
  }

  static bool isValid(facebook::jsi::Runtime &rt,
                      const facebook::jsi::Value &value) {
    return value.isString() || (value.isObject() && value.asObject(rt).isArrayBuffer(rt));
  }

};

}
