#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "glzclass.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  GlzClass::Init(exports);
}

NODE_MODULE(addon, InitAll)