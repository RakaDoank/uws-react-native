#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <jsi/jsi.h>
#include <unordered_map>
#include <vector>
#include "RecognizedString.h"
#ifdef REACT_NATIVE_DEBUG
#include "jsi/Console.h"
#endif
#include "uWebSockets/App.h"

namespace uws_react_native {

class HttpRequestHostObject : public facebook::jsi::HostObject {

public:
  HttpRequestHostObject(uWS::HttpRequest *pReq) {
    /// Intentionally I have to take another copy of uWS::HttpRequest here to be consumed from JS thread
    /// I always get "bad_alloc" error if I didn't this
    this->req = std::make_shared<uWS::HttpRequest>(*pReq);
  }

  facebook::jsi::Value get(facebook::jsi::Runtime &rt,
                           const facebook::jsi::PropNameID &propName) override {
    const auto name = propName.utf8(rt);

    if(name == "forEach") {
      return facebook::jsi::Function::createFromHostFunction(rt, propName, 0, this->forEach);
    }

    if(name == "getCaseSensitiveMethod") {
      return facebook::jsi::Function::createFromHostFunction(rt, propName, 0, this->getCaseSensitiveMethod);
    }

    if(name == "getHeader") {
      return facebook::jsi::Function::createFromHostFunction(rt, propName, 1, this->getHeader);
    }

    if(name == "getMethod") {
      return facebook::jsi::Function::createFromHostFunction(rt, propName, 0, this->getMethod);
    }

    if(name == "getParameter") {
      return facebook::jsi::Function::createFromHostFunction(rt, propName, 1, this->getParameter);
    }

    if(name == "getQuery") {
      return facebook::jsi::Function::createFromHostFunction(rt, propName, 1, this->getQuery);
    }

    if(name == "getUrl") {
      return facebook::jsi::Function::createFromHostFunction(rt, propName, 0, this->getUrl);
    }

    if(name == "setYield") {
      return facebook::jsi::Function::createFromHostFunction(rt, propName, 1, this->setYield);
    }

    return facebook::jsi::Value::undefined();
  }

  void set(facebook::jsi::Runtime &rt,
           const facebook::jsi::PropNameID &name,
           const facebook::jsi::Value &value) override {
    throw facebook::jsi::JSError(rt, "WebSocket object is read-only.");
  }

  std::vector<facebook::jsi::PropNameID> getPropertyNames(facebook::jsi::Runtime &rt) override {
    std::vector<facebook::jsi::PropNameID> names = {};
    names.reserve(this->propertyNames.size());

    std::for_each(propertyNames.begin(), propertyNames.end(), [&rt, &names](std::string &name) -> void {
      names.emplace_back(facebook::jsi::PropNameID::forUtf8(rt, name));
    });

    return names;
  }

private:
  std::shared_ptr<uWS::HttpRequest> req = nullptr;

  std::array<std::string, 8> propertyNames = {"forEach",
                                              "getCaseSensitiveMethod",
                                              "getHeader",
                                              "getMethod",
                                              "getParameter",
                                              "getQuery",
                                              "getUrl",
                                              "setYield"};

  facebook::jsi::HostFunctionType forEach = [this](auto &rt,
                                                   auto &thisValue,
                                                   auto *arguments,
                                                   auto count) -> facebook::jsi::Value {
    auto callback = arguments[0].asObject(rt).asFunction(rt);
    std::for_each(this->req->begin(),
                  this->req->end(),
                  [&rt, callback_ = std::move(callback)](const auto &item) {
                    callback_.call(rt,
                                   facebook::jsi::String::createFromAscii(rt, std::string(item.first)),
                                   facebook::jsi::String::createFromAscii(rt, std::string(item.second)));
                  });
    return facebook::jsi::Value::undefined();
  };

  facebook::jsi::HostFunctionType getCaseSensitiveMethod = [this](auto &rt,
                                                                  auto &thisValue,
                                                                  auto *arguments,
                                                                  auto count) -> facebook::jsi::Value {
    return facebook::jsi::String::createFromUtf8(rt,
                                                 std::string(this->req->getCaseSensitiveMethod()));
  };

  facebook::jsi::HostFunctionType getHeader = [this](auto &rt,
                                                     auto &thisValue,
                                                     auto *arguments,
                                                     auto count) -> facebook::jsi::Value {
    if(!arguments) {
#ifdef REACT_NATIVE_DEBUG
      Console::warn(rt, "getHeader expects one argument");
#endif
      return facebook::jsi::Value::undefined();
    }

    auto lowerCasedHeader = RecognizedString(rt, arguments[0]);
    if(!lowerCasedHeader.isValid()) {
      return facebook::jsi::Value::undefined();
    }
    return facebook::jsi::String::createFromUtf8(rt,
                                                 std::string(this->req->getHeader(lowerCasedHeader.getStringView())));
  };

  facebook::jsi::HostFunctionType getMethod = [this](auto &rt,
                                                     auto &thisValue,
                                                     auto *arguments,
                                                     auto count) -> facebook::jsi::Value {
    return facebook::jsi::String::createFromUtf8(rt,
                                                 std::string(this->req->getMethod()));
  };

  facebook::jsi::HostFunctionType getParameter = [this](auto &rt,
                                                        auto &thisValue,
                                                        auto *arguments,
                                                        auto count) -> facebook::jsi::Value {
    if(!arguments) {
#ifdef REACT_NATIVE_DEBUG
      Console::warn(rt, "getParameter expects one argument");
#endif
      return facebook::jsi::Value::undefined();
    }

    std::string_view parameter;

    if(arguments[0].isNumber()) {
      // get by index
      auto index = arguments[0].asNumber();
      parameter = this->req->getParameter(static_cast<int>(std::floor(index)));
    } else {
      // get by name
      auto paramNamed = arguments[0].asString(rt).utf8(rt);
      parameter = this->req->getParameter(std::string_view(paramNamed));
    }

    if(parameter.data() == nullptr) {
      return facebook::jsi::Value::undefined();
    }
    return facebook::jsi::String::createFromAscii(rt,
                                                  std::string(parameter));
  };

  facebook::jsi::HostFunctionType getQuery = [this](auto &rt,
                                                    auto &thisValue,
                                                    auto *arguments,
                                                    auto count) -> facebook::jsi::Value {
    std::string_view query;

    if(!arguments || arguments[0].isUndefined()) {
      query = this->req->getQuery();
    } else if(arguments[0].isString()) {
      query = this->req->getQuery(arguments[0].asString(rt).utf8(rt));
    }

    if(query.data() == nullptr) {
      return facebook::jsi::Value::undefined();
    }

    return facebook::jsi::String::createFromAscii(rt,
                                                  std::string(query));
  };

  facebook::jsi::HostFunctionType getUrl = [this](auto &rt,
                                                  auto &thisValue,
                                                  auto *arguments,
                                                  auto count) -> facebook::jsi::Value {
    return facebook::jsi::String::createFromUtf8(rt,
                                                 std::string(this->req->getUrl()));
  };

  facebook::jsi::HostFunctionType setYield = [this](auto &rt,
                                                    auto &thisValue,
                                                    auto *arguments,
                                                    auto count) -> facebook::jsi::Value {
    if(!arguments) {
#ifdef REACT_NATIVE_DEBUG
      Console::warn(rt, "setYield expects a boolean argument");
#endif
      return {rt, thisValue};
    }

    this->req->setYield(arguments[0].asBool());
    return {rt, thisValue};
  };

};

} // namespace uws_react_native
