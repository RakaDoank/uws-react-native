#import <Foundation/Foundation.h>
#import <ReactCommon/CxxTurboModuleUtils.h>
#import "ReactNativeUwsModule.h"

@interface ReactNativeUwsOnLoad : NSObject
@end

@implementation ReactNativeUwsOnLoad

+ (void)load {
  facebook::react::registerCxxModuleToGlobalModuleMap(std::string(facebook::react::ReactNativeUwsModule::kModuleName),
                                                      [](std::shared_ptr<facebook::react::CallInvoker> jsInvoker) {
    return std::make_shared<facebook::react::ReactNativeUwsModule>(jsInvoker);
  });
}

@end
