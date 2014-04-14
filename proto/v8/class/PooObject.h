#ifndef POOOBJECT_H
#define POOOBJECT_H

#include <node.h>

using namespace v8;

class PooObject : public Object {
  public:
    static Handle<Value> CtorNew(const Arguments& args);
    static void Init(Handle<Object> exports);

    // sets a property
    bool Set(Handle<Value> key, Handle<Value> value, PropertyAttribute attribs = None);
    // gets a property
    Local<Value> Get(Handle<Value> key);
    // returns an array with object properties
    Local<Array> GetOwnPropertyNames();

  private:
    static Persistent<Function> ctor;

};

#endif
