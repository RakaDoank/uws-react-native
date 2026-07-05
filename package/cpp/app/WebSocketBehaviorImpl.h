#pragma once

#include <memory>
#include <jsi/jsi.h>
#include "WebSocketObject.h"
#include "jsi/Buffer.h"
#include "uWebSockets/App.h"

namespace uws_react_native {

struct WebSocketBehaviorImpl : uWS::App::WebSocketBehavior<facebook::jsi::Value> {

public:
  WebSocketBehaviorImpl(facebook::jsi::Runtime &rt,
                        std::shared_ptr<facebook::react::CallInvoker> &jsInvoker,
                        facebook::jsi::Object &&object) {

    // AppRunner thread
    {
      auto prop = object.getProperty(rt, "close");
#ifdef REACT_NATIVE_DEBUG
      if(!prop.isObject()) {
        throw facebook::jsi::JSError(rt, "The \"close\" property must be a function");
      }
#endif

      auto obj = prop.asObject(rt);

#ifdef REACT_NATIVE_DEBUG
      if(!obj.isFunction(rt)) {
        throw facebook::jsi::JSError(rt, "The \"close\" property must be a function");
      }
#endif

      this->close = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws, int code, std::string_view message) {
        fn.call([sharedWs = std::make_shared<uWS::WebSocket<false, true, facebook::jsi::Object>>(*ws), code, message](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) {
          cb.call(rt_1,
                  WebSocketObject(rt_1, sharedWs),
                  code,
                  facebook::jsi::ArrayBuffer(rt_1,
                                             std::make_shared<StringViewMutableBuffer>(message)));
        });
      };
    }
  }
};

}
