var rational = require('./build/Release/rationalnumber.node');
console.log("Inside rationalnumbertest, the result of the require command is:\n");
console.log(rational);
var RationalNumber = rational.RationalNumber;
//var rationalInstance = new rational.RationalNumber();
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