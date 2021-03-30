#include "m4c0/objc/inject.hpp"

static void dummy() {
}
static const m4c0::objc::static_inject i { "mtkView:drawableSizeWillChange:", &dummy };
static const m4c0::objc::static_inject j { "drawInMTKView:", &dummy };
