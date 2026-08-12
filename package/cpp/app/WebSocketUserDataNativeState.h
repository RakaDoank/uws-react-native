#pragma once

#include <jsi/jsi.h>
#include <memory>
#include "WebSocketUserDataStorage.h"

namespace uws_react_native {

class WebSocketUserDataNativeState : public facebook::jsi::NativeState {

public:
  WebSocketUserDataNativeState(WebSocketUserDataStorage *storage) {
    this->storage = storage;
  }

  WebSocketUserDataStorage *storage = nullptr;

}; // WebSocketUserDataNativeState

} // namespace uws_react_native
