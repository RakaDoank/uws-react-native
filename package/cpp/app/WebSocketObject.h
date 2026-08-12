#pragma once

#include <jsi/jsi.h>
#include <memory>
#include "WebSocketNativeState.h"
#include "WebSocketUserDataNativeState.h"
#include "WebSocketUserDataObject.h"
#include "WebSocketUserDataStorage.h"
#include "uWebSockets/WebSocket.h"

namespace uws_react_native {

class WebSocketObject : public facebook::jsi::Object {

public:
  WebSocketObject(facebook::jsi::Runtime &rt,
                  const std::shared_ptr<WebSocketNativeState> &_nativeState) : facebook::jsi::Object(rt) {

    this->setNativeState(rt, _nativeState);

    this->setProperty(rt,
                      "close",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "close"),
                                                                      0,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;
      ws->close();
      return facebook::jsi::Value::undefined();
    }));

    this->setProperty(rt,
                      "cork",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "close"),
                                                                      1,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;

      ws->cork([&rt_1, cb = arguments[0].asObject(rt_1).asFunction(rt_1)] {
        cb.call(rt_1);
      });

      return {rt_1, thisValue};
    }));

    this->setProperty(rt,
                      "end",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "end"),
                                                                      2,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {

      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;

      if(!arguments) {
        ws->end();
        return facebook::jsi::Value::undefined();
      }

      int code = 0;

      if(arguments[0].isNumber()) {
        code = static_cast<int>(arguments[0].asNumber());
      }

      auto message = RecognizedString(rt_1, arguments[1]);
      if(!message.isValid()) {
        ws->end(code, {});
        return facebook::jsi::Value::undefined();
      }

      ws->end(code, message.getStringView());
      return {rt_1, thisValue};
    }));

    this->setProperty(rt,
                      "getBufferedAmount",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getBufferedAmount"),
                                                                      0,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;
      return {rt_1, static_cast<double>(ws->getBufferedAmount())};
    }));

    this->setProperty(rt,
                      "getRemoteAddress",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getRemoteAddress"),
                                                                      0,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;
      return facebook::jsi::ArrayBuffer(rt_1,
                                          std::make_shared<uws_react_native::StringViewMutableBuffer>(ws->getRemoteAddress()));
    }));

    this->setProperty(rt,
                      "getRemoteAddressAsText",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getRemoteAddressAsText"),
                                                                      0,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;
      return facebook::jsi::String::createFromAscii(rt_1, ws->getRemoteAddressAsText().data());
    }));

    this->setProperty(rt,
                      "getRemotePort",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getRemotePort"),
                                                                      0,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;
      return {rt_1, static_cast<double>(ws->getRemotePort())};
    }));

    this->setProperty(rt,
                      "getTopics",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getTopics"),
                                                                      0,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;

      /// Using jsi Array with zero element and "push" it later
      /// is only supported in React Native >= 0.86
      auto vec = std::vector<std::string_view>();

      ws->iterateTopics([&vec](std::string_view topic) -> void {
        vec.emplace_back(topic);
      });

      auto topics = facebook::jsi::Array(rt_1, vec.size());

      std::for_each(vec.begin(), vec.end(), [&rt_1, &topics, i = 0](auto topic) mutable -> void {
        topics.setValueAtIndex(rt_1,
                               i,
                               facebook::jsi::String::createFromAscii(rt_1, topic.data()));
        i++;
      });

      return topics;
    }));

    this->setProperty(rt,
                      "getUserData",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getUserData"),
                                                                      0,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;
      auto userDataNativeState = std::make_shared<WebSocketUserDataNativeState>(ws->getUserData());
      return WebSocketUserDataObject(rt_1, std::move(userDataNativeState));
    }));

    this->setProperty(rt,
                      "isSubscribed",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "isSubscribed"),
                                                                      1,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;

      if(!arguments) {
        return {rt_1, false};
      }

      auto topic = RecognizedString(rt_1, arguments[0]);
      if(!topic.isValid()) {
        return {rt_1, false};
      }

      return {rt_1, ws->isSubscribed(topic.getStringView())};
    }));

    this->setProperty(rt,
                      "ping",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "ping"),
                                                                      1,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;

      if(!arguments) {
        return {rt_1, int(0)};
      }

      auto message = RecognizedString(rt_1, arguments[0]);
      if(!message.isValid()){
        return {rt_1, int(0)};
      }

      auto sendStatus = ws->send(message.getStringView(), uWS::OpCode::PING);
      return {rt_1, sendStatus};
    }));

    this->setProperty(rt,
                      "publish",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "publish"),
                                                                      4,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      if(!arguments) {
        return {rt_1, false};
      }

      auto topic = RecognizedString(rt_1, arguments[0]);
      if(!topic.isValid()) {
        return {rt_1, false};
      }

      auto message = RecognizedString(rt_1, arguments[1]);
      if(!message.isValid()) {
        return {rt_1, false};
      }

      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;

      auto isBinary = arguments[2].isBool() && arguments[2].asBool();
      auto compress = arguments[3].isBool() && arguments[3].asBool();

      bool success = ws->publish(topic.getStringView(),
                                 message.getStringView(),
                                 isBinary ? uWS::OpCode::BINARY : uWS::OpCode::TEXT,
                                 compress);
      return {rt_1, success};
    }));

    this->setProperty(rt,
                      "send",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "send"),
                                                                      3,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      if(!arguments) {
        return facebook::jsi::Value::undefined();
      }

      auto message = RecognizedString(rt_1, arguments[0]);
      if(!message.isValid()) {
        return facebook::jsi::Value::undefined();
      }

      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;

      auto isBinary = arguments[1].isBool() && arguments[1].asBool();
      auto compress = arguments[2].isBool() && arguments[2].asBool();

      double sendStatus = ws->send(message.getStringView(),
                                   isBinary ? uWS::OpCode::BINARY : uWS::OpCode::TEXT,
                                   compress);
      return {rt_1, sendStatus};
    }));

    this->setProperty(rt,
                      "sendFirstFragment",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "sendFirstFragment"),
                                                                      3,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      if(!arguments) {
        return facebook::jsi::Value::undefined();
      }

      auto message = RecognizedString(rt_1, arguments[0]);
      if(!message.isValid()) {
        return facebook::jsi::Value::undefined();
      }

      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;

      auto isBinary = arguments[1].isBool() && arguments[1].asBool();
      auto compress = arguments[2].isBool() && arguments[2].asBool();

      double sendStatus = ws->sendFirstFragment(message.getStringView(),
                                                isBinary ? uWS::OpCode::BINARY : uWS::OpCode::TEXT,
                                                compress);
      return {rt_1, sendStatus};
    }));

    this->setProperty(rt,
                      "sendFragment",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "sendFragment"),
                                                                      2,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      if(!arguments) {
        return facebook::jsi::Value::undefined();
      }

      auto message = RecognizedString(rt_1, arguments[0]);
      if(!message.isValid()) {
        return facebook::jsi::Value::undefined();
      }

      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;

      auto compress = arguments[1].isBool() && arguments[1].asBool();

      double sendStatus = ws->sendFragment(message.getStringView(),
                                           compress);
      return {rt_1, sendStatus};
    }));

    this->setProperty(rt,
                      "sendLastFragment",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "sendLastFragment"),
                                                                      2,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      if(!arguments) {
        return facebook::jsi::Value::undefined();
      }

      auto message = RecognizedString(rt_1, arguments[0]);
      if(!message.isValid()) {
        return facebook::jsi::Value::undefined();
      }

      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;

      auto compress = arguments[1].isBool() && arguments[1].asBool();

      double sendStatus = ws->sendLastFragment(message.getStringView(),
                                               compress);
      return {rt_1, sendStatus};
    }));

    this->setProperty(rt,
                      "subscribe",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "subscribe"),
                                                                      1,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      if(!arguments) {
        return {rt_1, false};
      }

      auto topic = RecognizedString(rt_1, arguments[0]);
      if(!topic.isValid()) {
        return {rt_1, false};
      }

      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;
      bool success = ws->subscribe(topic.getStringView());
      return {rt_1, success};
    }));

    this->setProperty(rt,
                      "unsubscribe",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "unsubscribe"),
                                                                      1,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      if(!arguments) {
        return {rt_1, false};
      }

      auto topic = RecognizedString(rt_1, arguments[0]);
      if(!topic.isValid()) {
        return {rt_1, false};
      }

      auto ws = thisValue.asObject(rt_1).getNativeState<WebSocketNativeState>(rt_1)->ws;
      bool success = ws->unsubscribe(topic.getStringView());
      return {rt_1, success};
    }));

  } // WebSocketObject

}; // class WebSocketObject

} // namespace uws_react_native
