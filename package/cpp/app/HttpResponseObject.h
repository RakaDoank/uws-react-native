#pragma once

#include <ReactCommon/CallInvoker.h>
#include <jsi/jsi.h>
#include <react/bridging/Function.h>
#include <utility>
#include "HttpResponseObjectNativeState.h"
#include "jsi/Buffer.h"
#include "RecognizedString.h"
#include "WebSocketUserDataNativeState.h"
#include "WebSocketUserDataObject.h"
#include "WebSocketUserDataStorage.h"
#include "uWebSockets/App.h"

namespace uws_react_native {

/// Only use this in the JavaScript thread
class HttpResponseObject : public facebook::jsi::Object {

public:
  HttpResponseObject(facebook::jsi::Runtime &rt,
                     std::shared_ptr<facebook::react::CallInvoker> &jsInvoker,
                     const std::shared_ptr<HttpResponseObjectNativeState> &_nativeState) : facebook::jsi::Object(rt) {

    this->setNativeState(rt, _nativeState);

    this->setProperty(rt,
                      "close",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "close"),
                                                                      1,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);
      nativeState->res->close();
      return {rt_1, thisValue};
    }));

    this->setProperty(rt,
                      "cork",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "cork"),
                                                                      1,
                                                                      [&jsInvoker](facebook::jsi::Runtime &rt_1,
                                                                                   const facebook::jsi::Value &thisValue,
                                                                                   const facebook::jsi::Value *arguments,
                                                                                   size_t count) mutable -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);

#ifdef REACT_NATIVE_DEBUG
      nativeState->isInsideCork = true;
#endif

      nativeState->res->cork([fn = facebook::react::AsyncCallback<facebook::jsi::Value>(rt_1, arguments[0].asObject(rt_1).asFunction(rt_1), jsInvoker)]() {
        fn.callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority,
                            facebook::jsi::Value::undefined());
      });

      return {rt_1, thisValue};
    }));

    this->setProperty(rt,
                      "end", facebook::jsi::Function::createFromHostFunction(rt,
                                                                             facebook::jsi::PropNameID::forUtf8(rt, "end"),
                                                                             1,
                                                                             [](facebook::jsi::Runtime &rt_1,
                                                                                const facebook::jsi::Value &thisValue,
                                                                                const facebook::jsi::Value *arguments,
                                                                                size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);

      /// Due to JS run at different thread
      /// The race condition event is not avoidable under stress test
      /// Our predefined `res->onAborted` call earlier than JS callback
      /// This below makes JS side can call the "res.end" without attaching `onAborted` handler at all.
      /// If we know how to make a sync call across the thread, please update this.
      if(nativeState->dataAbort.isAlreadyAborted) {
        return {rt_1, thisValue};
      }
      auto body = RecognizedString(rt_1, arguments[0]).getStringView();

#ifdef REACT_NATIVE_DEBUG
      nativeState->assumeCorked(rt_1);
#endif
      nativeState->res->end(body);

      return {rt_1, thisValue};
    }));

    this->setProperty(rt,
                      "endWithoutBody",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "endWithoutBody"),
                                                                      2,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);

      /// Due to JS run at different thread
      /// The race condition event is not avoidable under stress test
      /// Our predefined `res->onAborted` call earlier than JS callback
      /// This below makes JS side can call the "res.end" without attaching `onAborted` handler at all.
      /// If we know how to make a sync call across the thread, please update this.
      if(nativeState->dataAbort.isAlreadyAborted) {
        return {rt_1, thisValue};
      }

      if(!arguments) {
        nativeState->res->endWithoutBody();
        return {rt_1, thisValue};
      }

      std::optional<double> reportedContentLength = std::nullopt;
      bool closeConnection = false;

      if(arguments[0].isNumber()) {
        reportedContentLength = arguments[0].asNumber();
      }

      if(arguments[1].isBool()) {
        closeConnection = arguments[1].asBool();
      }

