#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <stdint.h>
#include "nan.h"

extern "C" {
    #include "x16rv2.h"

}


#define THROW_ERROR_EXCEPTION(x) Nan::ThrowError(x)
#define THROW_ERROR_EXCEPTION_WITH_STATUS_CODE(x, y) NanThrowError(x, y)

using namespace node;
using namespace v8;

NAN_METHOD(x16rv2) {

    if (info.Length() < 1)
        return THROW_ERROR_EXCEPTION("You must provide one argument.");

    Local<Object> target = Nan::To<Object>(info[0]).ToLocalChecked();

    if(!Buffer::HasInstance(target))
        return THROW_ERROR_EXCEPTION("Argument should be a buffer object.");

    char * input = Buffer::Data(target);
    char *output = (char*) malloc(sizeof(char) * 32);

    // uint32_t input_len = Buffer::Length(target);

    x16rv2_hash(input, output);

    info.GetReturnValue().Set(Nan::NewBuffer(output, 32).ToLocalChecked());
}

NAN_MODULE_INIT(init) {
    Nan::Set(target, Nan::New("x16rv2").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(x16rv2)).ToLocalChecked());
}

NODE_MODULE(nodex16rv2, init)
