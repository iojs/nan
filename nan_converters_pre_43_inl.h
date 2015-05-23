/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2015 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#ifndef NAN_CONVERTERS_PRE_43_INL_H_
#define NAN_CONVERTERS_PRE_43_INL_H_

#define X(TYPE)                                                                \
Nan::imp::ToFactory<v8::TYPE>::return_t                                        \
Nan::imp::ToFactory<v8::TYPE>::convert(v8::Handle<v8::Value> val) {            \
  return NanMaybeLocal<v8::TYPE>(val->To ## TYPE());                           \
}

X(Boolean)
X(Number)
X(String)
X(Object)
X(Integer)
X(Uint32)
X(Int32)

#undef X

#define X(TYPE, NAME)                                                          \
Nan::imp::ToFactory<TYPE>::return_t                                            \
Nan::imp::ToFactory<TYPE>::convert(v8::Handle<v8::Value> val) {                \
  return NanJust<TYPE>(val->NAME ##Value());                                   \
}

X(bool, Boolean)
X(double, Number)
X(int64_t, Integer)
X(uint32_t, Uint32)
X(int32_t, Int32)

#undef X

#endif  // NAN_CONVERTERS_PRE_43_INL_H_