#ifdef REACT_NATIVE_DEBUG
      nativeState->assumeCorked(rt_1);
#endif
      nativeState->res->endWithoutBody(reportedContentLength, closeConnection);

      return {rt_1, thisValue};
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
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);
      auto remoteAddress = nativeState->res->getRemoteAddressAsText();
      return facebook::jsi::String::createFromUtf8(rt_1, std::string(remoteAddress));
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
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);
      return facebook::jsi::BigInt::fromUint64(rt_1, nativeState->res->getRemotePort());
    }));

    this->setProperty(rt,
                      "getWriteOffset",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "getWriteOffset"),
                                                                      0,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);
      return facebook::jsi::BigInt::fromUint64(rt_1, nativeState->res->getWriteOffset());
    }));

    this->setProperty(rt,
                      "onAborted",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "onAborted"),
                                                                      1,
                                                                      [&jsInvoker](facebook::jsi::Runtime &rt_1,
                                                                                   const facebook::jsi::Value &thisValue,
                                                                                   const facebook::jsi::Value *arguments,
                                                                                   size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);
      auto callback = arguments[0].asObject(rt_1).asFunction(rt_1);

      if(nativeState->dataAbort.isAlreadyAborted) {
        facebook::react::AsyncCallback(rt_1, std::move(callback), jsInvoker).call();
      } else {
        nativeState->dataAbort.callback = std::make_shared<facebook::react::AsyncCallback<facebook::jsi::Value>>(rt_1, std::move(callback), jsInvoker);
      }

      return {rt_1, thisValue};
    }));

    this->setProperty(rt,
                      "onData",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "onData"),
                                                                      1,
                                                                      [&jsInvoker](facebook::jsi::Runtime &rt_1,
                                                                                   const facebook::jsi::Value &thisValue,
                                                                                   const facebook::jsi::Value *arguments,
                                                                                   size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);

      if(nativeState->dataBody.callback) {
        throw facebook::jsi::JSError(rt_1, "Cannot reassign onData or assign it with existing onDataV2 and/or onFullData handler");
      }

      /// Same usage as the onDataV2
      /// except the second parameter to the JS handler is the boolean `isLast`
      auto callback = arguments[0].asObject(rt_1).asFunction(rt_1);
      nativeState->dataBody.callback = std::make_unique<facebook::react::AsyncCallback<facebook::jsi::Value, facebook::jsi::Value>>(rt_1, std::move(callback), jsInvoker);

      /// This a late call
      if(
        nativeState->dataBody.isStopCollecting ||
        nativeState->dataBody.maxRemainingBodyLength == 0
      ) {
        nativeState->dataBody.callback->callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority,
                                                         [nativeState](facebook::jsi::Runtime &rt, facebook::jsi::Function &cb) {
          auto mutableBuffer = CharsMutableBuffer(nativeState->dataBody.buffer.get());
          cb.call(rt,
                  facebook::jsi::ArrayBuffer(rt, std::make_shared<CharsMutableBuffer>(std::move(mutableBuffer))),
                  nativeState->dataBody.maxRemainingBodyLength == 0);
        });
      }

      return facebook::jsi::Value::undefined();
    }));

    this->setProperty(rt,
                      "onDataV2",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "onDataV2"),
                                                                      1,
                                                                      [&jsInvoker](facebook::jsi::Runtime &rt_1,
                                                                                   const facebook::jsi::Value &thisValue,
                                                                                   const facebook::jsi::Value *arguments,
                                                                                   size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);

      if(nativeState->dataBody.callback) {
        throw facebook::jsi::JSError(rt_1, "Cannot reassign onDataV2 or assign it with existing onData and/or onFullData handler");
      }

      auto callback = arguments[0].asObject(rt_1).asFunction(rt_1);
      nativeState->dataBody.callback = std::make_unique<facebook::react::AsyncCallback<facebook::jsi::Value, facebook::jsi::Value>>(rt_1, std::move(callback), jsInvoker);

      /// This is a late call to the onDataV2 callback
      /// due to the onDataV2 predefined lambda has finished earlier
      /// or isStopCollecting is already marked
      if(
        nativeState->dataBody.buffer &&
        (nativeState->dataBody.isStopCollecting || nativeState->dataBody.maxRemainingBodyLength == 0)
      ) {
        nativeState->dataBody.callback
          ->callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority,
                             [nativeState](facebook::jsi::Runtime &rt, facebook::jsi::Function &cb) {
          auto mutableBuffer = CharsMutableBuffer(nativeState->dataBody.buffer.get());
          cb.call(rt,
                  facebook::jsi::ArrayBuffer(rt, std::make_shared<CharsMutableBuffer>(std::move(mutableBuffer))),
                  facebook::jsi::BigInt::fromUint64(rt, nativeState->dataBody.maxRemainingBodyLength));
        });
      }

      return facebook::jsi::Value::undefined();
    }));

    this->setProperty(rt,
                      "onFullData",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "onFullData"),
                                                                      1,
                                                                      [&jsInvoker](facebook::jsi::Runtime &rt_1,
                                                                                   const facebook::jsi::Value &thisValue,
                                                                                   const facebook::jsi::Value *arguments,
                                                                                   size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);

      if(nativeState->dataBody.callback) {
        throw facebook::jsi::JSError(rt_1, "Cannot reassign onFullData or assign it with existing onData and/or onDataV2 handler");
      }

      auto callback = arguments[0].asObject(rt_1).asFunction(rt_1);
      nativeState->dataBody.isCallbackForFullChunk = true;
      nativeState->dataBody.callback = std::make_unique<facebook::react::AsyncCallback<facebook::jsi::Value, facebook::jsi::Value>>(rt_1, std::move(callback), jsInvoker);

      /// This is a late call to the onFullData callback
      /// due to the onDataV2 predefined lambda has finished earlier
      /// or isStopCollecting is already marked
      if(
        nativeState->dataBody.buffer &&
        (nativeState->dataBody.isStopCollecting || nativeState->dataBody.maxRemainingBodyLength == 0)
      ) {
        nativeState->dataBody.callback
          ->callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority,
                             [nativeState](facebook::jsi::Runtime &rt, facebook::jsi::Function &cb) {
          auto mutableBuffer = CharsMutableBuffer(nativeState->dataBody.buffer.get());
          cb.call(rt,
                  facebook::jsi::ArrayBuffer(rt, std::make_shared<CharsMutableBuffer>(std::move(mutableBuffer))));
        });
      }

      return facebook::jsi::Value::undefined();
    }));

    this->setProperty(rt,
                      "onFullDataText",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "onFullDataText"),
                                                                      1,
                                                                      [&jsInvoker](facebook::jsi::Runtime &rt_1,
                                                                                   const facebook::jsi::Value &thisValue,
                                                                                   const facebook::jsi::Value *arguments,
                                                                                   size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);

      if(nativeState->dataBody.callbackStr) {
        throw facebook::jsi::JSError(rt_1, "Cannot reassign onFullDataText handler");
      }

      auto callback = arguments[0].asObject(rt_1).asFunction(rt_1);
      nativeState->dataBody.isCallbackForFullChunk = true;
      nativeState->dataBody.callbackStr = std::make_unique<facebook::react::AsyncCallback<facebook::jsi::Value, facebook::jsi::Value>>(rt_1, std::move(callback), jsInvoker);

      /// This is a late call to the onFullDataText callback
      /// due to the onDataV2 predefined lambda has finished earlier
      /// or isStopCollecting is already marked
      if(
        nativeState->dataBody.buffer &&
        (nativeState->dataBody.isStopCollecting || nativeState->dataBody.maxRemainingBodyLength == 0)
      ) {
        nativeState->dataBody.callbackStr
          ->callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority,
                             [nativeState](facebook::jsi::Runtime &rt, facebook::jsi::Function &cb) {
          cb.call(rt,
                  std::string(nativeState->dataBody.buffer->begin(), nativeState->dataBody.buffer->end()));
        });
      }

      return facebook::jsi::Value::undefined();
    }));

    /// In the meantime, uws-react-native is not good for huge streaming data.
    /// We cannot support the `res.onWritable`, because of the asynchronous call
    /// from our runner to the React Native JS thread.
    /// This may be supported until we can tie our JavaScript runtime with
    /// react-native-worklets.
