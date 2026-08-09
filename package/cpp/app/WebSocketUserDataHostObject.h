#pragma once

#include <algorithm>
#include <array>
#include <jsi/jsi.h>
#include <vector>
#include "WebSocketUserDataStorage.h"

namespace uws_react_native {

class WebSocketUserDataHostObject : public facebook::jsi::HostObject {

public:
  WebSocketUserDataHostObject(WebSocketUserDataStorage *storage) {
    this->storage = storage;
  }

  facebook::jsi::Value get(facebook::jsi::Runtime &rt,
                           const facebook::jsi::PropNameID &propName) override {
    auto name = propName.utf8(rt);

    if(name == "getBoolean") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             1,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if(this->storage->booleans == nullptr || !arguments || !arguments[0].isString()) {
          return facebook::jsi::Value::undefined();
        }

        auto key = arguments[0].asString(rt_1).utf8(rt_1);
        auto it = this->storage->booleans->find(key);

        if(it == this->storage->booleans->end()) {
          return facebook::jsi::Value::undefined();
        }

        return {rt_1, it->second};
      });
    }

    if(name == "setBoolean") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             2,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if(!arguments || !arguments[0].isString() || !arguments[1].isBool()) {
          return facebook::jsi::Value::undefined();
        }

        this->storage->setBoolean(arguments[0].asString(rt_1).utf8(rt_1),
                                  arguments[1].asBool());

        return facebook::jsi::Value::undefined();
      });
    }

    if(name == "getNumber") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             1,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if(this->storage->numbers == nullptr || !arguments || !arguments[0].isString()) {
          return facebook::jsi::Value::undefined();
        }

        auto key = arguments[0].asString(rt_1).utf8(rt_1);
        auto it = this->storage->numbers->find(key);

        if(it == storage->numbers->end()) {
          return facebook::jsi::Value::undefined();
        }

        return {rt_1, it->second};
      });
    }

    if(name == "setNumber") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             2,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if(!arguments || !arguments[0].isString() || !arguments[1].isNumber()) {
          return facebook::jsi::Value::undefined();
        }

        this->storage->setNumber(arguments[0].asString(rt_1).utf8(rt_1),
                                 arguments[1].asNumber());

        return facebook::jsi::Value::undefined();
      });
    }

    if(name == "getString") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             1,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if(this->storage->strings == nullptr || !arguments || !arguments[0].isString()) {
          return facebook::jsi::Value::undefined();
        }

        auto key = arguments[0].asString(rt_1).utf8(rt_1);
        auto it = this->storage->strings->find(key);

        if(it == this->storage->strings->end()) {
          return facebook::jsi::Value::undefined();
        }

        return facebook::jsi::String::createFromUtf8(rt_1, it->second);
      });
    }

    if(name == "setString") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             2,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if(!arguments || !arguments[0].isString() || !arguments[1].isString()) {
          return facebook::jsi::Value::undefined();
        }

        this->storage->setString(arguments[0].asString(rt_1).utf8(rt_1),
                                 arguments[1].asString(rt_1).utf8(rt_1));

        return facebook::jsi::Value::undefined();
      });
    }

    if(name == "remove") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             1,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        if((this->storage->booleans == nullptr && this->storage->numbers == nullptr && this->storage->strings == nullptr) ||
           !arguments ||
           !arguments[0].isString()) {
          return facebook::jsi::Value::undefined();
        }

        auto key = arguments[0].asString(rt_1).utf8(rt_1);

        if(this->storage->booleans != nullptr) {
          this->storage->booleans->erase(key);
        }

        if(this->storage->numbers != nullptr) {
          this->storage->numbers->erase(key);
        }

        if(this->storage->strings != nullptr) {
          this->storage->strings->erase(key);
        }

        return facebook::jsi::Value::undefined();
      });
    }

    return facebook::jsi::Value::undefined();
  }

  void set(facebook::jsi::Runtime &rt,
           const facebook::jsi::PropNameID &name,
           const facebook::jsi::Value &value) override {
    throw facebook::jsi::JSError(rt, "WebSocket object is read-only.");
  }

  std::vector<facebook::jsi::PropNameID> getPropertyNames(facebook::jsi::Runtime& rt) override {
    std::vector<facebook::jsi::PropNameID> names = {};
    names.reserve(this->propertyNames.size());

    std::for_each(propertyNames.begin(), propertyNames.end(), [&rt, &names](std::string &name) -> void {
      names.emplace_back(facebook::jsi::PropNameID::forUtf8(rt, name));
    });

    return names;
  }

private:
  WebSocketUserDataStorage *storage = nullptr;

  std::array<std::string, 7> propertyNames = {"getBoolean",
                                              "setBoolean",

                                              "getNumber",
                                              "setBoolean",

                                              "getString",
                                              "setString",

                                              "remove"};


};

} // namespace uws_react_native
