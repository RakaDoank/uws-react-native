#pragma once

#include <UwsReactNativeSpecsJSI.h>
#include "app/TemplatedAppObject.h"

namespace facebook::react {

class UwsReactNativeModule : public NativeUwsReactNativeCxxSpec<UwsReactNativeModule> {

public:
  UwsReactNativeModule(std::shared_ptr<CallInvoker> jsInvoker);

  uws_react_native::TemplatedAppObject App(facebook::jsi::Runtime &rt,
                                           std::optional<facebook::jsi::Object> appOptions);

  facebook::jsi::Object getParts(facebook::jsi::Runtime &rt,
                                 facebook::jsi::Object body,
                                 facebook::jsi::String contentType);

  void _us_listen_socket_close(facebook::jsi::Runtime &rt,
                              double id
                              /*facebook::jsi::Object listenSocket*/);

  double _us_socket_local_port(facebook::jsi::Runtime &rt,
                            double id
                            /*facebook::jsi::Object socket*/);

};

}
