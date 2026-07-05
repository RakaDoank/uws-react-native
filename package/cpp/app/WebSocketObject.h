#pragma once

#include <memory>
#include <jsi/jsi.h>
#include "uWebSockets/App.h"

namespace uws_react_native {

/// Only use this in the JavaScript thread
struct WebSocketObject : public facebook::jsi::Object {

public:
  WebSocketObject(facebook::jsi::Runtime &rt,
                  const std::shared_ptr<uWS::WebSocket<false, true, facebook::jsi::Object>> &ws) : facebook::jsi::Object(rt) {
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
#ifdef REACT_NATIVE_DEBUG
      if(!arguments) {
        throw facebook::jsi::JSError(rt_1, "Expected a function from the first argument");
      }
      if(!arguments[0].isObject()) {
        throw facebook::jsi::JSError(rt_1, "Expected a function from the first argument");
      }
#endif

      auto obj = arguments[0].asObject(rt_1);

#ifdef REACT_NATIVE_DEBUG
      if(!obj.isFunction(rt_1)) {
        throw facebook::jsi::JSError(rt_1, "Expected a function from the first argument");
      }
#endif

      ws->cork([&rt_1, callback = std::move(obj).asFunction(rt_1)] {
        callback.call(rt_1);
      });

      return {rt_1, thisValue};
    }));
  }

};

}
