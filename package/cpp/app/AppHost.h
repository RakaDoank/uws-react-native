#pragma once

#include <jsi/jsi.h>
#include <memory>
#include "AppRunner.h"
#include "TemplatedAppObject.h"

namespace react_native_uws {

class AppHost {

private:
  std::function<void ()> closeHandler;

public:
  AppRunner appRunner = {};

  AppHost(std::function<void ()> &&closeHandler) {
    // TODO Implement the uWS::App ssl options
//    this->appRunner = std::make_shared<AppRunner>();

    this->closeHandler = closeHandler;
  }

  TemplatedAppObject getTemplatedAppObject(facebook::jsi::Runtime &rt,
                                           std::shared_ptr<facebook::react::CallInvoker> &jsInvoker,
                                           unsigned short id) {
    return {this->appRunner, rt, jsInvoker, id, [this]() {
      this->appRunner.close([this]() {
        this->closeHandler();
      });
    }};
  }

};

}