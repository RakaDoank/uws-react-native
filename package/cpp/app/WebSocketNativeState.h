#pragma once

#include <jsi/jsi.h>
#include "WebSocketUserDataStorage.h"
#include "uWebSockets/WebSocket.h"

namespace uws_react_native {

class WebSocketNativeState : public facebook::jsi::NativeState {

public:
  WebSocketNativeState(uWS::WebSocket<false, true, WebSocketUserDataStorage> *ws) {
    this->ws = ws;
  } // WebSocketNativeState

  uWS::WebSocket<false, true, WebSocketUserDataStorage> *ws;

};

} // namespace uws_react_native
