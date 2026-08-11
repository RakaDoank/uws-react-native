#pragma once

#include <ReactCommon/CallInvoker.h>
#include <ReactCommon/SchedulerPriority.h>
#include <memory>
#include <jsi/jsi.h>
#include <react/bridging/Function.h>
#include "AppRunner.h"
#include "HttpRequestObject.h"
#include "HttpResponseObject.h"
#include "WebSocketHostObject.h"
#include "WebSocketUserDataStorage.h"
#include "jsi/Buffer.h"
#include "uWebSockets/App.h"

namespace uws_react_native {

struct WebSocketBehaviorImpl : uWS::App::WebSocketBehavior<WebSocketUserDataStorage> {

public:
  WebSocketBehaviorImpl(facebook::jsi::Runtime &rt,
                        std::shared_ptr<facebook::react::CallInvoker> &jsInvoker,
                        facebook::jsi::Object &&object) {
    {
      auto prop = object.getProperty(rt, "close");
      if(prop.isObject()) {

        auto obj = prop.asObject(rt);
        if(obj.isFunction(rt)) {

          this->close = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws, int code, std::string_view message) -> void {
            // AppRunner thread
            fn.callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority, [webSocketHostObject = std::make_shared<WebSocketHostObject>(ws), code, message](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
              // React Native JS Runtime
              cb.call(rt_1,
                      facebook::jsi::Object::createFromHostObject(rt_1, webSocketHostObject),
                      code,
                      facebook::jsi::ArrayBuffer(rt_1,
                                                 std::make_shared<StringViewMutableBuffer>(message)));
            });
          };

        }

      }
    }

    {
      auto prop = object.getProperty(rt, "closeOnBackpressureLimit");
      if(prop.isBool()) {
        this->closeOnBackpressureLimit = prop.asBool();
      }
    }

    {
      auto prop = object.getProperty(rt, "compression");
      if(prop.isNumber()) {
        this->compression = (uWS::CompressOptions) prop.asNumber();
      }
    }