//    this->setProperty(rt,
//                      "onWritable",
//                      facebook::jsi::Function::createFromHostFunction(rt,
//                                                                      facebook::jsi::PropNameID::forUtf8(rt, "onWritable"),
//                                                                      1,
//                                                                      [provider, &jsInvoker](facebook::jsi::Runtime &rt_1,
//                                                                                             const facebook::jsi::Value &thisValue,
//                                                                                             const facebook::jsi::Value *arguments,
//                                                                                             size_t count) -> facebook::jsi::Value {
//#ifdef REACT_NATIVE_DEBUG
//      /// Does JS users really need this check in runtime?
//      if(!arguments || !arguments[0].isObject()) {
//        throw facebook::jsi::JSError(rt_1, "Expects a function with boolean returned in the first argument.");
//      }
//#endif
//
//      provider->res->onWritable([fn = facebook::react::AsyncCallback(rt_1, arguments[0].asObject(rt_1).asFunction(rt_1), jsInvoker)](uintmax_t offset) -> bool {
//        fn.callWithPriority(facebook::react::SchedulerPriority::ImmediatePriority, [offset](facebook::jsi::Runtime &rt_2, facebook::jsi::Function &cb) -> void {
//          auto value = cb.call(rt_2, facebook::jsi::BigInt::fromUint64(rt_2, offset));
//          if(value.isBool()) {
//            // TODO
//          }
//          // TODO
//        });
//        return true;
//      });
//
//      return {rt_1, thisValue};
//    }));

    this->setProperty(rt,
                      "pause",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "pause"),
                                                                      0,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);
      nativeState->res->pause();
      return facebook::jsi::Value::undefined();
    }));

    this->setProperty(rt,
                      "resume",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "resume"),
                                                                      0,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);
      nativeState->res->resume();
      return facebook::jsi::Value::undefined();
    }));

    this->setProperty(rt,
                      "tryEnd",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "tryEnd"),
                                                                      2,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);

      /// Due to JS run at different thread
      /// The race condition event is not avoidable under stress test
      /// Our predefined `res->onAborted` call earlier than JS callback
      /// This below makes JS side can call the "res.end" without attaching `onAborted` handler at all.
      /// If we know how to make a JS sync call across the thread, please update this.
      if(nativeState->dataAbort.isAlreadyAborted) {
        return {rt_1, thisValue};
      }

      auto fullBodyOrChunk = RecognizedString(rt_1, arguments[0]).getStringView();
      auto totalSize = arguments[1].asNumber();

