#pragma once

#include <array>
#include <jsi/jsi.h>
#include "RecognizedString.h"
#include "WebSocketUserDataStorage.h"
#include "uWebSockets/App.h"

namespace uws_react_native {

class WebSocketHostObject : public facebook::jsi::HostObject {

public:
  WebSocketHostObject(uWS::WebSocket<false, true, WebSocketUserDataStorage> *ws) {
    this->ws = ws;
  }

  facebook::jsi::Value get(facebook::jsi::Runtime &rt,
                           const facebook::jsi::PropNameID &propName) override {
    auto name = propName.utf8(rt);

    if(name == "close") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             0,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        this->ws->close();
        return facebook::jsi::Value::undefined();
      });
    }

    if(name == "cork") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             1,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        this->ws->cork([&rt_1, cb = arguments[0].asObject(rt_1).asFunction(rt_1)] {
          cb.call(rt_1);
        });

        return {rt_1, thisValue};
      });
    }

    if(name == "end") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             2,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {

        if(!arguments) {
          this->ws->end();
          return facebook::jsi::Value::undefined();
        }

        int code = 0;

        if(arguments[0].isNumber()) {
          code = static_cast<int>(arguments[0].asNumber());
        }

        auto message = RecognizedString(rt_1, arguments[1]);
        if(!message.isValid()) {
          this->ws->end(code, {});
          return facebook::jsi::Value::undefined();
        }

        this->ws->end(code, message.getStringView());
        return {rt_1, thisValue};
      });
    }

    if(name == "getBufferedAmount") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             0,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        return {rt_1, static_cast<double>(this->ws->getBufferedAmount())};
      });
    }

    if(name == "getRemoteAddress") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             0,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        auto remoteAddress = this->ws->getRemoteAddress();
        return facebook::jsi::ArrayBuffer(rt_1,
                                          std::make_shared<uws_react_native::StringViewMutableBuffer>(remoteAddress));
      });
    }

    if(name == "getRemoteAddressAsText") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             0,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        return facebook::jsi::String::createFromAscii(rt_1, this->ws->getRemoteAddressAsText().data());
      });
    }

    if(name == "getRemotePort") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             0,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        return {rt_1, static_cast<double>(this->ws->getRemotePort())};
      });
    }

    if(name == "getTopics") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             0,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
        /// Using jsi Array with zero element and "push" it later
        /// is only supported in React Native >= 0.86

        auto vec = std::vector<std::string_view>();

        this->ws->iterateTopics([&vec](std::string_view topic) -> void {
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
      });
    }

    if(name == "getUserData") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             0,
                                                             [this](facebook::jsi::Runtime &rt_1,
                                                                    const facebook::jsi::Value &thisValue,
                                                                    const facebook::jsi::Value *arguments,
                                                                    size_t count) -> facebook::jsi::Value {
//        return WebSocketUserDataObject(rt_1,
//                                       std::make_shared<WebSocketUserDataObjectProvider *>(this->ws->getUserData()));
        return facebook::jsi::Object::createFromHostObject(rt_1,
                                                           std::make_shared<WebSocketUserDataHostObject>(this->ws->getUserData()));
      });
    }

    // isSubscribed
    if(name == "isSubscribed") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             1,
                                                             [this](facebook::jsi::Runtime &rt_1,
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

        return {rt_1, this->ws->isSubscribed(topic.getStringView())};
      });
    }

    // ping
    if(name == "ping") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             1,
                                                             [this](facebook::jsi::Runtime &rt_1,
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

        auto sendStatus = this->ws->send(message.getStringView(), uWS::OpCode::PING);
        return {rt_1, sendStatus};
      });
    }

    if(name == "publish") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             4,
                                                             [this](facebook::jsi::Runtime &rt_1,
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

        bool success = this->ws->publish(topic.getStringView(),
                                         message.getStringView(),
                                         isBinary ? uWS::OpCode::BINARY : uWS::OpCode::TEXT,
                                         compress);
        return {rt_1, success};
      });
    }

    if(name == "send") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             3,
                                                             [this](facebook::jsi::Runtime &rt_1,
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

        double sendStatus = this->ws->send(message.getStringView(),
                                           isBinary ? uWS::OpCode::BINARY : uWS::OpCode::TEXT,
                                           compress);
        return {rt_1, sendStatus};
      });
    }

    if(name == "sendFirstFragment") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             3,
                                                             [this](facebook::jsi::Runtime &rt_1,
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

        double sendStatus = this->ws->sendFirstFragment(message.getStringView(),
                                                  isBinary ? uWS::OpCode::BINARY : uWS::OpCode::TEXT,
                                                  compress);
        return {rt_1, sendStatus};
      });
    }

    if(name == "sendFragment") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             2,
                                                             [this](facebook::jsi::Runtime &rt_1,
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

        auto compress = arguments[1].isBool() && arguments[1].asBool();

        double sendStatus = this->ws->sendFragment(message.getStringView(),
                                                   compress);
        return {rt_1, sendStatus};
      });
    }

    if(name == "sendLastFragment") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             2,
                                                             [this](facebook::jsi::Runtime &rt_1,
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

        auto compress = arguments[1].isBool() && arguments[1].asBool();

        double sendStatus = ws->sendLastFragment(message.getStringView(),
                                                 compress);
        return {rt_1, sendStatus};
      });
    }

    if(name == "subscribe") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             1,
                                                             [this](facebook::jsi::Runtime &rt_1,
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
      });
    }

    if(name == "unsubscribe") {
      return facebook::jsi::Function::createFromHostFunction(rt,
                                                             propName,
                                                             1,
                                                             [this](facebook::jsi::Runtime &rt_1,
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
  uWS::WebSocket<false, true, WebSocketUserDataStorage> *ws;

  std::array<std::string, 18> propertyNames = {"close",
                                               "cork",
                                               "end",
                                               "getBufferedAmount",
                                               "getRemoteAddress",
                                               "getRemoteAddressAsText",
                                               "getRemotePort",
                                               "getTopics",
                                               "getUserData",
                                               "isSubscribed",
                                               "ping",
                                               "publish",
                                               "send",
                                               "sendFirstFragment",
                                               "sendFragment",
                                               "sendLastFragment",
                                               "subscribe",
                                               "unsubscribe"};

};

}