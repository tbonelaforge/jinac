#include <v8.h>
#include <node.h>

using namespace v8;

int gcd(int a, int b) {
    int c = a % b;
    while(c != 0) {
        a = b;
        b = c;
        c = a % b;
    }
    return b;
}



class RationalNumber : node::ObjectWrap {
private :
    int numerator_;
    int denominator_;
    static Persistent<Function> constructor_;
    void _Reduce() {
        int divisor = gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }
public :
    static Persistent<FunctionTemplate> persistent_function_template;
    RationalNumber() {}
    ~RationalNumber() {}
    static Handle<Value> New(const Arguments& args) {
        HandleScope scope;
        RationalNumber * rationalnumber_instance = new RationalNumber();
        rationalnumber_instance->numerator_ = 0;
        rationalnumber_instance->denominator_ = 1;
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

        constructor_ = Persistent<Function>::New(RationalNumber::persistent_function_template->GetFunction());

        target->Set(String::NewSymbol("RationalNumber"), RationalNumber::persistent_function_template->GetFunction());
    }

    static Handle<Value> GetNumerator(Local<String> property, const AccessorInfo& info) {
        RationalNumber * rationalnumber_instance = node::ObjectWrap::Unwrap<RationalNumber>(info.Holder());
        return Integer::New(rationalnumber_instance->numerator_);
    }

    static void SetNumerator(Local<String> property, Local<Value> value, const AccessorInfo& info) {
        RationalNumber * rationalnumber_instance = node::ObjectWrap::Unwrap<RationalNumber>(info.Holder());
            rationalnumber_instance->numerator_ = value->Int32Value();
    }

    static Handle<Value> GetDenominator(Local<String> property, const AccessorInfo& info) {
        RationalNumber * rationalnumber_instance = node::ObjectWrap::Unwrap<RationalNumber>(info.Holder());
        return Integer::New(rationalnumber_instance->denominator_);
    }

    static void SetDenominator(Local<String> property, Local<Value> value, const AccessorInfo& info) {
        RationalNumber * rationalnumber_instance = node::ObjectWrap::Unwrap<RationalNumber>(info.Holder());
            rationalnumber_instance->denominator_ = value->Int32Value();
    }

    static Handle<Value> Add(const Arguments& args) {
        HandleScope scope;
        Local<Object> sum = constructor_->NewInstance();
        RationalNumber * this_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * that_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        RationalNumber * new_rationalnumber_instance = new RationalNumber();
        new_rationalnumber_instance->denominator_ = this_rationalnumber->denominator_ * that_rationalnumber->denominator_;
        int new_this_numerator = this_rationalnumber->numerator_ * that_rationalnumber->denominator_;
        int new_that_numerator = that_rationalnumber->numerator_ * this_rationalnumber->denominator_;
        new_rationalnumber_instance->numerator_ = new_this_numerator + new_that_numerator;
        new_rationalnumber_instance->_Reduce();
        sum->SetInternalField(0, External::New(new_rationalnumber_instance));
        return scope.Close(sum);
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
