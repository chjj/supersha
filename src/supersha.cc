/**
 * supersha - sha256 bindings to libsecp256k1
 * Copyright (c) 2016, Christopher Jeffrey (MIT License)
 */

#include <node.h>
#include <nan.h>

#include "hash_impl.h"

NAN_METHOD(sha256) {
  Nan::HandleScope scope;

  if (info.Length() < 1)
    return Nan::ThrowError("sha256() requires arguments.");

  v8::Local<v8::Object> buf = info[0].As<v8::Object>();

  if (!node::Buffer::HasInstance(buf))
    return Nan::ThrowTypeError("First argument must be a Buffer.");

  const unsigned char *data = (unsigned char *)node::Buffer::Data(buf);
  size_t len = node::Buffer::Length(buf);

  secp256k1_sha256_t sha;
  unsigned char output[32];

  secp256k1_sha256_initialize(&sha);
  secp256k1_sha256_write(&sha, data, len);
  secp256k1_sha256_finalize(&sha, &output[0]);

  info.GetReturnValue().Set(
    Nan::CopyBuffer((char *)&output[0], 32).ToLocalChecked());
}

NAN_METHOD(sha256hmac) {
  Nan::HandleScope scope;

  if (info.Length() < 2)
    return Nan::ThrowError("sha256hmac() requires arguments.");

  v8::Local<v8::Object> buf = info[0].As<v8::Object>();
  v8::Local<v8::Object> kbuf = info[1].As<v8::Object>();

  if (!node::Buffer::HasInstance(buf))
    return Nan::ThrowTypeError("First argument must be a Buffer.");

  if (!node::Buffer::HasInstance(kbuf))
    return Nan::ThrowTypeError("Second argument must be a Buffer.");

  const unsigned char *data = (unsigned char *)node::Buffer::Data(buf);
  size_t len = node::Buffer::Length(buf);

  const unsigned char *kdata = (unsigned char *)node::Buffer::Data(kbuf);
  size_t klen = node::Buffer::Length(kbuf);

  secp256k1_hmac_sha256_t sha;
  unsigned char output[32];

  secp256k1_hmac_sha256_initialize(&sha, kdata, klen);
  secp256k1_hmac_sha256_write(&sha, data, len);
  secp256k1_hmac_sha256_finalize(&sha, &output[0]);

  info.GetReturnValue().Set(
    Nan::CopyBuffer((char *)&output[0], 32).ToLocalChecked());
}

NAN_METHOD(hash256) {
  Nan::HandleScope scope;

  if (info.Length() < 1)
    return Nan::ThrowError("hash256() requires arguments.");

  v8::Local<v8::Object> buf = info[0].As<v8::Object>();

  if (!node::Buffer::HasInstance(buf))
    return Nan::ThrowTypeError("First argument must be a Buffer.");

  const unsigned char *data = (unsigned char *)node::Buffer::Data(buf);
  size_t len = node::Buffer::Length(buf);

  secp256k1_sha256_t sha;
  unsigned char output[32];

  secp256k1_sha256_initialize(&sha);
  secp256k1_sha256_write(&sha, data, len);
  secp256k1_sha256_finalize(&sha, &output[0]);

  secp256k1_sha256_initialize(&sha);
  secp256k1_sha256_write(&sha, output, 32);
  secp256k1_sha256_finalize(&sha, &output[0]);

  info.GetReturnValue().Set(
    Nan::CopyBuffer((char *)&output[0], 32).ToLocalChecked());
}

NAN_MODULE_INIT(Init) {
  Nan::Export(target, "sha256", sha256);
  Nan::Export(target, "sha256hmac", sha256hmac);
  Nan::Export(target, "hash256", hash256);
}

NODE_MODULE(supersha, Init)
