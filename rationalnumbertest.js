var rational = require('./build/Release/rationalnumber.node');
console.log("Inside rationalnumbertest, the result of the require command is:\n");
console.log(rational);
var RationalNumber = rational.RationalNumber;
console.log("The rational number constructor's prototype looks like:\n");
console.log(RationalNumber.prototype);
console.log("The add function looks like:\n", RationalNumber.prototype.add);
function testing() {
    var rationalInstance = new RationalNumber();
    console.log("The rationalInstance looks like:\n", rationalInstance);
    console.log("Is the rationalInstance instanceof RationalNumber?", (rationalInstance instanceof RationalNumber) ? 'yes' : 'no');


    rationalInstance.numerator = 1;
    console.log("After setting the numerator, the instance looks like:\n", rationalInstance);

    rationalInstance.denominator = 2;
    console.log("After setting the denominator, the instance looks like:\n", rationalInstance);
    console.log("And getting the new denominator yields:\n", rationalInstance.denominator);

    var rationalInstance2 = new RationalNumber();
    rationalInstance2.numerator = 3;
    rationalInstance2.denominator = 4;
    console.log("The second rational instance looks like:\n", rationalInstance2);

    var rationalInstance3 = rationalInstance.add(rationalInstance2);
    console.log("The sum is: ", rationalInstance3, "\n!!!1111\n");


    console.log("After setting the numerator of the result to 6, the result now looks like:\n");
    rationalInstance3.numerator = 6;
    console.log(rationalInstance3);

    var rationalInstance4 = rationalInstance.subtract(rationalInstance2);
    console.log("The difference between 1/2 and 3/4 is:\n", rationalInstance4);

    var rationalInstance5 = rationalInstance.multiply(rationalInstance2);

    console.log("The product of 1/2 and 3/4 is:\n", rationalInstance5);

    var rationalInstance6 = rationalInstance.divide(rationalInstance2);

    console.log("The quotient of 1/2 and 3/4 is:\n", rationalInstance6);

    var perfectSquare = new RationalNumber();

    perfectSquare.numerator = 4;
    perfectSquare.denominator = 9;
    
    var oneHalf = new RationalNumber();
    oneHalf.numerator = 1;
    oneHalf.denominator = 2;

    var perfectRoot = perfectSquare.power(oneHalf);
    console.log("The result of (4/9)^(1/2) is:\n", perfectRoot);

    try {
        var imperfectRoot = new RationalNumber();
        imperfectRoot.numerator = 2;
        imperfectRoot.denominator = 3;
        var result = imperfectRoot.power(oneHalf);
    } catch(error) {
        console.log("Got error object:\n", error.toString());
    }

    var perfectCube = new RationalNumber();
    perfectCube.initializeFromString("-27/8");
    var negativeOneThird = new RationalNumber();
    negativeOneThird.initializeFromString("-1/3");

    var perfectRoot = perfectCube.power(negativeOneThird);
    console.log("The result of (-27/8)^(-1/3) is:\n", perfectRoot.numerator + "/" + perfectRoot.denominator);

    var bigFraction = new RationalNumber();
    bigFraction.initializeFromString("12/13");
    console.log("The bigFraction's numerator is:\n", bigFraction.numerator);
    console.log("The bigFraction's denominator is:\n", bigFraction.denominator);

    console.log("About to construct a really, really big fraction.\n");
    bigFraction.initializeFromString("11111111111111111111111111111111111111111111111111/2222222222222222222222222222222222222222222222222222");
    console.log("The really, really big fraction's numerator is:\n", bigFraction.numerator);
    console.log("The really, really big fraction's denominator is:\n", bigFraction.denominator);

    var integerFraction = new RationalNumber();
    integerFraction.initializeFromString("12");
    console.log("The integer fraction's numerator is:\n", integerFraction.numerator);
    console.log("The integer fraction's denominator is:\n", integerFraction.denominator);


    bigFraction.initializeFromString("12/13");
    var zero = new RationalNumber();
    console.log("About to try dividing by zero.\n");
    try {
        var divideByZero = bigFraction.divide(zero);
        console.log("12/13 / 0 is:\n", divideByZero.numerator + "/" + divideByZero.denominator);
    } catch(error) {
        console.log("The result of dividing 12/13 by 0 got error:\n", error.toString());
    }


    var selfFraction = new RationalNumber();
    selfFraction.initializeFromString("12/13");
    var otherFraction = new RationalNumber();
    otherFraction.initializeFromString("12");
    console.log("The result of testing whether 12/13 is equal to 12 is:\n");
    console.log(selfFraction.isEqualTo(otherFraction));

    otherFraction.initializeFromString("24/26");
    console.log("The result of testing whether 12/13 is equal to 24/26 is:\n");
    console.log(selfFraction.isEqualTo(otherFraction));

    console.log("The result of testing whether 12/13 is less than 24/26 is:\n");
    console.log(selfFraction.isLessThan(otherFraction));

    otherFraction.initializeFromString("12");
    console.log("The result of testing whether 12 is greater than 12/13 is:\n");
    console.log(otherFraction.isGreaterThan(selfFraction));

    otherFraction.initializeFromString("24/26");
    console.log("The result of testing whether 12/13 is less than or equal to 24/26 is:\n");
    console.log(selfFraction.isLessThanOrEqualTo(otherFraction));

    otherFraction.initializeFromString("14/13");
    console.log("The result of testing whether 12/13 is greater than or equal to 14/13 is:\n");
    console.log(selfFraction.isGreaterThanOrEqualTo(otherFraction));

    var smallInteger = new RationalNumber();
    smallInteger.numerator = 3125;
    var factorialResult = smallInteger.factorial();
    console.log("The result of taking the factorial of 3125 is:\n", factorialResult.numerator, "/", factorialResult.denominator);

    smallInteger.initializeFromString("1/2");
    console.log("ABout to try and take the factorial of 1/2.\n");
    try {
        factorialResult = smallInteger.factorial();
    } catch(error) {
        console.log("Got error:\n", error.toString());
    }
    smallInteger.initializeFromString("-23");
    console.log("About to try and take the factorial of -23.\n");
    try {
        factorialResult = smallInteger.factorial();
    } catch(error) {
        console.log("Got error:\n", error.toString());
    }

    console.log("About to try and take the factorial of:.\n", RationalNumber.prototype.getFactorialMax().numerator);
    try {
        factorialResult = RationalNumber.prototype.getFactorialMax().factorial();
    } catch(error) {
        console.log("Got error:\n", error.toString());
    }
    console.log("The result is:\n", factorialResult.numerator);
    var oneMore = new RationalNumber();
    oneMore.initializeFromString("1");
    console.log("About to try and take the factorial of:\n", RationalNumber.prototype.getFactorialMax().add(oneMore).numerator);
    try {
        factorialResult = RationalNumber.prototype.getFactorialMax().add(oneMore).factorial();
    } catch(error) {
        console.log("Got error:\n", error.toString());
    }

    var five = new RationalNumber();
    five.initializeFromString("5");
    var three = new RationalNumber();
    three.initializeFromString("3");
    var r = five.modulus(three);
    console.log("The result of 5%3 is:\n", r.numerator + "/" + r.denominator);

    five.denominator = 2;
    try {
        five.modulus(three);
    } catch(error) {
        console.log("5/2 % 3Got error:\n", error.toString());
    }
    five.denominator = 1;
    three.denominator = 2;
    try {
        five.modulus(three);
    } catch(error) {
        console.log("5 % 3/2 Got error:\n", error.toString());
    }

    five.initializeFromString("-5");
    three.initializeFromString("3");
    r = five.modulus(three);
    console.log("The result of -5 % 3 is:\n", r.numerator + "/" + r.denominator);

    five.initializeFromString("5");
    three.initializeFromString("-3");
    r = five.modulus(three);
    console.log("The result of 5 % -3 is:\n", r.numerator + "/" + r.denominator);

    five.initializeFromString("-5");
    three.initializeFromString("-3");
    r = five.modulus(three);
    console.log("The result of -5 % -3 is:\n", r.numerator + "/" + r.denominator);

    five.initializeFromString("5");
    three.initializeFromString("3");
    r = three.modulus(five);
    console.log("The result of 3 % 5 is:\n", r.numerator + "/" + r.denominator);

    three.initializeFromString("0");
    try {
        r = five.modulus(three);
        console.log("The result of 5 % 0 is:\n", r.numerator + "/" + r.denominator);
    } catch(error) {
        console.log("5 % 0 resulted in error:\n", error.toString());
    }

    five.initializeFromString("5/3");
    three.initializeFromString("3/2");
    r = five.modulus(three);
    console.log("The result of 5/3 % 3/2 is:\n", r.numerator + "/" + r.denominator);

    var zero = new RationalNumber();
    var one = zero.power(zero);
    console.log("The result of 0^0 is:\n", one.numerator + "/" + one.denominator);
    
    var negativeOne = new RationalNumber();
    negativeOne.initializeFromString("-1");
    try {
        var inf = zero.power(negativeOne);
        console.log("Taking zero to the power of negative one gave result:\n", inf.numerator + "/" + inf.denominator);
    } catch(error) {
        console.log("Taking zero to the power of negative one resulted in error:\n", error.toString());
    }

    var negative2 = new RationalNumber();
    negative2.initializeFromString('-2');
    oneFourth = negative2.power(negative2);
    console.log("The result of (-2)^(-2) is:\n", oneFourth.numerator + '/' + oneFourth.denominator);
    

}

testing();


setInterval( function() {
    console.log("Waiting for garbage to be collected.");
}, 2000);
