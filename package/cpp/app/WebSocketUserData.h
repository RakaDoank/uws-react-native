#pragma once

#include <algorithm>
#include <functional>
#include <jsi/jsi.h>
#include <vector>

namespace uws_react_native {

class WebSocketUserData : public facebook::jsi::HostObject {

public:
  WebSocketUserData &operator=(WebSocketUserData &) = delete;

  facebook::jsi::Value get(facebook::jsi::Runtime &rt,
                           const facebook::jsi::PropNameID &name) override {
    auto nameStr = name.utf8(rt);

    // getBoolean
    if(nameStr == this->propertyNames[0]) {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             facebook::jsi::PropNameID::forUtf8(rt, this->propertyNames[0]),
                                                             2,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if(this->booleans == nullptr || !arguments || !arguments[0].isString()) {
          return facebook::jsi::Value::undefined();
        }

        auto key = arguments[0].asString(rt_1).utf8(rt_1);
        return {rt_1, this->booleans->at(key)};
      });
    }

    // setBoolean
    if(nameStr == this->propertyNames[1]) {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             facebook::jsi::PropNameID::forUtf8(rt, this->propertyNames[1]),
                                                             2,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if(!arguments || !arguments[0].isString() || !arguments[1].isBool()) {
          return facebook::jsi::Value::undefined();
        }

        auto key = arguments[0].asString(rt_1).utf8(rt_1);
        auto boolean = arguments[1].asBool();

        if(this->booleans == nullptr) {
          this->booleans = std::make_unique<std::unordered_map<std::string, bool>>();
        }
        this->booleans->insert({ key, boolean });

        return facebook::jsi::Value::undefined();
      });
    }

    // getNumber
    if(nameStr == this->propertyNames[2]) {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             facebook::jsi::PropNameID::forUtf8(rt, this->propertyNames[2]),
                                                             2,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if(this->numbers == nullptr || !arguments || !arguments[0].isString()) {
          return facebook::jsi::Value::undefined();
        }

        auto key = arguments[0].asString(rt_1).utf8(rt_1);
        return {rt_1, this->numbers->at(key)};
      });
    }

    // setNumber
    if(nameStr == this->propertyNames[3]) {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             facebook::jsi::PropNameID::forUtf8(rt, this->propertyNames[3]),
                                                             2,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if(!arguments || !arguments[0].isString() || !arguments[1].isNumber()) {
          return facebook::jsi::Value::undefined();
        }

        auto key = arguments[0].asString(rt_1).utf8(rt_1);
        auto number = arguments[1].asNumber();

        if(this->numbers == nullptr) {
          this->numbers = std::make_unique<std::unordered_map<std::string, double>>();
        }
        this->numbers->insert({ key, number });

        return facebook::jsi::Value::undefined();
      });
    }

    // getString
    if(nameStr == this->propertyNames[4]) {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             facebook::jsi::PropNameID::forUtf8(rt, this->propertyNames[4]),
                                                             2,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if(this->strings == nullptr || !arguments || !arguments[0].isString()) {
          return facebook::jsi::Value::undefined();
        }

        auto key = arguments[0].asString(rt_1).utf8(rt_1);
        auto it = this->strings->find(key);

        if(it == this->strings->end()) {
          return facebook::jsi::Value::undefined();
        }

        return facebook::jsi::String::createFromAscii(rt_1, it->second);
      });
    }

    // setString
    if(nameStr == this->propertyNames[5]) {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             facebook::jsi::PropNameID::forUtf8(rt, this->propertyNames[5]),
                                                             2,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if(!arguments || !arguments[0].isString() || !arguments[1].isString()) {
          return facebook::jsi::Value::undefined();
        }

        auto key = arguments[0].asString(rt_1).utf8(rt_1);
        auto string = arguments[1].asString(rt_1).utf8(rt_1);

        if(this->strings == nullptr) {
          this->strings = std::make_unique<std::unordered_map<std::string, std::string>>();
        }
        this->strings->insert({ key, std::move(string) });

        return facebook::jsi::Value::undefined();
      });
    }

    // remove
    if(nameStr == this->propertyNames[6]) {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             facebook::jsi::PropNameID::forUtf8(rt, this->propertyNames[5]),
                                                             1,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if(this->isEmpty() || !arguments || !arguments[0].isString()) {
          return facebook::jsi::Value::undefined();
        }

        auto key = arguments[0].asString(rt_1).utf8(rt_1);

        if(this->booleans != nullptr) {
          this->booleans->erase(key);
        }

        if(this->numbers != nullptr) {
          this->numbers->erase(key);
        }

        if(this->strings != nullptr) {
          this->strings->erase(key);
        }

        return facebook::jsi::Value::undefined();
      });
    }

    return facebook::jsi::Value::undefined();
  }

  void set(facebook::jsi::Runtime &rt,
           const facebook::jsi::PropNameID &name,
           const facebook::jsi::Value &value) override {
    throw facebook::jsi::JSError(rt, "User data object is read-only.");
  }

  std::vector<facebook::jsi::PropNameID> getPropertyNames(facebook::jsi::Runtime& rt) override {
    std::vector<facebook::jsi::PropNameID> names = {};
    names.reserve(this->propertyNames.size());

    std::for_each(propertyNames.begin(), propertyNames.end(), [&rt, &names](std::string &name) -> void {
      names.emplace_back(facebook::jsi::PropNameID::forUtf8(rt, name));
    });

    return names;
  }

  [[nodiscard]] bool isEmpty() const {
    return this->booleans == nullptr && this->numbers == nullptr && this->strings == nullptr;
  }

private:
  std::unique_ptr<std::unordered_map<std::string, bool>> booleans = nullptr;
  std::unique_ptr<std::unordered_map<std::string, double>> numbers = nullptr;
  std::unique_ptr<std::unordered_map<std::string, std::string>> strings = nullptr;

  std::array<std::string, 7> propertyNames = {"getBoolean",
                                              "setBoolean",

                                              "getNumber",
                                              "setBoolean",

                                              "getString",
                                              "setString",

                                              "remove"};

};

}