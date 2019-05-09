#include "IModule.h"


static const char MODULE_VERSION[] = "1.0.0.180717";
static const char MODULE_NAME[] = "libWindowManager.so";

#if defined(__cplusplus)
extern "C" {
#endif

const iris::ModuleInfo IRIS_MODULE_INFO_SYM = {
        .version = MODULE_VERSION,
        .name = MODULE_NAME,
        .reserved = {0},
};

__attribute__((visibility("default"))) const iris::ModuleInfo* getModuleInfo() {
    return &IRIS_MODULE_INFO_SYM;
}

#if defined(__cplusplus)
}
#endif