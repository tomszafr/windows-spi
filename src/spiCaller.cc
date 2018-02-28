#include <node.h>
#include <nan.h>
#include <windows.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#pragma comment(lib, "user32.lib")

using v8::Isolate;
using v8::Local;
using v8::Array;
using v8::Object;
using v8::String;
using v8::Value;

#define RETURN_BOOL 0
#define RETURN_INT 1
#define RETURN_ARRAY 2

void SPISet(const Nan::FunctionCallbackInfo<Value> &info)
{
  Isolate *isolate = info.GetIsolate();
  auto resolver = v8::Promise::Resolver::New(isolate);
  info.GetReturnValue().Set(resolver->GetPromise());
  BOOL fResult;
  void *ptr;

  if (!info[0]->IsNumber() || info[0]->IntegerValue() < 0)
  {
    Nan::ThrowTypeError("First argument must be a positive number referencing the uiAction.");
    return;
  }

  UINT action = info[0]->Uint32Value();

  if (info[1]->IsNumber())
  {
    int numberValue = info[1]->Uint32Value();
    ptr = &numberValue;
    PUINT_PTR intPtr = static_cast<PUINT_PTR>(ptr);
    fResult = SystemParametersInfo(action,
                                   0,
                                   (LPVOID)*intPtr,
                                   SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
  }
  else if (info[1]->IsArray())
  {
    Local<Array> arrayValue = Local<Array>::Cast(info[1]);
    std::vector<int> valuesVector;

    for (unsigned int i = 0; i < arrayValue->Length(); i++)
    {
      valuesVector.push_back(arrayValue->Get(i)->Uint32Value());
    }

    ptr = &valuesVector;
    PUINT_PTR arrayPtr = static_cast<PUINT_PTR>(ptr);
    fResult = SystemParametersInfo(action,
                                   0,
                                   (LPVOID)*arrayPtr,
                                   SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
  }
  else
  {
    Nan::ThrowTypeError("Unsupported 2nd argument type.");
    return;
  }

  if (fResult)
  {
    resolver->Resolve(Nan::New("Success.").ToLocalChecked());
  }
  else
  {
    resolver->Reject(Nan::New("Failed.").ToLocalChecked());
  }
}

void SPIGet(const Nan::FunctionCallbackInfo<Value> &info)
{
  Isolate *isolate = info.GetIsolate();
  auto resolver = v8::Promise::Resolver::New(isolate);
  info.GetReturnValue().Set(resolver->GetPromise());
  BOOL fResult;
  if (!info[0]->IsNumber() || info[0]->IntegerValue() < 0)
  {
    Nan::ThrowTypeError("First argument must be a positive number referencing the uiAction.");
    return;
  }

  UINT action = info[0]->Uint32Value();

  if (!info[1]->IsNumber())
  {
    Nan::ThrowTypeError("Second argument must be an integer specyfing the return type.");
    return;
  }

  int returnType = info[1]->Uint32Value();

  switch (returnType)
  {
  case RETURN_BOOL:
    bool returnBoolValue;
    fResult = SystemParametersInfo(action,
                                   0,
                                   &returnBoolValue,
                                   0);
    if (fResult)
    {
      resolver->Resolve(Nan::New(returnBoolValue));
    }
    else
    {
      resolver->Reject(Nan::New("Failed.").ToLocalChecked());
    }
    break;
  case RETURN_ARRAY:
    int returnArrayValue[3];
    fResult = SystemParametersInfo(action,
                                   0,
                                   &returnArrayValue,
                                   0);
    if (fResult)
    {
      Local<Array> resultsArray = Nan::New<v8::Array>(3);
      for (unsigned i = 0; i < 3; i++)
      {
        resultsArray->Set(Nan::New(i), Nan::New(returnArrayValue[i]));
      }
      resolver->Resolve(resultsArray);
    }
    else
    {
      resolver->Reject(Nan::New("Failed.").ToLocalChecked());
    }
    break;
  case RETURN_INT:
    int returnIntValue;
    fResult = SystemParametersInfo(action,
                                   0,
                                   &returnIntValue,
                                   0);
    if (fResult)
    {
      resolver->Resolve(Nan::New(returnIntValue));
    }
    else
    {
      resolver->Reject(Nan::New("Failed.").ToLocalChecked());
    }
    break;
  }
}

void Initialize(Local<v8::Object> exports)
{
  Nan::SetMethod(exports, "spiSet", SPISet);
  Nan::SetMethod(exports, "spiGet", SPIGet);
}

NODE_MODULE(spiCaller, Initialize)