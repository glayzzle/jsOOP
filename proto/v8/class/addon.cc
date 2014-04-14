#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "glzclass.h"
#include "PooObject.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  GlzClass::Init(exports);
  PooObject::Init(exports);
}

NODE_MODULE(addon, InitAll)