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
using namespace std;

static const cl_RA zero = "0";

string cln_integer_to_string(cl_I integer) {
    ostringstream outs;
    fprint(outs, integer);
    return outs.str();
}

class RationalNumber : node::ObjectWrap {
private :
    static Persistent<Function> constructor_;
    cl_RA fraction_;
public :
    static Persistent<FunctionTemplate> persistent_function_template;
    RationalNumber() {}
    ~RationalNumber() {
        fraction_ = zero; // Trigger cleanup of this object's fraction.
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
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("power"), FunctionTemplate::New(Power)->GetFunction());
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("initializeFromString"), FunctionTemplate::New(InitializeFromString)->GetFunction());

        constructor_ = Persistent<Function>::New(RationalNumber::persistent_function_template->GetFunction());

        target->Set(String::NewSymbol("RationalNumber"), RationalNumber::persistent_function_template->GetFunction());
    }

    static Handle<Value> GetNumerator(Local<String> property, const AccessorInfo& info) {
        HandleScope scope;
        RationalNumber * rationalnumber_instance = node::ObjectWrap::Unwrap<RationalNumber>(info.Holder());
        cl_I cl_I_numerator = cln::numerator(rationalnumber_instance->fraction_);
        return scope.Close(String::New(cln_integer_to_string(cl_I_numerator).c_str()));
    }

    static void SetNumerator(Local<String> property, Local<Value> value, const AccessorInfo& info) {
        RationalNumber * rationalnumber_instance = node::ObjectWrap::Unwrap<RationalNumber>(info.Holder());
        cl_I old_denominator = cln::denominator(rationalnumber_instance->fraction_);
        v8::String::Utf8Value numerator_string(value);
        cl_I new_numerator = *numerator_string;
        rationalnumber_instance->fraction_ = new_numerator / old_denominator;
    }

    static Handle<Value> GetDenominator(Local<String> property, const AccessorInfo& info) {
        HandleScope scope;
        RationalNumber * rationalnumber_instance = node::ObjectWrap::Unwrap<RationalNumber>(info.Holder());
        cl_I cl_I_denominator = cln::denominator(rationalnumber_instance->fraction_);
        return scope.Close(String::New(cln_integer_to_string(cl_I_denominator).c_str()));
    }

    static void SetDenominator(Local<String> property, Local<Value> value, const AccessorInfo& info) {
        RationalNumber * rationalnumber_instance = node::ObjectWrap::Unwrap<RationalNumber>(info.Holder());
        cl_I old_numerator = cln::numerator(rationalnumber_instance->fraction_);
        v8::String::Utf8Value denominator_string(value);
        cl_I new_denominator = *denominator_string;
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

    static Handle<Value> Power(const Arguments& args) {
        HandleScope scope;
        Local<Object> result_object = constructor_->NewInstance();
        RationalNumber * base = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * exponent = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        RationalNumber * new_rationalnumber_instance = new RationalNumber();
        cl_RA base_fraction = base->fraction_;
        cl_RA exponent_fraction = exponent->fraction_;
        cl_I exponent_numerator = cln::numerator(exponent_fraction);
        cl_I exponent_denominator = cln::denominator(exponent_fraction);
        cl_RA root_fraction, result_fraction;
        if (cln::rootp( base_fraction, exponent_denominator, &root_fraction)) {
            result_fraction = cln::expt( root_fraction, exponent_numerator);
            new_rationalnumber_instance->fraction_ = result_fraction;
            result_object->SetInternalField(0, External::New(new_rationalnumber_instance));
            return scope.Close(result_object);
        } else {
            ThrowException(Exception::TypeError(String::New("Irrational number!")));
            return scope.Close(Undefined());
        }
    }

    static Handle<Value> InitializeFromString(const Arguments& args) {
        HandleScope scope;
        RationalNumber * self = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        v8::String::Utf8Value string_pointer(args[0]);
        cl_RA new_fraction = *string_pointer;
        self->fraction_ = new_fraction;
        return scope.Close(Undefined());
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
