#include <v8.h>
#include <node.h>

#include <cln/rational.h>
#include <cln/integer.h>
#include <cln/rational_io.h>
#include <cln/exception.h>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace v8;
using namespace cln;
using namespace std;

static const cl_RA ZERO = "0";
static const int FACTORIAL_MAX = 45000;
static const char * DIVIDE_BY_ZERO_ERROR = "Cannot divide by zero.";
static const char * BAD_INTEGER_SYNTAX = "Cannot parse integer from given notation.";
static const char * BAD_FRACTION_SYNTAX = "Cannot parse fraction from given notation.";

string cln_integer_to_string(cl_I integer) {
    ostringstream outs;
    fprint(outs, integer);
    return outs.str();
}


int matches_integer_pattern(const char * input) {
    int i = 0;
    int state = 0;
    char c = '\0';

    while((c = input[i++]) != '\0') {
        if (state == 0) {
            if (c == '-') {
                state = 1;
            } else if (isdigit(c)) {
                state = 2;
            } else {
                return 0;
            }
        } else if (state == 1) {
            if (isdigit(c)) {
                state = 2;
            } else {
                return 0;
            }
        } else if (state == 2) {
            if (isdigit(c)) {
                state = 2;
            } else {
                return 0;
            }
        }
    }
    return (state == 2) ? 1 : 0;
}

int matches_fraction_pattern(const char * input) {
    int i = 0;
    int state = 0;
    char c = '\0';

    while ((c = input[i++]) != '\0') {
        if (state == 0) {
            if (c == '-') {
                state = 1;
            } else if (isdigit(c)) {
                state = 2;
            } else {
                return 0;
            }
        } else if (state == 1) {
            if (isdigit(c)) {
                state = 2;
            } else {
                return 0;
            }
        } else if (state == 2) {
            if (isdigit(c)) {
                state = 2;
            } else if (c == '/') {
                state = 3;
            } else {
                return 0;
            }
        } else if (state == 3) {
            if (isdigit(c)) {
                state = 4;
            } else {
                return 0;
            }
        } else if (state == 4) {
            if (isdigit(c)) {
                state = 4;
            } else {
                return 0;
            }
        } // End state case statement.
    }
    return (state == 2 || state == 4) ? 1 : 0;
}

bool isHandleForRationalNumber(v8::Handle<v8::Object>);


