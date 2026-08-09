#pragma once

#include <jsi/jsi.h>
#include <string_view>

namespace uws_react_native {

/// JS console functions for a simple message.
/// Not compatible with the specifiers like %s, %d, etc.
/// For an error, prefer to throw an actual `facebook::jsi::JSError` exception.
class Console {

public:
  static void info(facebook::jsi::Runtime &rt,
                   std::string_view message) {
    Console::print(rt, "info", message);
  }

  static void log(facebook::jsi::Runtime &rt,
                  std::string_view message) {
    Console::print(rt, "log", message);
  }

  static void warn(facebook::jsi::Runtime &rt,
                   std::string_view message) {
    Console::print(rt, "warn", message);
  }

private:
  static constexpr std::string_view messagePrefix = "[uws-react-native] ";

  /// This is just simple logger function
  /// Not compatible with the specifiers like %s, %d, etc
  static void print(facebook::jsi::Runtime &rt,
                    const std::string_view &&type,
                    const std::string_view message) {
    auto console = rt.global().getProperty(rt, "console");
    if(!console.isObject()) {
      return;
    }

    /// could be "warn" or "log" or "error"
    auto logger = console.asObject(rt).getProperty(rt, type.data());
    if(!logger.isObject()) {
      return;
    }

    auto fn = logger.asObject(rt);
    if(!fn.isFunction(rt)) {
      return;
    }

    std::string output;
    output.reserve(messagePrefix.size() + message.size());
    output.append(messagePrefix);
    output.append(message);

    fn.asFunction(rt).call(rt, output);
  }

};

} // namespace uws_react_native
