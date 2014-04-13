#ifndef GLZCLASS_H
#define GLZCLASS_H

#include <string>
#include <node.h>

class GlzClass : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  std::string title;

 private:
  explicit GlzClass(double value = 0);
  ~GlzClass();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> Properties(const v8::Arguments& args);
  static v8::Handle<v8::Value> Extends(const v8::Arguments& args);
  static v8::Persistent<v8::Function> constructor;

  double value_;
};

#endif
