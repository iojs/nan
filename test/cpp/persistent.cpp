/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2015 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include <nan.h>
#include <cstring>  // memset()

static v8::Persistent<v8::String> persistentTest1;

NAN_METHOD(Save1) {
  NanAssignPersistent(persistentTest1, info[0].As<v8::String>());
  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(Get1) {
  info.GetReturnValue().Set(NanNew(persistentTest1));
}

NAN_METHOD(Dispose1) {
  NanDisposePersistent(persistentTest1);
  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(ToPersistentAndBackAgain) {
  v8::Persistent<v8::Object> persistent;
  NanAssignPersistent(persistent, info[0].As<v8::Object>());
  v8::Local<v8::Object> object = NanNew(persistent);
  NanDisposePersistent(persistent);
  memset(&persistent, -1, sizeof(persistent));  // Clobber it good.
  info.GetReturnValue().Set(object);
}

NAN_METHOD(PersistentToPersistent) {
  v8::Persistent<v8::String> persistent;
  NanAssignPersistent(persistent, info[0].As<v8::String>());
  NanAssignPersistent(persistentTest1, persistent);
  NanDisposePersistent(persistent);
  NanDisposePersistent(persistentTest1);
  info.GetReturnValue().SetUndefined();
}

void Init (v8::Handle<v8::Object> target) {
  target->Set(
      NanNew<v8::String>("save1")
    , NanNew<v8::FunctionTemplate>(Save1)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("get1")
    , NanNew<v8::FunctionTemplate>(Get1)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("dispose1")
    , NanNew<v8::FunctionTemplate>(Dispose1)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("toPersistentAndBackAgain")
    , NanNew<v8::FunctionTemplate>(ToPersistentAndBackAgain)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("persistentToPersistent")
    , NanNew<v8::FunctionTemplate>(PersistentToPersistent)->GetFunction()
  );
}

NODE_MODULE(persistent, Init)
