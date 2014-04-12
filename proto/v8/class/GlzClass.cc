#include <node.h>
#include "glzclass.h"

using namespace v8;

Persistent<Function> GlzClass::constructor;

GlzClass::GlzClass(double value) : value_(value) {
}

GlzClass::~GlzClass() {
}

static v8::Handle<Value> GetTitle(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
  // Extract the C++ request object from the JavaScript wrapper.
  GlzClass* instance = node::ObjectWrap::Unwrap<GlzClass>(info.Holder());
  return v8::String::New(instance->title.c_str());
}
// this.title=
static void SetTitle(Local<String> property, Local<Value> value, const AccessorInfo& info) {
  GlzClass* instance = node::ObjectWrap::Unwrap<GlzClass>(info.Holder());
  v8::String::Utf8Value v8str(value);
  instance->title = *v8str;
}

void GlzClass::Init(Handle<Object> exports) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("GlzClass"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype
    tpl->PrototypeTemplate()->Set(
            String::NewSymbol("properties"),
            FunctionTemplate::New(Properties)->GetFunction()
            );
    tpl->PrototypeTemplate()->Set(
            String::NewSymbol("extends"),
            FunctionTemplate::New(Extends)->GetFunction()
            );

    //this->tpl = tpl;


    constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("GlzClass"), constructor);


}

Handle<Value> GlzClass::New(const Arguments& args) {
    HandleScope scope;

    if (args.IsConstructCall()) {
        // Invoked as constructor: `new GlzClass(...)`
        double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
        GlzClass* obj = new GlzClass(value);
        obj->Wrap(args.This());
        return args.This();
    } else {
        // Invoked as plain function `GlzClass(...)`, turn into construct call.
        const int argc = 1;
        Local<Value> argv[argc] = {args[0]};
        return scope.Close(constructor->NewInstance(argc, argv));
    }
}

static void Log(v8::Local<v8::Value> value) {
    String::Utf8Value utf8(value->ToString());
    printf("> %s\n", *utf8);
}

Handle<Value> CommonAccessorGetter (Local<String> property, const AccessorInfo& info)
{
    printf("> Get: \n");
    Log(property);
    return v8::Object::New();
}

void CommonAccessorSetter (Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    printf("> Set: \n");
    Log(property);
}

Handle<Value> GlzClass::Properties(const Arguments& args) {
    HandleScope scope;

    if (args[0]->IsArray()) {
        return scope.Close(v8::Object::New());
    }

    //Local<String> privateKey = String::NewSymbol("private");
    Local<String> protectedKey = String::NewSymbol("protected");
    //Local<String> publicKey = String::NewSymbol("public");

    v8::Handle<v8::Object> classDefinition = args[0]->ToObject();
    //v8::Local<v8::Value> privateProp = classDefinition->Get(privateKey);
    v8::Local<v8::Value> protectedProp = classDefinition->Get(protectedKey);
    //v8::Local<v8::Value> publicProp = classDefinition->Get(publicKey);

    GlzClass* obj = ObjectWrap::Unwrap<GlzClass> (args.This());

    if(protectedProp->IsObject()) {
        v8::Handle<v8::Object> protectedDefinition = protectedProp->ToObject();
        v8::Handle<v8::Array> properties = protectedDefinition->GetPropertyNames();

        AccessorGetter getter = &CommonAccessorGetter;
        AccessorSetter setter = &CommonAccessorSetter;

        int length = properties->Length();
        for (int i = 0; i < length; i++) {
            v8::Local<v8::Value> propertyName = properties->Get(i);
            v8::Local<v8::Value> propertyValue = protectedDefinition->Get(propertyName);
            args.This()->SetAccessor(propertyName->ToString(), getter, setter);
        }

        return scope.Close(protectedDefinition);
    }

    return scope.Close(v8::Object::New());
}

Handle<Value> GlzClass::Extends(const Arguments& args) {
    HandleScope scope;

    //GlzClass* obj = ObjectWrap::Unwrap<GlzClass > (args.This());
    //obj->value_ += 1;

    return scope.Close(v8::Object::New());
}