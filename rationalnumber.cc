#include <v8.h>
#include <node.h>

#include <cln/rational.h>
#include <cln/integer.h>
#include <cln/rational_io.h>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace v8;
using namespace cln;

class RationalNumber : node::ObjectWrap {
private :
    static Persistent<Function> constructor_;
    cl_RA fraction_;
public :
    static Persistent<FunctionTemplate> persistent_function_template;
    RationalNumber() {}
    ~RationalNumber() {
        fraction_ = NULL; // Hopefully triggers reclaiming of the cl_RA object's memory.
    }
    static Handle<Value> New(const Arguments& args) {
        HandleScope scope;
        RationalNumber * rationalnumber_instance = new RationalNumber();
        cl_I num(0), den(1);
        rationalnumber_instance->fraction_ = num / den;
        rationalnumber_instance->Wrap(args.This());
        return args.This();
    }
    static void Init(Handle<Object> target) {
        Local<FunctionTemplate> local_function_template = FunctionTemplate::New(New);
        RationalNumber::persistent_function_template = Persistent<FunctionTemplate>::New(local_function_template);
        RationalNumber::persistent_function_template->InstanceTemplate()->SetInternalFieldCount(1);
        RationalNumber::persistent_function_template->SetClassName(String::NewSymbol("RationalNumber"));

        // Instance. 
        RationalNumber::persistent_function_template->InstanceTemplate()->SetAccessor(String::New("numerator"), GetNumerator, SetNumerator);
        RationalNumber::persistent_function_template->InstanceTemplate()->SetAccessor(String::New("denominator"), GetDenominator, SetDenominator);

        // Prototype.
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("add"), FunctionTemplate::New(Add)->GetFunction());
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("subtract"), FunctionTemplate::New(Subtract)->GetFunction());
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("multiply"), FunctionTemplate::New(Multiply)->GetFunction());
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("divide"), FunctionTemplate::New(Divide)->GetFunction());

        constructor_ = Persistent<Function>::New(RationalNumber::persistent_function_template->GetFunction());

        target->Set(String::NewSymbol("RationalNumber"), RationalNumber::persistent_function_template->GetFunction());
    }

    static Handle<Value> GetNumerator(Local<String> property, const AccessorInfo& info) {
        RationalNumber * rationalnumber_instance = node::ObjectWrap::Unwrap<RationalNumber>(info.Holder());
        cl_I cl_I_numerator = cln::numerator(rationalnumber_instance->fraction_);
        return Integer::New(cl_I_to_int(cl_I_numerator));
    }

    static void SetNumerator(Local<String> property, Local<Value> value, const AccessorInfo& info) {
        RationalNumber * rationalnumber_instance = node::ObjectWrap::Unwrap<RationalNumber>(info.Holder());
        cl_I old_denominator = cln::denominator(rationalnumber_instance->fraction_);
        cl_I new_numerator = value->Int32Value();
        rationalnumber_instance->fraction_ = new_numerator / old_denominator;
    }

    static Handle<Value> GetDenominator(Local<String> property, const AccessorInfo& info) {
        RationalNumber * rationalnumber_instance = node::ObjectWrap::Unwrap<RationalNumber>(info.Holder());
        cl_I cl_I_denominator = cln::denominator(rationalnumber_instance->fraction_);
        return Integer::New(cl_I_to_int(cl_I_denominator));
    }

    static void SetDenominator(Local<String> property, Local<Value> value, const AccessorInfo& info) {
        RationalNumber * rationalnumber_instance = node::ObjectWrap::Unwrap<RationalNumber>(info.Holder());
        cl_I old_numerator = cln::numerator(rationalnumber_instance->fraction_);
        cl_I new_denominator = value->Int32Value();
        rationalnumber_instance->fraction_ = old_numerator / new_denominator;
    }

    static Handle<Value> Add(const Arguments& args) {
        HandleScope scope;
        Local<Object> sum = constructor_->NewInstance();
        RationalNumber * this_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * that_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        RationalNumber * new_rationalnumber_instance = new RationalNumber();
        cl_RA new_fraction = this_rationalnumber->fraction_ + that_rationalnumber->fraction_;
        new_rationalnumber_instance->fraction_ = new_fraction;
        sum->SetInternalField(0, External::New(new_rationalnumber_instance));
        return scope.Close(sum);
    }

    static Handle<Value> Subtract(const Arguments& args) {
        HandleScope scope;
        Local<Object> difference = constructor_->NewInstance();
        RationalNumber * this_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * that_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        RationalNumber * new_rationalnumber_instance = new RationalNumber();
        cl_RA new_fraction = this_rationalnumber->fraction_ - that_rationalnumber->fraction_;
        new_rationalnumber_instance->fraction_ = new_fraction;
        difference->SetInternalField(0, External::New(new_rationalnumber_instance));
        return scope.Close(difference);
    }

    static Handle<Value> Multiply(const Arguments& args) {
        HandleScope scope;
        Local<Object> product = constructor_->NewInstance();
        RationalNumber * this_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * that_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        RationalNumber * new_rationalnumber_instance = new RationalNumber();
        cl_RA new_fraction = this_rationalnumber->fraction_ * that_rationalnumber->fraction_;
        new_rationalnumber_instance->fraction_ = new_fraction;
        product->SetInternalField(0, External::New(new_rationalnumber_instance));
        return scope.Close(product);
    }

    static Handle<Value> Divide(const Arguments& args) {
        HandleScope scope;
        Local<Object> quotient = constructor_->NewInstance();
        RationalNumber * this_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * that_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        RationalNumber * new_rationalnumber_instance = new RationalNumber();
        cl_RA new_fraction = this_rationalnumber->fraction_ / that_rationalnumber->fraction_;
        new_rationalnumber_instance->fraction_ = new_fraction;
        quotient->SetInternalField(0, External::New(new_rationalnumber_instance));
        return scope.Close(quotient);
    }




};

v8::Persistent<FunctionTemplate> RationalNumber::persistent_function_template;

v8::Persistent<Function> RationalNumber::constructor_;

extern "C" {
    static void init(Handle<Object> target) {
        RationalNumber::Init(target);
    }

    NODE_MODULE(rationalnumber, init);
}
