#import <Foundation/Foundation.h>
#import <ReactCommon/CxxTurboModuleUtils.h>
#import "UwsReactNativeModule.h"

@interface UwsReactNativeOnLoad : NSObject
@end

@implementation UwsReactNativeOnLoad

+ (void)load {
  facebook::react::registerCxxModuleToGlobalModuleMap(std::string(facebook::react::UwsReactNativeModule::kModuleName),
                                                      [](std::shared_ptr<facebook::react::CallInvoker> jsInvoker) {
    return std::make_shared<facebook::react::UwsReactNativeModule>(jsInvoker);
  });
}

@end
