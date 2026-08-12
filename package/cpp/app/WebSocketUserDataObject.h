#pragma once

#include <jsi/jsi.h>
#include <memory>
#include "WebSocketUserDataNativeState.h"

namespace uws_react_native {

class WebSocketUserDataObject : public facebook::jsi::Object {

public:
  WebSocketUserDataObject(facebook::jsi::Runtime &rt,
                          const std::shared_ptr<WebSocketUserDataNativeState> &&_nativeState) : facebook::jsi::Object(rt) {

    this->setNativeState(rt, _nativeState);

    this->setProperty(rt,
                      "getBoolean",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getBoolean"),
                                                                      1,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto storage = thisValue.asObject(rt_1).getNativeState<WebSocketUserDataNativeState>(rt_1)->storage;

      if(storage->booleans == nullptr || !arguments || !arguments[0].isString()) {
        return facebook::jsi::Value::undefined();
      }

      auto key = arguments[0].asString(rt_1).utf8(rt_1);
      auto it = storage->booleans->find(key);

      if(it == storage->booleans->end()) {
        return facebook::jsi::Value::undefined();
      }

      return {rt_1, it->second};
    }));

    this->setProperty(rt,
                      "setBoolean",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "setBoolean"),
                                                                      2,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto storage = thisValue.asObject(rt_1).getNativeState<WebSocketUserDataNativeState>(rt_1)->storage;

      if(!arguments || !arguments[0].isString() || !arguments[1].isBool()) {
        return facebook::jsi::Value::undefined();
      }

      storage->setBoolean(arguments[0].asString(rt_1).utf8(rt_1),
                          arguments[1].asBool());

      return facebook::jsi::Value::undefined();
    }));

    this->setProperty(rt,
                      "getNumber",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getNumber"),
                                                                      1,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto storage = thisValue.asObject(rt_1).getNativeState<WebSocketUserDataNativeState>(rt_1)->storage;

      if(storage->numbers == nullptr || !arguments || !arguments[0].isString()) {
        return facebook::jsi::Value::undefined();
      }

      auto key = arguments[0].asString(rt_1).utf8(rt_1);
      auto it = storage->numbers->find(key);

      if(it == storage->numbers->end()) {
        return facebook::jsi::Value::undefined();
      }

      return {rt_1, it->second};
    }));

    this->setProperty(rt,
                      "setNumber",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "setNumber"),
                                                                      2,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      if(!arguments || !arguments[0].isString() || !arguments[1].isNumber()) {
        return facebook::jsi::Value::undefined();
      }

      auto storage = thisValue.asObject(rt_1).getNativeState<WebSocketUserDataNativeState>(rt_1)->storage;
      storage->setNumber(arguments[0].asString(rt_1).utf8(rt_1),
                         arguments[1].asNumber());

      return facebook::jsi::Value::undefined();
    }));

    this->setProperty(rt,
                      "getString",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getString"),
                                                                      1,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto storage = thisValue.asObject(rt_1).getNativeState<WebSocketUserDataNativeState>(rt_1)->storage;

      if(storage->strings == nullptr || !arguments || !arguments[0].isString()) {
        return facebook::jsi::Value::undefined();
      }

      auto key = arguments[0].asString(rt_1).utf8(rt_1);
      auto it = storage->strings->find(key);

      if(it == storage->strings->end()) {
        return facebook::jsi::Value::undefined();
      }

      return facebook::jsi::String::createFromUtf8(rt_1, it->second);
    }));

    this->setProperty(rt,
                      "setString",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "setString"),
                                                                      2,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      if(!arguments || !arguments[0].isString() || !arguments[1].isString()) {
        return facebook::jsi::Value::undefined();
      }

      auto storage = thisValue.asObject(rt_1).getNativeState<WebSocketUserDataNativeState>(rt_1)->storage;
      storage->setString(arguments[0].asString(rt_1).utf8(rt_1),
                         arguments[1].asString(rt_1).utf8(rt_1));

      return facebook::jsi::Value::undefined();
    }));

  } // WebSocketUserDataObject

}; // class WebSocketUserDataObject

} // namespace uws_react_native