    {
      auto prop = object.getProperty(rt, "drain");
      if(prop.isObject()) {

        auto obj = prop.asObject(rt);
        if(obj.isFunction(rt)) {

          this->drain = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws) -> void {
            // AppRunner thread
            fn.callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority, [webSocketHostObject = std::make_shared<WebSocketHostObject>(ws)](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
              // React Native JS Runtime
              cb.call(rt_1,
                      facebook::jsi::Object::createFromHostObject(rt_1, webSocketHostObject));
            });
          };

        }

      }
    }

    {
      auto prop = object.getProperty(rt, "dropped");
      if(prop.isObject()) {

        auto obj = prop.asObject(rt);
        if(obj.isFunction(rt)) {

          this->dropped = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws, std::string_view message, uWS::OpCode opCode) -> void {
            // AppRunner thread
            fn.callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority, [webSocketHostObject = std::make_shared<WebSocketHostObject>(ws), message, opCode](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
              // React Native JS Runtime
              cb.call(rt_1,
                      facebook::jsi::Object::createFromHostObject(rt_1, webSocketHostObject),
                      facebook::jsi::ArrayBuffer(rt_1, std::make_shared<StringViewMutableBuffer>(message)),
                      opCode == uWS::OpCode::BINARY);
            });
          };

        }

      }
    }

    {
      auto prop = object.getProperty(rt, "idleTimeout");
      if(prop.isNumber()) {

        auto number = prop.asNumber();
        if(number >= 0 && number <= USHRT_MAX) {
          this->idleTimeout = static_cast<unsigned short>(number);
        }

      }
    }

    {
      auto prop = object.getProperty(rt, "maxBackpressure");
      if(prop.isNumber()) {

        auto number = prop.asNumber();
        if(number >= 0 && number <= UINT_MAX) {
          this->maxBackpressure = static_cast<unsigned int>(number);
        }

      }
    }

    {
      auto prop = object.getProperty(rt, "maxLifetime");
      if(prop.isNumber()) {

        auto number = prop.asNumber();
        if(number >= 0 && number <= USHRT_MAX) {
          this->maxLifetime = static_cast<unsigned short>(number);
        }

      }
    }

    {
      auto prop = object.getProperty(rt, "maxPayloadLength");
      if(prop.isNumber()) {

        auto number = prop.asNumber();
        if(number >= 0 && number <= UINT_MAX) {
          this->maxPayloadLength = static_cast<unsigned int>(number);
        }

      }
    }

    {
      auto prop = object.getProperty(rt, "message");
      if(prop.isObject()) {

        auto obj = prop.asObject(rt);
        if(obj.isFunction(rt)) {

          this->message = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws, std::string_view message, uWS::OpCode opCode) -> void {
            // AppRunner thread
            fn.callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority, [webSocketHostObject = std::make_shared<WebSocketHostObject>(ws), message, opCode](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
              // React Native JS Runtime
              cb.call(rt_1,
                      facebook::jsi::Object::createFromHostObject(rt_1, webSocketHostObject),
                      facebook::jsi::ArrayBuffer(rt_1, std::make_shared<StringViewMutableBuffer>(message)),
                      opCode == uWS::OpCode::BINARY);
            });
          };

        }

      }
    }

    {
      auto prop = object.getProperty(rt, "open");
      if(prop.isObject()) {

        auto obj = prop.asObject(rt);
        if(obj.isFunction(rt)) {

          this->open = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws) -> void {
            // AppRunner thread
            fn.callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority, [webSocketHostObject = std::make_shared<WebSocketHostObject>(ws)](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
              // React Native JS Runtime
              cb.call(rt_1,
                      facebook::jsi::Object::createFromHostObject(rt_1, webSocketHostObject));
            });
          };

        }

      }
    }

    {
      auto prop = object.getProperty(rt, "ping");
      if(prop.isObject()) {

        auto obj = prop.asObject(rt);
        if(obj.isFunction(rt)) {

          this->ping = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws, std::string_view message) -> void {
            // AppRunner thread
            fn.callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority, [webSocketHostObject = std::make_shared<WebSocketHostObject>(ws), message](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
              // React Native JS Runtime
              cb.call(rt_1,
                      facebook::jsi::Object::createFromHostObject(rt_1, webSocketHostObject),
                      facebook::jsi::ArrayBuffer(rt_1, std::make_shared<StringViewMutableBuffer>(message)));
            });
          };

        }

      }
    }

    {
      auto prop = object.getProperty(rt, "pong");
      if(prop.isObject()) {

        auto obj = prop.asObject(rt);
        if(obj.isFunction(rt)) {

          this->pong = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws, std::string_view message) -> void {
            // AppRunner thread
            fn.callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority, [webSocketHostObject = std::make_shared<WebSocketHostObject>(ws), message](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
              // React Native JS Runtime
              cb.call(rt_1,
                      facebook::jsi::Object::createFromHostObject(rt_1, webSocketHostObject),
                      facebook::jsi::ArrayBuffer(rt_1, std::make_shared<StringViewMutableBuffer>(message)));
            });
          };

        }

      }
    }

    {
      auto prop = object.getProperty(rt, "sendPingsAutomatically");
      if(prop.isBool()) {
        this->sendPingsAutomatically = prop.asBool();
      }
    }

    {
      auto prop = object.getProperty(rt, "subscription");
      if(prop.isObject()) {

        auto obj = prop.asObject(rt);
        if(obj.isFunction(rt)) {

          this->subscription = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker)](auto *ws, std::string_view topic, int newCount, int oldCount) -> void {
            // AppRunner thread
            fn.callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority, [webSocketHostObject = std::make_shared<WebSocketHostObject>(ws), topic, newCount, oldCount](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) -> void {
              // React Native JS Runtime
              cb.call(rt_1,
                      facebook::jsi::Object::createFromHostObject(rt_1, webSocketHostObject),
                      facebook::jsi::ArrayBuffer(rt_1, std::make_shared<StringViewMutableBuffer>(topic)),
                      newCount,
                      oldCount);
            });
          };

        }

      }
    }

    {
      auto prop = object.getProperty(rt, "upgrade");
      if(prop.isObject()) {

        auto obj = prop.asObject(rt);
        if(obj.isFunction(rt)) {

          this->upgrade = [fn = facebook::react::AsyncCallback(rt, std::move(obj).asFunction(rt), jsInvoker), &jsInvoker](auto *res, auto *req, us_socket_context_t *context) -> void {
            // AppRunner thread
            auto httpResponseObjectProvider = std::make_shared<HttpResponseObjectProvider>(res);

            /// Intentionally I have to take another copy of uWS::HttpRequest here to be consumed from JS thread
            /// I always get "bad_alloc" error if I didn't this
            auto httpRequest = std::make_shared<uWS::HttpRequest>(*req);

            fn.callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority, [httpResponseObjectProvider,
                                                                                        httpRequest,
                                                                                        &jsInvoker,
                                                                                        contextAddress = reinterpret_cast<uintptr_t>(context)](facebook::jsi::Runtime &rt_1, facebook::jsi::Function &cb) {
              // React Native JS runtime
              if(httpResponseObjectProvider && httpRequest) {
                cb.call(rt_1,
                        HttpResponseObject(rt_1, httpResponseObjectProvider, jsInvoker),
                        HttpRequestObject(rt_1, httpRequest),
                        facebook::jsi::BigInt::fromUint64(rt_1, contextAddress));
              }
            });

            /// Same like the .get, .post, .put, and others in the TemplatedAppObject.h
            /// We have to predefined the res->onAborted here
            res->onAborted([httpResponseObjectProvider]() -> void {
              if(httpResponseObjectProvider->dataAbort.callback) {
                httpResponseObjectProvider->dataAbort.callback->call(facebook::jsi::Value::undefined());
              }
            });
          };

        }

      }
    }
  } // WebSocketBehaviorImpl
}; // WebSocketBehaviorImpl

}