class RationalNumber : node::ObjectWrap {
private :
    static Persistent<Function> constructor_;
    cl_RA fraction_;
public :
    static Persistent<FunctionTemplate> persistent_function_template;
    RationalNumber() {}
    ~RationalNumber() {
        fraction_ = ZERO; // Trigger cleanup of this object's fraction.
    }
    static Handle<Value> New(const Arguments& args) {
        HandleScope scope;
        RationalNumber * rationalnumber_instance = new RationalNumber();
        cl_I num(0), den(1);
        rationalnumber_instance->fraction_ = num / den;
        rationalnumber_instance->Wrap(args.This());
        if (!args[0]->IsUndefined()) {
            rationalnumber_instance->InitializeFromString(args);
        }
        return args.This();
    }
    static void Init(Handle<Object> target) {
        Local<FunctionTemplate> local_function_template = FunctionTemplate::New(New);
        RationalNumber::persistent_function_template = Persistent<FunctionTemplate>::New(local_function_template);
        RationalNumber::persistent_function_template->InstanceTemplate()->SetInternalFieldCount(1);
        RationalNumber::persistent_function_template->SetClassName(String::NewSymbol("RationalNumber"));

        // "Class members"
        RationalNumber::persistent_function_template->Set(String::NewSymbol("gcd"), FunctionTemplate::New(GCD)->GetFunction());
        RationalNumber::persistent_function_template->Set(String::NewSymbol("lcm"), FunctionTemplate::New(LCM)->GetFunction());

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
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("isEqualTo"), FunctionTemplate::New(IsEqualTo)->GetFunction());
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("isLessThan"), FunctionTemplate::New(IsLessThan)->GetFunction());
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("isGreaterThan"), FunctionTemplate::New(IsGreaterThan)->GetFunction());
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("isLessThanOrEqualTo"), FunctionTemplate::New(IsLessThanOrEqualTo)->GetFunction());
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("isGreaterThanOrEqualTo"), FunctionTemplate::New(IsGreaterThanOrEqualTo)->GetFunction());
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("factorial"), FunctionTemplate::New(Factorial)->GetFunction());
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("getFactorialMax"), FunctionTemplate::New(GetFactorialMax)->GetFunction());
        RationalNumber::persistent_function_template->PrototypeTemplate()->Set(String::NewSymbol("modulus"), FunctionTemplate::New(Modulus)->GetFunction());

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
        if (!matches_integer_pattern(*numerator_string)) {
            ThrowException(Exception::TypeError(String::New(BAD_INTEGER_SYNTAX)));
            return;
        }
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
        if (!matches_integer_pattern(*denominator_string)) {
            ThrowException(Exception::TypeError(String::New(BAD_INTEGER_SYNTAX)));
            return;
        }
        cl_I new_denominator = *denominator_string;
        if (new_denominator == 0) {
            ThrowException(Exception::TypeError(String::New(DIVIDE_BY_ZERO_ERROR)));
            return;
        }
        rationalnumber_instance->fraction_ = old_numerator / new_denominator;
    }

    static Handle<Value> Add(const Arguments& args) {
        HandleScope scope;
        Persistent<Object> sum = Persistent<Object>::New(
            RationalNumber::persistent_function_template->InstanceTemplate()->NewInstance()
        );

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
        Persistent<Object> difference = Persistent<Object>::New(
            RationalNumber::persistent_function_template->InstanceTemplate()->NewInstance()
        );
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
        Persistent<Object> product = Persistent<Object>::New(
            RationalNumber::persistent_function_template->InstanceTemplate()->NewInstance()
        );
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
        Persistent<Object> quotient = Persistent<Object>::New(
            RationalNumber::persistent_function_template->InstanceTemplate()->NewInstance()
        );

        RationalNumber * this_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * that_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        RationalNumber * new_rationalnumber_instance = new RationalNumber();
        cl_RA new_fraction;
        if (that_rationalnumber->fraction_ == 0) {
            ThrowException(Exception::TypeError(String::New(DIVIDE_BY_ZERO_ERROR)));
            new_rationalnumber_instance->fraction_ = new_fraction;
            quotient->SetInternalField(0, External::New(new_rationalnumber_instance));
            return scope.Close(quotient);
        }

        new_fraction = this_rationalnumber->fraction_ / that_rationalnumber->fraction_;
        new_rationalnumber_instance->fraction_ = new_fraction;
        quotient->SetInternalField(0, External::New(new_rationalnumber_instance));
        return scope.Close(quotient);
    }

    static Handle<Value> Power(const Arguments& args) {
        HandleScope scope;
        Persistent<Object> result_object = Persistent<Object>::New(
            RationalNumber::persistent_function_template->InstanceTemplate()->NewInstance()
        );

        RationalNumber * base = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * exponent = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        RationalNumber * new_rationalnumber_instance = new RationalNumber();
        cl_RA base_fraction = base->fraction_;
        cl_RA exponent_fraction = exponent->fraction_;
        cl_I exponent_numerator = cln::numerator(exponent_fraction);
        cl_I exponent_denominator = cln::denominator(exponent_fraction);
        cl_RA root_fraction, result_fraction;
        if (base_fraction == 0 && exponent_fraction < 0) { // Can't raise zero to negative power.
            ThrowException(Exception::TypeError(String::New(DIVIDE_BY_ZERO_ERROR)));
            new_rationalnumber_instance->fraction_ = result_fraction;
            result_object->SetInternalField(0, External::New(new_rationalnumber_instance));
            return scope.Close(result_object);
        }

        if (exponent_denominator == 1) { // Integer power.
            result_fraction = cln::expt(base_fraction, exponent_numerator);
            new_rationalnumber_instance->fraction_ = result_fraction;
            result_object->SetInternalField(0, External::New(new_rationalnumber_instance));
            return scope.Close(result_object);
        }
        if (cln::evenp(exponent_denominator)) { // E.g. x^(1/2)
            if (cln::rootp(base_fraction, exponent_denominator, &root_fraction)) {
                result_fraction = cln::expt( root_fraction, exponent_numerator);
                new_rationalnumber_instance->fraction_ = result_fraction;
                result_object->SetInternalField(0, External::New(new_rationalnumber_instance));
                return scope.Close(result_object);
            } else { // Imperfect even root.
                ThrowException(Exception::TypeError(String::New("Irrational number!")));
                new_rationalnumber_instance->fraction_ = result_fraction;
                result_object->SetInternalField(0, External::New(new_rationalnumber_instance));
                return scope.Close(result_object);
            }
        } else { // E.g. x^(1/3)
            cl_RA positive_base_fraction = cln::abs(base_fraction);
            cl_RA sign = ( cln::signum(base_fraction) < 0 ) ? -1 : 1;
            if (cln::rootp(positive_base_fraction, exponent_denominator, &root_fraction)) {
                result_fraction = sign * cln::expt(root_fraction, exponent_numerator);
                new_rationalnumber_instance->fraction_ = result_fraction;
                result_object->SetInternalField(0, External::New(new_rationalnumber_instance));
                return scope.Close(result_object);
            } else { // Imperfect odd root.
                ThrowException(Exception::TypeError(String::New("Irrational number!")));
                new_rationalnumber_instance->fraction_ = result_fraction;
                result_object->SetInternalField(0, External::New(new_rationalnumber_instance));
                return scope.Close(result_object);
            }
        }
    }

    static Handle<Value> InitializeFromString(const Arguments& args) {
        HandleScope scope;
        RationalNumber * self = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        v8::String::Utf8Value string_pointer(args[0]);
        if (!matches_fraction_pattern(*string_pointer)) {
            ThrowException(Exception::TypeError(String::New(BAD_FRACTION_SYNTAX)));
            return scope.Close(Undefined());
        }
        cl_RA new_fraction = *string_pointer;
        self->fraction_ = new_fraction;
        return scope.Close(Undefined());
    }

    static Handle<Value> IsEqualTo(const Arguments& args) {
        HandleScope scope;
        RationalNumber * self = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * other = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        cl_RA self_fraction = self->fraction_;
        cl_RA other_fraction = other->fraction_;
        if (self_fraction == other_fraction) {
            return scope.Close(True());
        } else {
            return scope.Close(False());
        }
    }

    static Handle<Value> IsLessThan(const Arguments& args) {
        HandleScope scope;
        RationalNumber * self = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * other = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        cl_RA self_fraction = self->fraction_;
        cl_RA other_fraction = other->fraction_;
        if (self_fraction < other_fraction) {
            return scope.Close(True());
        } else {
            return scope.Close(False());
        }
    }

    static Handle<Value> IsGreaterThan(const Arguments& args) {
        HandleScope scope;
        RationalNumber * self = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * other = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        cl_RA self_fraction = self->fraction_;
        cl_RA other_fraction = other->fraction_;
        if (self_fraction > other_fraction) {
            return scope.Close(True());
        } else {
            return scope.Close(False());
        }
    }

    static Handle<Value> IsLessThanOrEqualTo(const Arguments& args) {
        HandleScope scope;
        RationalNumber * self = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * other = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        cl_RA self_fraction = self->fraction_;
        cl_RA other_fraction = other->fraction_;
        if (self_fraction <= other_fraction) {
            return scope.Close(True());
        } else {
            return scope.Close(False());
        }
    }

    static Handle<Value> IsGreaterThanOrEqualTo(const Arguments& args) {
        HandleScope scope;
        RationalNumber * self = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * other = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        cl_RA self_fraction = self->fraction_;
        cl_RA other_fraction = other->fraction_;
        if (self_fraction >= other_fraction) {
            return scope.Close(True());
        } else {
            return scope.Close(False());
        }
    }

    static Handle<Value> Factorial(const Arguments& args) {
        HandleScope scope;
        Persistent<Object> result = Persistent<Object>::New(
            RationalNumber::persistent_function_template->InstanceTemplate()->NewInstance()
        );
        RationalNumber * new_rationalnumber_instance = new RationalNumber();
        RationalNumber * self = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        cl_RA self_fraction = self->fraction_;
        cl_RA new_fraction; // In case we need to throw an exception.
        if (cln::denominator(self_fraction) != 1) { // Not an integer.
            ThrowException(Exception::TypeError(String::New("Factorial only allowed for integers.")));

            new_rationalnumber_instance->fraction_ = new_fraction;
            result->SetInternalField(0, External::New(new_rationalnumber_instance));
            return scope.Close(result);
            
        }
        if (cln::numerator(self_fraction) < 0) { // Negative integer.
            ThrowException(Exception::TypeError(String::New("Factorial only allowed for positive numbers.")));
            new_rationalnumber_instance->fraction_ = new_fraction;
            result->SetInternalField(0, External::New(new_rationalnumber_instance));
            return scope.Close(result);
        }
        if (cln::numerator(self_fraction) > FACTORIAL_MAX) { // Too big to compute in under a second.
            ThrowException(Exception::TypeError(String::New("Cannot take factorial (number too big)")));
            new_rationalnumber_instance->fraction_ = new_fraction;
            result->SetInternalField(0, External::New(new_rationalnumber_instance));
            return scope.Close(result);
        }
        
        // Assert: The cl_I can be converted to an unsigned long int,
        // without throwing an exception.
        unsigned long c_integer = cl_I_to_ulong(numerator(self_fraction));

        new_rationalnumber_instance->fraction_ = cln::factorial(c_integer);
        result->SetInternalField(0, External::New(new_rationalnumber_instance));
        return scope.Close(result);
    
    }

    static Handle<Value> GetFactorialMax(const Arguments& args) {
        HandleScope scope;
        Persistent<Object> factorial_max = Persistent<Object>::New(
            RationalNumber::persistent_function_template->InstanceTemplate()->NewInstance()
        );
        RationalNumber * new_rationalnumber_instance = new RationalNumber();
        new_rationalnumber_instance->fraction_ = FACTORIAL_MAX;
        factorial_max->SetInternalField(0, External::New(new_rationalnumber_instance));
        return scope.Close(factorial_max);
    }

    static Handle<Value> Modulus(const Arguments& args) {
        HandleScope scope;
        Persistent<Object> remainder = Persistent<Object>::New(
            RationalNumber::persistent_function_template->InstanceTemplate()->NewInstance()
        );
        RationalNumber * new_rationalnumber_instance = new RationalNumber();
        cl_RA new_fraction;

        RationalNumber * this_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args.This());
        RationalNumber * that_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        cl_RA D = this_rationalnumber->fraction_;
        cl_RA d = that_rationalnumber->fraction_;
        if ( d == 0 ) {
            ThrowException(Exception::TypeError(String::New(DIVIDE_BY_ZERO_ERROR)));
            new_rationalnumber_instance->fraction_ = new_fraction;
            remainder->SetInternalField(0, External::New(new_rationalnumber_instance));
            return scope.Close(remainder);
        }

        new_fraction = D - d * cln::floor1(D / d);
        new_rationalnumber_instance->fraction_ = new_fraction;
        remainder->SetInternalField(0, External::New(new_rationalnumber_instance));
        return scope.Close(remainder);
        
    }

    static Handle<Value> GCD(const Arguments& args) {
        HandleScope scope;
        cl_RA new_fraction;
        Persistent<Object> result = Persistent<Object>::New(
            RationalNumber::persistent_function_template->InstanceTemplate()->NewInstance()
        );
        RationalNumber * new_rationalnumber_instance = new RationalNumber();
        if (!isHandleForRationalNumber(args[0]->ToObject()) ||
            !isHandleForRationalNumber(args[1]->ToObject())) {
            ThrowException(Exception::TypeError(String::New("GCD only works on rational number objects.")));
            new_rationalnumber_instance->fraction_ = new_fraction;
            result->SetInternalField(0, External::New(new_rationalnumber_instance));
            return scope.Close(result);
        }

        RationalNumber * first_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        RationalNumber * second_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args[1]->ToObject());
        cl_RA a = first_rationalnumber->fraction_;
        cl_RA b = second_rationalnumber->fraction_;

        if (cln::denominator(a) != 1 || cln::denominator(b) != 1) { // GCD requires integer arguments.
            ThrowException(Exception::TypeError(String::New("GCD only allowed for integers.")));

            new_rationalnumber_instance->fraction_ = new_fraction;
            result->SetInternalField(0, External::New(new_rationalnumber_instance));
            return scope.Close(result);
            
        }

        cl_I integer_a = cln::numerator(a);
        cl_I integer_b = cln::numerator(b);

        new_fraction = cln::gcd(integer_a, integer_b);
        new_rationalnumber_instance->fraction_ = new_fraction;
        result->SetInternalField(0, External::New(new_rationalnumber_instance));
        return scope.Close(result);
        
    }

    static Handle<Value> LCM(const Arguments& args) {
        HandleScope scope;
        cl_RA new_fraction;
        Persistent<Object> result = Persistent<Object>::New(
            RationalNumber::persistent_function_template->InstanceTemplate()->NewInstance()
        );
        RationalNumber * new_rationalnumber_instance = new RationalNumber();
        if (!isHandleForRationalNumber(args[0]->ToObject()) ||
            !isHandleForRationalNumber(args[1]->ToObject())) {
            ThrowException(Exception::TypeError(String::New("LCM only works on rational number objects.")));
            new_rationalnumber_instance->fraction_ = new_fraction;
            result->SetInternalField(0, External::New(new_rationalnumber_instance));
            return scope.Close(result);
        }

        RationalNumber * first_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args[0]->ToObject());
        RationalNumber * second_rationalnumber = node::ObjectWrap::Unwrap<RationalNumber>(args[1]->ToObject());
        cl_RA a = first_rationalnumber->fraction_;
        cl_RA b = second_rationalnumber->fraction_;


        if (cln::denominator(a) != 1 || cln::denominator(b) != 1) { // LCM requires integer arguments.
            ThrowException(Exception::TypeError(String::New("LCM only allowed for integers.")));

            new_rationalnumber_instance->fraction_ = new_fraction;
            result->SetInternalField(0, External::New(new_rationalnumber_instance));
            return scope.Close(result);
            
        }

        cl_I integer_a = cln::numerator(a);
        cl_I integer_b = cln::numerator(b);

        new_fraction = cln::lcm(integer_a, integer_b);
        new_rationalnumber_instance->fraction_ = new_fraction;
        result->SetInternalField(0, External::New(new_rationalnumber_instance));
        return scope.Close(result);
        
    }


};

bool isHandleForRationalNumber(v8::Handle<v8::Object> handle) {
    HandleScope scope;
    Local<v8::String> desiredClassName = v8::String::New("RationalNumber");
    if (handle->GetConstructorName()->Equals(desiredClassName)) {
        return true;
    }
    return false;
}

v8::Persistent<FunctionTemplate> RationalNumber::persistent_function_template;

v8::Persistent<Function> RationalNumber::constructor_;

extern "C" {
    static void init(Handle<Object> target) {
        RationalNumber::Init(target);
    }

    NODE_MODULE(rationalnumber, init);
}
