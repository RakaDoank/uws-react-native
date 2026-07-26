#pragma once

#include <memory>
#include <jsi/jsi.h>
#include <string>
#include <string_view>
#include <vector>
#include "RecognizedString.h"
#include "WebSocketUserData.h"
#include "jsi/Buffer.h"
#include "uWebSockets/App.h"

namespace uws_react_native {

/// Only use this in the JavaScript thread
struct WebSocketObject : public facebook::jsi::Object {

public:
  WebSocketObject(facebook::jsi::Runtime &rt,
                  const std::shared_ptr<uWS::WebSocket<false, true, std::shared_ptr<WebSocketUserData>>> &ws) : facebook::jsi::Object(rt) {

    this->setProperty(rt,
                      "close",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "close"),
                                                                      0,
                                                                      [ws](facebook::jsi::Runtime &rt_1,
                                                                           const facebook::jsi::Value &thisValue,
                                                                           const facebook::jsi::Value *arguments,
                                                                           size_t count) -> facebook::jsi::Value {
      ws->close();
      return {rt_1, thisValue};
    }));

    this->setProperty(rt,
                      "cork",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "cork"),
                                                                      1,
                                                                      [ws](facebook::jsi::Runtime &rt_1,
                                                                           const facebook::jsi::Value &thisValue,
                                                                           const facebook::jsi::Value *arguments,
                                                                           size_t count) -> facebook::jsi::Value {
      ws->cork([&rt_1, callback = arguments[0].asObject(rt_1).asFunction(rt_1)] {
        callback.call(rt_1);
      });

      return {rt_1, thisValue};
    }));

    this->setProperty(rt,
                      "end",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "end"),
                                                                      2,
                                                                      [ws](facebook::jsi::Runtime &rt_1,
                                                                           const facebook::jsi::Value &thisValue,
                                                                           const facebook::jsi::Value *arguments,
                                                                           size_t count) -> facebook::jsi::Value {
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
      return facebook::jsi::Value::undefined();
    }));

    this->setProperty(rt,
                      "getBufferedAmount",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getBufferedAmount"),
                                                                      0,
                                                                      [ws](facebook::jsi::Runtime &rt_1,
                                                                           const facebook::jsi::Value &thisValue,
                                                                           const facebook::jsi::Value *arguments,
                                                                           size_t count) -> facebook::jsi::Value {
      return {rt_1, static_cast<double>(ws->getBufferedAmount())};
    }));

    this->setProperty(rt,
                      "getRemoteAddress",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getRemoteAddress"),
                                                                      0,
                                                                      [ws](facebook::jsi::Runtime &rt_1,
                                                                           const facebook::jsi::Value &thisValue,
                                                                           const facebook::jsi::Value *arguments,
                                                                           size_t count) -> facebook::jsi::Value {
      auto remoteAddress = ws->getRemoteAddress();
      return facebook::jsi::ArrayBuffer(rt_1,
                                        std::make_shared<uws_react_native::StringViewMutableBuffer>(remoteAddress));
    }));

    this->setProperty(rt,
                      "getRemoteAddressAsText",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getRemoteAddressAsText"),
                                                                      0,
                                                                      [ws](facebook::jsi::Runtime &rt_1,
                                                                           const facebook::jsi::Value &thisValue,
                                                                           const facebook::jsi::Value *arguments,
                                                                           size_t count) -> facebook::jsi::Value {
      return facebook::jsi::String::createFromAscii(rt_1, ws->getRemoteAddressAsText().data());
    }));

    this->setProperty(rt,
                      "getRemotePort",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getRemotePort"),
                                                                      0,
                                                                      [ws](facebook::jsi::Runtime &rt_1,
                                                                           const facebook::jsi::Value &thisValue,
                                                                           const facebook::jsi::Value *arguments,
                                                                           size_t count) -> facebook::jsi::Value {
      return {rt_1, static_cast<double>(ws->getRemotePort())};
    }));

    this->setProperty(rt,
                      "getTopics",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getTopics"),
                                                                      0,
                                                                      [ws](facebook::jsi::Runtime &rt_1,
                                                                           const facebook::jsi::Value &thisValue,
                                                                           const facebook::jsi::Value *arguments,
                                                                           size_t count) -> facebook::jsi::Value {
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
                                                                      [ws](facebook::jsi::Runtime &rt_1,
                                                                           const facebook::jsi::Value &thisValue,
                                                                           const facebook::jsi::Value *arguments,
                                                                           size_t count) -> facebook::jsi::Value {
      return facebook::jsi::Object::createFromHostObject(rt_1,
                                                         *(ws->getUserData()));
    }));

    this->setProperty(rt,
                      "isSubscribed",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "isSubscribed"),
                                                                      1,
                                                                      [ws](facebook::jsi::Runtime &rt_1,
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

      return {rt_1, ws->isSubscribed(topic.getStringView())};
    }));

    this->setProperty(rt,
                      "ping",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "ping"),
                                                                      1,
                                                                      [ws](facebook::jsi::Runtime &rt_1,
                                                                           const facebook::jsi::Value &thisValue,
                                                                           const facebook::jsi::Value *arguments,
                                                                           size_t count) -> facebook::jsi::Value {
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
                                                                      [ws](facebook::jsi::Runtime &rt_1,
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
                                                                      [ws](facebook::jsi::Runtime &rt_1,
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
                                                                      [ws](facebook::jsi::Runtime &rt_1,
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
                                                                      [ws](facebook::jsi::Runtime &rt_1,
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

      auto compress = arguments[2].isBool() && arguments[2].asBool();

      double sendStatus = ws->sendFragment(message.getStringView(),
                                           compress);
      return {rt_1, sendStatus};
    }));

    this->setProperty(rt,
                      "sendLastFragment",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "sendLastFragment"),
                                                                      2,
                                                                      [ws](facebook::jsi::Runtime &rt_1,
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

      auto compress = arguments[2].isBool() && arguments[2].asBool();

      double sendStatus = ws->sendLastFragment(message.getStringView(),
                                               compress);
      return {rt_1, sendStatus};
    }));

    this->setProperty(rt,
                      "subscribe",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "subscribe"),
                                                                      1,
                                                                      [ws](facebook::jsi::Runtime &rt_1,
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

      bool success = ws->subscribe(topic.getStringView());
      return {rt_1, success};
    }));

    this->setProperty(rt,
                      "unsubscribe",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "unsubscribe"),
                                                                      1,
                                                                      [ws](facebook::jsi::Runtime &rt_1,
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

      bool success = ws->unsubscribe(topic.getStringView());
      return {rt_1, success};
    }));

  } // WebSocketObject

};

}