#ifdef REACT_NATIVE_DEBUG
      nativeState->assumeCorked(rt_1);
#endif
      auto tryEndResult = nativeState->res->tryEnd(fullBodyOrChunk, static_cast<uintmax_t>(totalSize));

      return facebook::jsi::Array::createWithElements(rt_1, {tryEndResult.first, tryEndResult.second});
    }));

    this->setProperty(rt, "upgrade", facebook::jsi::Function::createFromHostFunction(rt,
                                                                                     facebook::jsi::PropNameID::forUtf8(rt, "upgrade"),
                                                                                     5,
                                                                                     [](facebook::jsi::Runtime &rt_1,
                                                                                        const facebook::jsi::Value &thisValue,
                                                                                        const facebook::jsi::Value *arguments,
                                                                                        size_t count) -> facebook::jsi::Value {
      if(!arguments || count != 5 ||
         !arguments[1].isString() ||
         !arguments[2].isString() ||
         !arguments[3].isString() ||
         !arguments[4].isBigInt()) {
        return facebook::jsi::Value::undefined();
      }

      if(!arguments[0].isObject()) {
        return facebook::jsi::Value::undefined();
      }

      auto userDataFnObj = arguments[0].asObject(rt_1);
      if(!userDataFnObj.isFunction(rt_1)) {
        return facebook::jsi::Value::undefined();
      }

      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);

      /// We are not supposed to store the user data object inside of singleton member,
      /// such as map, vector, or any else.
      /// See this manual
      /// https://github.com/uNetworking/uWebSockets/blob/master/misc/READMORE.md#the-appws-route
      ///
      /// Not like uWebSockets.js, there is no equivalent of v8::UniquePersistent in JSI.
      /// So, instead of holding an JS object,
      /// we store user data as plain struct, and we provide construct the JS object later.
      /// See WebSocketUserDataStorage.h
      auto userDataStorage = WebSocketUserDataStorage();

      auto userDataFn = userDataFnObj.asFunction(rt_1);
      auto secWebSocketKey = arguments[1].asString(rt_1).utf8(rt_1);
      auto secWebSocketProtocol = arguments[2].asString(rt_1).utf8(rt_1);
      auto secWebSocketExtensions = arguments[3].asString(rt_1).utf8(rt_1);
      auto context = arguments[4].asBigInt(rt_1).asUint64(rt_1);

      userDataFn.call(rt_1,
                      WebSocketUserDataObject(rt_1,
                                              std::make_shared<WebSocketUserDataNativeState>(&userDataStorage)));

#ifdef REACT_NATIVE_DEBUG
      nativeState->assumeCorked(rt_1);
#endif

      nativeState->res->upgrade(std::move(userDataStorage),
                             secWebSocketKey,
                             secWebSocketProtocol,
                             secWebSocketExtensions,
                             reinterpret_cast<us_socket_context_t *>(context));

      return facebook::jsi::Value::undefined();
    }));

    this->setProperty(rt,
                      "write",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "write"),
                                                                      2,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);
      auto chunk = RecognizedString(rt_1, arguments[0]).getStringView();

