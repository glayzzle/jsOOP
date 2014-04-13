#include <node.h>
#include "glzclass.h"

using namespace v8;

Persistent<Function> GlzClass::constructor;

GlzClass::GlzClass(double value) : value_(value) {
}

GlzClass::~GlzClass() {
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

    // Set a prototype method
    //NODE_SET_PROTOTYPE_METHOD(tpl, "getName", Extends);

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
    // Prevent recursion with SetNamedPropertyHandler
    printf("> Get: \n");
    Log(property);
    return info.This()->Get(property);
}

void CommonAccessorSetter (Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    printf("> Set: \n");
    Log(property);
    //GlzClass* obj = GlzClass::Unwrap<GlzClass> (info.Holder());

    // ForceSet = Bypass AccessorSetter handling
    info.This()->ForceSet(property, value); // try info.Holder() ???
}

Handle<Value> GlzClass::Properties(const Arguments& args) {
    HandleScope scope;

    if (args[0]->IsArray()) {
        return scope.Close(v8::Object::New());
    }

    //Local<String> privateKey = String::NewSymbol("private");
    //Local<String> protectedKey = String::NewSymbol("protected");
    //Local<String> publicKey = String::NewSymbol("public");

    v8::Handle<v8::Object> classDefinition = args[0]->ToObject();

    if(classDefinition->IsObject()) {
        AccessorGetter getter = &CommonAccessorGetter;
        AccessorSetter setter = &CommonAccessorSetter;
        v8::Handle<v8::Array> propScopes = classDefinition->GetPropertyNames();
        int scopesLen = propScopes->Length();

        // Iterate object definition (private, protected, public)
        for (int i = 0; i < scopesLen; i++) {
            v8::Local<v8::Value> scopeKey = propScopes->Get(i);
            v8::Local<v8::Value> scopeValue = classDefinition->Get(scopeKey);
            v8::Handle<v8::Object> scopeDefinition = scopeValue->ToObject();
            v8::Handle<v8::Array> scopeProps = scopeDefinition->GetPropertyNames();

            int scopeDefinitionLen = scopeProps->Length();

            // Iterate each scope
            for (int i = 0; i < scopeDefinitionLen; i++) {
                v8::Local<v8::Value> propertyName = scopeProps->Get(i);
                //v8::Local<v8::Value> propertyValue = protectedDefinition->Get(propertyName);

                // SetNamedPropertyHandler ????
                //args.This()->SetAccessor(propertyName->ToString(), getter, setter);
                args.This()->SetAccessor(propertyName->ToString(), 0, setter);
            }
        }
    //GlzClass* obj = ObjectWrap::Unwrap<GlzClass> (args.This());
        return scope.Close(classDefinition);
    }
    return scope.Close(v8::Object::New());
}

Handle<Value> GlzClass::Extends(const Arguments& args) {
    HandleScope scope;

    //GlzClass* obj = ObjectWrap::Unwrap<GlzClass > (args.Holder());
    //obj->value_ += 1;

    return scope.Close(v8::Object::New());
}