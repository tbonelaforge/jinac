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

}

testing();


setInterval( function() {
    console.log("Waiting for garbage to be collected.");
}, 2000);