#ifdef REACT_NATIVE_DEBUG
      nativeState->assumeCorked(rt_1);
#endif
      return nativeState->res->write(chunk);
    }));

    this->setProperty(rt,
                      "writeHeader",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "writeHeader"),
                                                                      2,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);
      auto headerKey = RecognizedString(rt_1, arguments[0]).getStringView();
      auto headerVal = RecognizedString(rt_1, arguments[1]).getStringView();

#ifdef REACT_NATIVE_DEBUG
      nativeState->assumeCorked(rt_1);
#endif
      nativeState->res->writeHeader(headerKey, headerVal);

      return {rt_1, thisValue};
    }));

    this->setProperty(rt,
                      "writeStatus",
                      facebook::jsi::Function::createFromHostFunction(rt,
                                                                      facebook::jsi::PropNameID::forUtf8(rt, "writeStatus"),
                                                                      1,
                                                                      [](facebook::jsi::Runtime &rt_1,
                                                                         const facebook::jsi::Value &thisValue,
                                                                         const facebook::jsi::Value *arguments,
                                                                         size_t count) -> facebook::jsi::Value {
      auto nativeState = thisValue.asObject(rt_1).getNativeState<HttpResponseObjectNativeState>(rt_1);
      auto status = RecognizedString(rt_1, arguments[0]).getStringView();

#ifdef REACT_NATIVE_DEBUG
      nativeState->assumeCorked(rt_1);
#endif
      nativeState->res->writeStatus(status);

      return {rt_1, thisValue};
    }));

  } // HttpResponseObject

}; // class HttpResponseObject

} // namespace uws_react_native
