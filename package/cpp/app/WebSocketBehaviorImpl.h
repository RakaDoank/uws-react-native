#pragma once

#include <ReactCommon/CallInvoker.h>
#include <ReactCommon/SchedulerPriority.h>
#include <memory>
#include <jsi/jsi.h>
#include <react/bridging/Function.h>
#include "WebSocketObject.h"
#include "WebSocketUserData.h"
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
      if(!prop.isObject()) {
        return;
      }

      auto obj = prop.asObject(rt);
      if(!obj.isFunction(rt)) {
        return;
      }

      this->close = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws, int code, std::string_view message) {
        fn.call([sharedWs = std::make_shared<uWS::WebSocket<false, true, std::shared_ptr<WebSocketUserData>>>(*ws), code, message](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
          cb.call(rt_1,
                  WebSocketObject(rt_1, sharedWs),
                  code,
                  facebook::jsi::ArrayBuffer(rt_1,
                                             std::make_shared<StringViewMutableBuffer>(message)));
        });
      };
    }

    {
      auto prop = object.getProperty(rt, "closeOnBackpressureLimit");
      if(!prop.isBool()) {
        return;
      }

      this->closeOnBackpressureLimit = prop.asBool();
    }

    {
      auto prop = object.getProperty(rt, "compression");
      if(!prop.isNumber()) {
        return;
      }

      this->compression = (uWS::CompressOptions) prop.asNumber();
    }

    // AppRunner thread
    {
      auto prop = object.getProperty(rt, "drain");
      if(!prop.isObject()) {
        return;
      }

      auto obj = prop.asObject(rt);
      if(!obj.isFunction(rt)) {
        return;
      }

      this->drain = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws) -> void {
        fn.call([sharedWs = std::make_shared<uWS::WebSocket<false, true, std::shared_ptr<WebSocketUserData>>>(*ws)](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
          cb.call(rt_1,
                  WebSocketObject(rt_1, sharedWs));
        });
      };
    }

    // AppRunner thread
    {
      auto prop = object.getProperty(rt, "dropped");
      if(!prop.isObject()) {
        return;
      }

      auto obj = prop.asObject(rt);
      if(!obj.isFunction(rt)) {
        return;
      }

      this->dropped = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws, std::string_view message, uWS::OpCode opCode) -> void {
        fn.call([sharedWs = std::make_shared<uWS::WebSocket<false, true, std::shared_ptr<WebSocketUserData>>>(*ws), message, opCode](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
          cb.call(rt_1,
                  WebSocketObject(rt_1, sharedWs),
                  facebook::jsi::ArrayBuffer(rt_1, std::make_shared<StringViewMutableBuffer>(message)),
                  opCode == uWS::OpCode::BINARY);
        });
      };
    }

    {
      auto prop = object.getProperty(rt, "idleTimeout");
      if(!prop.isNumber()) {
        return;
      }

      auto number = prop.asNumber();
      if(number < 0 || number > USHRT_MAX) {
        return;
      }

      this->idleTimeout = static_cast<unsigned short>(number);
    }

    {
      auto prop = object.getProperty(rt, "maxBackpressure");
      if(!prop.isNumber()) {
        return;
      }

      auto number = prop.asNumber();
      if(number < 0 || number > UINT_MAX) {
        return;
      }

      this->maxBackpressure = static_cast<unsigned int>(number);
    }

    {
      auto prop = object.getProperty(rt, "maxLifetime");
      if(!prop.isNumber()) {
        return;
      }

      auto number = prop.asNumber();
      if(number < 0 || number > USHRT_MAX) {
        return;
      }

      this->maxLifetime = static_cast<unsigned short>(number);
    }

    {
      auto prop = object.getProperty(rt, "maxPayloadLength");
      if(!prop.isNumber()) {
        return;
      }

      auto number = prop.asNumber();
      if(number < 0 || number > UINT_MAX) {
        return;
      }

      this->maxPayloadLength = static_cast<unsigned int>(number);
    }

    // AppRunner thread
    {
      auto prop = object.getProperty(rt, "message");
      if(!prop.isObject()) {
        return;
      }

      auto obj = prop.asObject(rt);
      if(!obj.isFunction(rt)) {
        return;
      }

      this->message = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws, std::string_view message, uWS::OpCode opCode) -> void {
        fn.call([sharedWs = std::make_shared<uWS::WebSocket<false, true, std::shared_ptr<WebSocketUserData>>>(*ws), message, opCode](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
          cb.call(rt_1,
                  WebSocketObject(rt_1, sharedWs),
                  facebook::jsi::ArrayBuffer(rt_1, std::make_shared<StringViewMutableBuffer>(message)),
                  opCode == uWS::OpCode::BINARY);
        });
      };
    }

    // AppRunner thread
    {
      auto prop = object.getProperty(rt, "open");
      if(!prop.isObject()) {
        return;
      }

      auto obj = prop.asObject(rt);
      if(!obj.isFunction(rt)) {
        return;
      }

      this->open = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws) -> void {
        fn.call([sharedWs = std::make_shared<uWS::WebSocket<false, true, std::shared_ptr<WebSocketUserData>>>(*ws)](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
          cb.call(rt_1,
                  WebSocketObject(rt_1, sharedWs));
        });
      };
    }

    // AppRunner thread
    {
      auto prop = object.getProperty(rt, "ping");
      if(!prop.isObject()) {
        return;
      }

      auto obj = prop.asObject(rt);
      if(!obj.isFunction(rt)) {
        return;
      }

      this->ping = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws, std::string_view message) -> void {
        fn.call([sharedWs = std::make_shared<uWS::WebSocket<false, true, std::shared_ptr<WebSocketUserData>>>(*ws), message](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
          cb.call(rt_1,
                  WebSocketObject(rt_1, sharedWs),
                  facebook::jsi::ArrayBuffer(rt_1, std::make_shared<StringViewMutableBuffer>(message)));
        });
      };
    }

    // AppRunner thread
    {
      auto prop = object.getProperty(rt, "pong");
      if(!prop.isObject()) {
        return;
      }

      auto obj = prop.asObject(rt);
      if(!obj.isFunction(rt)) {
        return;
      }

      this->pong = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws, std::string_view message) -> void {
        fn.call([sharedWs = std::make_shared<uWS::WebSocket<false, true, std::shared_ptr<WebSocketUserData>>>(*ws), message](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
          cb.call(rt_1,
                  WebSocketObject(rt_1, sharedWs),
                  facebook::jsi::ArrayBuffer(rt_1, std::make_shared<StringViewMutableBuffer>(message)));
        });
      };
    }

    {
      auto prop = object.getProperty(rt, "sendPingsAutomatically");
      if(!prop.isBool()) {
        return;
      }

      this->sendPingsAutomatically = prop.asBool();
    }

    // AppRunner thread
    {
      auto prop = object.getProperty(rt, "subscription");
      if(!prop.isObject()) {
        return;
      }

      auto obj = prop.asObject(rt);
      if(!obj.isFunction(rt)) {
        return;
      }

      this->subscription = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws, std::string_view topic, int newCount, int oldCount) -> void {
        fn.call([sharedWs = std::make_shared<uWS::WebSocket<false, true, std::shared_ptr<WebSocketUserData>>>(*ws), topic, newCount, oldCount](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
          cb.call(rt_1,
                  WebSocketObject(rt_1, sharedWs),
                  facebook::jsi::ArrayBuffer(rt_1, std::make_shared<StringViewMutableBuffer>(topic)),
                  newCount,
                  oldCount);
        });
      };
    }

    // AppRunner thread
    {
      auto prop = object.getProperty(rt, "upgrade");
      if(!prop.isObject()) {
        return;
      }

      auto obj = prop.asObject(rt);
      if(!obj.isFunction(rt)) {
        return;
      }

      this->upgrade = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker), &jsInvoker](auto *res, auto *req, us_socket_context_t *context) -> void {
        auto httpResponseObjectProvider = std::make_shared<HttpResponseObjectProvider>(res);
        auto httpRequestShared = std::make_shared<uWS::HttpRequest>(*req);

        fn.callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority, [httpResponseObjectProvider, httpRequestShared, &jsInvoker, contextAddress = reinterpret_cast<uintptr_t>(context)](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) {
          // React Native JS runtime
          if(httpResponseObjectProvider && httpRequestShared) {
            cb.call(rt_1,
                    HttpResponseObject(rt_1, httpResponseObjectProvider, jsInvoker),
                    HttpRequestObject(rt_1, httpRequestShared),
                    facebook::jsi::BigInt::fromUint64(rt_1, contextAddress));
          }
        });
      };
    }
  } // WebSocketBehaviorImpl
}; // WebSocketBehaviorImpl

}
