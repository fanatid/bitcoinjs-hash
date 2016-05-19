#include <node.h>
#include <nan.h>

#include "ripemd160.h"
#include "sha1.h"
#include "sha256.h"

#define CHECK_TYPE_BUFFER(value) {                                             \
  if (!node::Buffer::HasInstance(value)) {                                     \
    return Nan::ThrowTypeError("Expected input as Buffer");                    \
  }                                                                            \
}

NAN_METHOD(ripemd160) {
  Nan::HandleScope scope;

  v8::Local<v8::Object> input = info[0].As<v8::Object>();
  CHECK_TYPE_BUFFER(input);

  v8::Local<v8::Object> output = Nan::NewBuffer(20).ToLocalChecked();
  ripemd160(
    (unsigned char*) node::Buffer::Data(output),
    (const unsigned char*) node::Buffer::Data(input),
    node::Buffer::Length(input));

  info.GetReturnValue().Set(output);
}

NAN_METHOD(sha1) {
  Nan::HandleScope scope;

  v8::Local<v8::Object> input = info[0].As<v8::Object>();
  CHECK_TYPE_BUFFER(input);

  v8::Local<v8::Object> output = Nan::NewBuffer(20).ToLocalChecked();
  sha1(
    (unsigned char*) node::Buffer::Data(output),
    (const unsigned char*) node::Buffer::Data(input),
    node::Buffer::Length(input));

  info.GetReturnValue().Set(output);
}

NAN_METHOD(sha256) {
  Nan::HandleScope scope;

  v8::Local<v8::Object> input = info[0].As<v8::Object>();
  CHECK_TYPE_BUFFER(input);

  v8::Local<v8::Object> output = Nan::NewBuffer(32).ToLocalChecked();
  sha256(
    (unsigned char*) node::Buffer::Data(output),
    (const unsigned char*) node::Buffer::Data(input),
    node::Buffer::Length(input));

  info.GetReturnValue().Set(output);
}

NAN_METHOD(hash160) {
  Nan::HandleScope scope;

  v8::Local<v8::Object> input = info[0].As<v8::Object>();
  CHECK_TYPE_BUFFER(input);

  unsigned char tmp[32];
  sha256(
    (unsigned char*) tmp,
    (const unsigned char*) node::Buffer::Data(input),
    node::Buffer::Length(input));

  v8::Local<v8::Object> output = Nan::NewBuffer(20).ToLocalChecked();
  ripemd160(
    (unsigned char*) node::Buffer::Data(output),
    (const unsigned char*) tmp,
    32);

  info.GetReturnValue().Set(output);
}

NAN_METHOD(hash256) {
  Nan::HandleScope scope;

  v8::Local<v8::Object> input = info[0].As<v8::Object>();
  CHECK_TYPE_BUFFER(input);

  v8::Local<v8::Object> output = Nan::NewBuffer(32).ToLocalChecked();
  sha256(
    (unsigned char*) node::Buffer::Data(output),
    (const unsigned char*) node::Buffer::Data(input),
    node::Buffer::Length(input));
  sha256(
    (unsigned char*) node::Buffer::Data(output),
    (const unsigned char*) node::Buffer::Data(output),
    32);

  info.GetReturnValue().Set(output);
}

NAN_MODULE_INIT(Init) {
  Nan::Export(target, "ripemd160", ripemd160);
  Nan::Export(target, "sha1", sha1);
  Nan::Export(target, "sha256", sha256);
  Nan::Export(target, "hash160", hash160);
  Nan::Export(target, "hash256", hash256);
}

NODE_MODULE(bitcoinjsHash, Init)
