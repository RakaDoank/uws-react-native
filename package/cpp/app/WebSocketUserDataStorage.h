#pragma once

#include <memory>
#include <unordered_map>
#include <string>

namespace uws_react_native {

struct WebSocketUserDataStorage {

public:
  // Getter per key/name methods are in WebSocketUserDataObject.h

  void setBoolean(std::string &&key, bool value) {
    if(this->booleans == nullptr) {
      this->booleans = std::make_unique<std::unordered_map<std::string, bool>>();
    }
    this->booleans->insert({ key, value });
  }

  void setNumber(std::string &&key, double value) {
    if(this->numbers == nullptr) {
      this->numbers = std::make_unique<std::unordered_map<std::string, double>>();
    }
    this->numbers->insert({ key, value });
  }

  void setString(std::string &&key, std::string &&value) {
    if(this->strings == nullptr) {
      this->strings = std::make_unique<std::unordered_map<std::string, std::string>>();
    }
    this->strings->insert({ key, value });
  }

  std::unique_ptr<std::unordered_map<std::string, bool>> booleans = nullptr;
  std::unique_ptr<std::unordered_map<std::string, double>> numbers = nullptr;
  std::unique_ptr<std::unordered_map<std::string, std::string>> strings = nullptr;

}; // WebSocketUserDataObjectProvider

} // namespace uws_react_native
