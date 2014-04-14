#include <node.h>
#include "PooObject.h"

using namespace v8;


static void Log(v8::Local<v8::Value> value) {
    String::Utf8Value utf8(value->ToString());
    printf("  >> %s\n", *utf8);
}

static void Log(v8::Handle<v8::Value> value) {
    String::Utf8Value utf8(value->ToString());
    printf("  !> %s\n", *utf8);
}

Persistent<Function> PooObject::ctor;

// Share the object instance as an empty prototype
void PooObject::Init(Handle<Object> exports) {
  Local<FunctionTemplate> tpl = FunctionTemplate::New(CtorNew);
  tpl->SetClassName(String::NewSymbol("PooClass"));
  ctor = Persistent<PooObject>::New(tpl->GetFunction());
  exports->Set(String::NewSymbol("Class"), ctor);
}


Handle<Value> PooObject::CtorNew(const Arguments& args) {
  HandleScope scope;
  if (args.IsConstructCall()) {
    // Invoked as constructor
    return args.This();
  } else {
    // Invoked as plain function, turn into construct call.
    return scope.Close(ctor->NewInstance());
  }
  
}

// sets a property
bool PooObject::Set(Handle<Value> key, Handle<Value> value, PropertyAttribute attribs) {
  printf("Set a property \n");
  Log(key);
  Log(value);
  return Object::Set(key, value, attribs);
}
// gets a property
Local<Value> PooObject::Get(Handle<Value> key) {
  printf("Reads a property \n");
  Local<Value> value = Object::Get(key);
  Log(key);
  Log(value);
  return value;
}
// returns an array with object properties
Local<Array> PooObject::GetOwnPropertyNames() {
  printf("List properties \n");
  return Object::GetOwnPropertyNames();
}