#pragma once

#include <UwsReactNativeSpecsJSI.h>
#include "app/TemplatedAppObject.h"
#include "uWebSockets/PerMessageDeflate.h"

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

  double DISABLED(facebook::jsi::Runtime &rt) {
    return uWS::DISABLED;
  }

  double SHARED_COMPRESSOR(facebook::jsi::Runtime &rt) {
    return uWS::SHARED_COMPRESSOR;
  }

  double SHARED_DECOMPRESSOR(facebook::jsi::Runtime &rt) {
    return uWS::SHARED_DECOMPRESSOR;
  }

  double DEDICATED_COMPRESSOR_3KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_COMPRESSOR_3KB;
  }

  double DEDICATED_COMPRESSOR_4KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_COMPRESSOR_4KB;
  }

  double DEDICATED_COMPRESSOR_8KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_COMPRESSOR_8KB;
  }

  double DEDICATED_COMPRESSOR_16KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_COMPRESSOR_16KB;
  }

  double DEDICATED_COMPRESSOR_32KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_COMPRESSOR_32KB;
  }

  double DEDICATED_COMPRESSOR_64KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_COMPRESSOR_64KB;
  }

  double DEDICATED_COMPRESSOR_128KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_COMPRESSOR_128KB;
  }

  double DEDICATED_COMPRESSOR_256KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_COMPRESSOR_256KB;
  }

  double DEDICATED_DECOMPRESSOR_32KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_DECOMPRESSOR_32KB;
  }

  double DEDICATED_DECOMPRESSOR_16KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_DECOMPRESSOR_16KB;
  }

  double DEDICATED_DECOMPRESSOR_8KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_DECOMPRESSOR_8KB;
  }

  double DEDICATED_DECOMPRESSOR_4KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_DECOMPRESSOR_4KB;
  }

  double DEDICATED_DECOMPRESSOR_2KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_DECOMPRESSOR_2KB;
  }

  double DEDICATED_DECOMPRESSOR_1KB(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_DECOMPRESSOR_1KB;
  }

  double DEDICATED_DECOMPRESSOR_512B(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_DECOMPRESSOR_512B;
  }

  double DEDICATED_DECOMPRESSOR(facebook::jsi::Runtime &rt) {
    return uWS::DEDICATED_DECOMPRESSOR;
  }

};

}
