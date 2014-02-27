#Jinac Documentation

***
Jinac is an addon to node.js which enables arbitrarily precise rational numbers, and ways of manipulating them without losing precision.

	var RationalNumber = require('jinac').RationalNumber;
	var oneHalf = new RationalNumber('1/2');
	var twoThirds = new RationalNumber('2/3');
	var result = oneHalf.add(twoThirds);
	console.log("The result is:");
	console.log(result.numerator + '/' + result.denominator); // '7/6'





This project was started in response to the growing need for high-performance grading of mathematics in web-based educational software.  The RationalNumber class provided by jinac can handle really, really big numbers, and can perform operations on them very quickly.  

For example, this module can perform 

	factorial(45000)
	
 
 in about a quarter of a second.


Dependencies:

CLN - Class Library for Numbers: You must have this package installed on your system in order to use jinac.

http://www.ginac.de/CLN/
***

##Installation

### linux systems
1. sudo apt-get install libcln-dev
2. npm install jinac

### Mac OS X systems
1. sudo brew install cln
2. npm install jinac

##Examples
###Constructing
* Constructing a new rational number:

		var RationalNumber = require('jinac').RationalNumber;
		var rat = new RationalNumber();
		console.log("The new rational number looks like:");
		console.log(rat); // { denominator: '1', numerator: '0' }

* Constructing a new rational number from a string:

		var RationalNumber = require('jinac').RationalNumber;
		var rat1 = new RationalNumber('-3/4');
		var rat2 = new RationalNumber('5');
		var rat3 = new RationalNumber('0.5'); // Throws exception
		var rat4 = new RationalNumber('3/-4'); // Throws exception
		
* Auto-simplification:

		var RationalNumber = require('jinac').RationalNumber;
		var rat = new RationalNumber('8/10');
		console.log("The simplified rational number looks like:");
		console.log(rat); // { denominator : '5', numerator : '4' }
		
###Instance Methods
		
####Getters
* numerator

		var RationalNumber = require('jinac').RationalNumber;
		var rat = new RationalNumber('111222333444555666777888999/2');
		console.log("The numerator is:");
		console.log(rat.numerator); // '111222333444555666777888999'

* denominator

		var RationalNumber = require('jinac').RationalNumber;
		var rat = new RationalNumber('2/111222333444555666777888999');
		console.log("The denomiator is:");
		console.log(rat.denominator); // '111222333444555666777888999'
		
####Setters
* numerator

		var RationalNumber = require('jinac').RationalNumber;
		var rat = new RationalNumber('1/2');
		rat.numerator = '111222333444555666777888999';
		console.log("After setting the numerator, the rational number is:");
		console.log(rat); // { denominator : '2', numerator : '111222333444555666777888999' } 
		
* denominator

		var RationalNumber = require('jinac').RationalNumber;
		var rat = new RationalNumber('1/2');
		rat.denominator = '111222333444555666777888999';
		console.log("After setting the denominator, the rational number is:");
		console.log(rat); // { denominator : '111222333444555666777888999', numerator : '1' }  
		


####Binary Operations
* add
	
		var RationalNumber = require('jinac').RationalNumber;
		var oneHalf = new RationalNumber('1/2');
		var twoThirds = new RationalNumber('2/3');
		var result = oneHalf.add(twoThirds);
		console.log("The result is:");
		console.log(result.numerator + '/' + result.denominator); // '7/6'

* subtract

		var RationalNumber = require('jinac').RationalNumber;
		var oneHalf = new RationalNumber('1/2');
		var twoThirds = new RationalNumber('2/3');
		var result = oneHalf.subtract(twoThirds);
		console.log("The result is:");
		console.log(result.numerator + '/' + result.denominator); // '-1/6'
		
* multiply

		var RationalNumber = require('jinac').RationalNumber;
		var oneHalf = new RationalNumber('1/2');
		var twoThirds = new RationalNumber('2/3');
		var result = oneHalf.multiply(twoThirds);
		console.log("The result is:");
		console.log(result.numerator + '/' + result.denominator); // '1/3'
		
* divide

		var RationalNumber = require('jinac').RationalNumber;
		var oneHalf = new RationalNumber('1/2');
		var twoThirds = new RationalNumber('2/3');
		var result = oneHalf.divide(twoThirds);
		console.log("The result is:");
		console.log(result.numerator + '/' + result.denominator); // '3/4'
		
* power

		var RationalNumber = require('jinac').RationalNumber;
		var oneSixteenth = new RationalNumber('1/16');
		var oneHalf = new RationalNumber('1/2');
		var result = oneSixteenth.power(oneHalf);
		console.log("The result is:");
		console.log(result.numerator + '/' + result.denominator); // '1/4'
		
* modulus

		var RationalNumber = require('jinac').RationalNumber;
		var five = new RationalNumber('5');
		var three = new RationalNumber('3');
		var result = five.modulus(three);
		console.log("The result is:");
		console.log(result.numerator + '/' + result.denominator); // '2/1'


####Unary Operations

* factorial

		var RationalNumber = require('jinac').RationalNumber;
		var five = new RationalNumber('5');
		var result = five.factorial();
		console.log("The result is:");
		console.log(result.numerator + '/' + result.denominator); // '120/1'

* floor

		var RationalNumber = require('jinac').RationalNumber;
		var sevenThirds = new RationalNumber('7/3'); // Approximately 2.333...                     
		var result = sevenThirds.floor();
		console.log("The result is:");
		console.log(result.numerator + '/' + result.denominator); // '2/1'


####Comparisons
* isLessThan
* isLessThanOrEqualTo
* isEqualTo
* isGreaterThanOrEqualTo
* isGreaterThan

		var RationalNumber = require('jinac').RationalNumber;
		var three = new	RationalNumber('3/1');
		var nineThirds = new RationalNumber('9/3');
		
		console.log("'Three is less than nine thirds' is:");
		console.log(three.isLessThan(nineThirds)); // false                                        
		
		console.log("'Three is less than or equal to nine thirds' is:");
		console.log(three.isLessThanOrEqualTo(nineThirds)); // true                                
		
		console.log("'Three is equal to  nine thirds' is:");
		console.log(three.isEqualTo(nineThirds)); // true                                          
		
		console.log("'Three is greater than or equal to nine thirds' is:");
		console.log(three.isGreaterThanOrEqualTo(nineThirds)); // true                             
		
		console.log("'Three is greater than nine thirds' is:");
		console.log(three.isGreaterThan(nineThirds)); // false	

###Class Methods
* gcd

		var RationalNumber = require('jinac').RationalNumber;
		var six = new	RationalNumber('6');
		var eight = new RationalNumber('8');
		var gcd	= RationalNumber.gcd(six, eight);
		console.log("The gcd of six and eight is:");
		console.log(gcd); // { denominator : 1, numerator : 2 }
		
* lcm

		var RationalNumber = require('jinac').RationalNumber;
		var six = new	RationalNumber('6');
		var eight = new RationalNumber('8');
		var lcm	= RationalNumber.lcm(six, eight);
		console.log("The lcm of six and eight is:");
		console.log(lcm); // { denominator : 1, numerator : 24 }






		




	
