var RationalNumber = require('jinac').RationalNumber,
    should         = require('should');

describe('RationalNumber', function() {

    var powerTestCases = [null, null];

    powerTestCases[0] = [ // column -> exponent, row -> base.
        ['',     '-8',        '-4',       '-3',        '-2',      '-1/2',        '-1/3' ],
        ['-8',   '1/16777216','1/4096',   '-1/512',    '1/64',    'err',         '-1/2' ],
        ['-4',   '1/65536',   '1/256',    '-1/64',     '1/16',    'err',         'err'  ],
        ['-3',   '1/6561',    '1/81',     '-1/27',     '1/9',     'err',         'err'  ],
        ['-2',   '1/256',     '1/16',     '-1/8',      '1/4',     'err',         'err'  ],
        ['-1/2', '256',       '16',       '-8',        '4',       'err',         'err'  ],
        ['-1/3', '6561',      '81',       '-27',       '9',       'err',         'err'  ],
        ['0',    'err',       'err',      'err',       'err',     'err',         'err'  ],
        ['1/3',  '6561',      '81',       '27',        '9',       'err',         'err'  ],
        ['1/2',  '256',       '16',       '8',         '4',       'err',         'err'  ],
        ['2',    '1/256',     '1/16',     '1/8',       '1/4',     'err',         'err'  ],
        ['3',    '1/6561',    '1/81',     '1/27',      '1/9',     'err',         'err'  ],
        ['4',    '1/65536',   '1/256',    '1/64',      '1/16',    '1/2',         'err'  ],
        ['8',    '1/16777216','1/4096',   '1/512',     '1/64',    'err',         '1/2'  ]
    ];

    powerTestCases[1] = [ // column -> exponent, row -> base.
        ['',     '0',         '1/3',      '1/2',       '2',       '3',           '4',       '8'        ],
        ['-8',   '1',         '-2',        'err',       '64',      '-512',        '4096',   '16777216' ],
        ['-4',   '1',         'err',      'err',       '16',      '-64',         '256',     '65536'    ],
        ['-3',   '1',         'err',      'err',       '9',       '-27',         '81',      '6561'     ],
        ['-2',   '1',         'err',      'err',       '4',       '-8',          '16',      '256'      ],
        ['-1/2', '1',         'err',      'err',       '1/4',     '-1/8',        '1/16',    '1/256'    ],
        ['-1/3', '1',         'err',      'err',       '1/9',     '-1/27',       '1/81',    '1/6561'   ],
        ['0',    '1',         '0',        '0',         '0',       '0',           '0',       '0'        ],
        ['1/3',  '1',         'err',      'err',       '1/9',     '1/27',        '1/81',    '1/6561'   ],
        ['1/2',  '1',         'err',      'err',       '1/4',     '1/8',         '1/16',    '1/256'    ],
        ['2',    '1',         'err',      'err',       '4',       '8',           '16',      '256'      ],
        ['3',    '1',         'err',      'err',       '9',       '27',          '81',      '6561'     ],
        ['4',    '1',         'err',      '2',         '16',      '64',          '256',     '65536'    ],
        ['8',    '1',         '2',        'err',       '64',      '512',         '4096',    '16777216' ]
    ];



    describe('constructor', function() {
        it('should allow constructing a new fraction.', function() {
            var firstFraction = new RationalNumber();
            (firstFraction instanceof RationalNumber).should.eql(true);
        });

        it('should allow initialization from a string.', function() {
            var secondFraction = new RationalNumber('1/3');
            (secondFraction instanceof RationalNumber).should.eql(true);
            secondFraction.numerator.should.eql('1');
            secondFraction.denominator.should.eql('3');
        });
    });

    describe('numerator', function() {
        it('should allow setting and getting the numerator of a fraction, using numbers.', function() {
            var fraction = new RationalNumber();
            fraction.numerator = 42;
            fraction.numerator.should.eql('42');
        });

        it('should allow setting and getting the numerator of a fraction, using strings.', function() {
            var fraction = new RationalNumber();
            fraction.numerator = '42';
            fraction.numerator.should.eql('42');
        });

        it('should throw an error if given bad integer syntax.', function() {
            var fraction = new RationalNumber();
            try {
                fraction.numerator = 'poop';
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }

            try {
                fraction.numerator = {"poop" : true};
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }

            try {
                fraction.numerator = ['poop', 'face'];
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }

            try {
                fraction.numerator = true;
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }
        }); // End bad integer syntax case.


    });

    describe('denominator', function() {
        it('should allow setting and getting the denominator of a fraction, using numbers.', function() {
            var fraction = new RationalNumber();
            fraction.numerator = 1;
            fraction.denominator = 43;
            fraction.denominator.should.eql('43');
        });

        it('should allow setting and getting the denominator of a fraciton, using strings.', function() {
            var fraction = new RationalNumber();
            fraction.numerator = 1;
            fraction.denominator = '43';
            fraction.denominator.should.eql('43');
        });

        it('should throw an error when setting the denominator to zero from a number.', function() {
            var fraction = new RationalNumber();
            try {
                fraction.denominator = 0;
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('divide by zero') > -1).should.eql(true);
            }
        });

        it('should throw an error if given bad integer syntax.', function() {
            var fraction = new RationalNumber();
            try {
                fraction.denominator = 'poop';
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }

            try {
                fraction.denominator = {"poop" : true};
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }

            try {
                fraction.denominator = ['poop', 'face'];
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }

            try {
                fraction.denominator = true
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }
        }); // End bad integer syntax case.

    });

    describe('initializeFromString', function() {
        it('should allow intialization of a rational number from slash notation.', function() {
            var fraction = new RationalNumber();
            fraction.initializeFromString('-2/3');
            fraction.numerator.should.eql('-2');
            fraction.denominator.should.eql('3');
        });
        it('should allow initialization of a rational number from integer notation.', function() {
            var fraction = new RationalNumber();
            fraction.initializeFromString('-2');
            fraction.numerator.should.eql('-2');
            fraction.denominator.should.eql('1');
        });

        it('should throw an error if given bad fraction syntax.', function() {
            var fraction = new RationalNumber();
            try {
                fraction.initializeFromString('poop');
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('fraction') > -1).should.eql(true);
            }

            try {
                fraction.initializeFromString({"poop" : true});
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('fraction') > -1).should.eql(true);
            }

            try {
                fraction.initializeFromString(['poop', 'face']);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('fraction') > -1).should.eql(true);
            }

            try {
                fraction.initializeFromString(true);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('fraction') > -1).should.eql(true);
            }

        }); // End bad fraction syntax case.
    });

    describe('add', function() {
        it('should allow adding two rational numbers together, obtaining another rational number.', function() {
            var oneHalf = new RationalNumber();
            oneHalf.initializeFromString('1/2');
            var twoThirds = new RationalNumber();
            twoThirds.initializeFromString('2/3');
            var sevenSixths = oneHalf.add(twoThirds);
            (sevenSixths instanceof RationalNumber).should.eql(true);
            sevenSixths.numerator.should.eql('7');
            sevenSixths.denominator.should.eql('6');
        });

        it('should throw an error, when given anything other than another rational number object.', function() {
            var oneHalf = new RationalNumber();
            oneHalf.initializeFromString('1/2');
            try {
                var sevenSixths = oneHalf.add(twoThirds);
                true.should.eql(false); // Shouldn't get here.
            } catch(e) {
                (e.indexOf('rational') > -1).should.be.true;
            }
        });
    });

    describe('subtract', function() {
        it('should allow subtracting two rational numbers, obtaining another rational number.', function() {
            var oneHalf = new RationalNumber();
            oneHalf.initializeFromString('1/2');
            var twoThirds = new RationalNumber();
            twoThirds.initializeFromString('2/3');
            var negativeOneSixth = oneHalf.subtract(twoThirds);
            (negativeOneSixth instanceof RationalNumber).should.eql(true);
            negativeOneSixth.numerator.should.eql('-1');
            negativeOneSixth.denominator.should.eql('6');
        });
    });

    describe('multiply', function() {
        it('should allow multiplication of two rational numbers, obtaining another rational number.', function() {
            var twoThirds = new RationalNumber();
            twoThirds.initializeFromString('2/3');
            var threeQuarters = new RationalNumber();
            threeQuarters.initializeFromString('3/4');
            var oneHalf = twoThirds.multiply(threeQuarters);
            (oneHalf instanceof RationalNumber).should.eql(true);
            oneHalf.numerator.should.eql('1');
            oneHalf.denominator.should.eql('2');
        });
    });

    describe('divide', function() {
        it('should allow division of rational numbers, obtaining another rational number.', function() {
            var twoThirds = new RationalNumber();
            twoThirds.initializeFromString('2/3');
            var threeQuarters = new RationalNumber();
            threeQuarters.initializeFromString('3/4');
            var eightNinths = twoThirds.divide(threeQuarters);
            (eightNinths instanceof RationalNumber).should.eql(true);
            eightNinths.numerator.should.eql('8');
            eightNinths.denominator.should.eql('9');
        });

        it('should throw an exception when trying to divide by zero.', function() {
            var one = new RationalNumber();
            one.initializeFromString("1");
            var zero = new RationalNumber();
            zero.initializeFromString("0");
            try {
                var result = one.divide(zero);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('divide by zero') > -1).should.eql(true);
            }
        });
    });

    describe('isEqualTo', function() {
        it('should recognize when two fractions are equal', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('2/3');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('4/6');
            frac1.isEqualTo(frac2).should.eql(true);
        });

        it('should recognize when two fractions are not equal', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('2/3');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('5/6');
            frac1.isEqualTo(frac2).should.eql(false);
        });
    });


    function runPowerTest(t, i, j) {
        var baseFraction = new RationalNumber();
        var exponentFraction = new RationalNumber();
        var expectedFraction = new RationalNumber();
        var baseString = null;
        var exponentString = null;
        var expectedString = null;
        var gotFraction = null;
        var runtimeError = null;
        var thesePowerTestCases = powerTestCases[t];

        it('should compute powers like basic algebra students dofor test case: (' + t + ', ' + i + ', ' + j + ').', function() {
            exponentString = thesePowerTestCases[0][j];
            runtimeError = '';
            gotFraction = null;
            baseString = thesePowerTestCases[i][0];
            baseFraction.initializeFromString(baseString);
            exponentFraction.initializeFromString(exponentString);
            expectedString = thesePowerTestCases[i][j];
            try {
                gotFraction = baseFraction.power(exponentFraction);
            } catch(error) {
                runtimeError = error.toString();
                gotFraction = null;
            }
            if (expectedString == 'err') {
                (runtimeError.length > 0).should.eql(true);
            } else {
                (gotFraction instanceof RationalNumber).should.eql(true);
                expectedFraction.initializeFromString(expectedString);
                (gotFraction.isEqualTo(expectedFraction)).should.eql(true);
            }        
        });
    }


    function runPowerTests() {
        for (var t = 0; t < powerTestCases.length; t++) {
            for (var i = 1; i < powerTestCases[t].length; i++) {
                for (var j = 1; j < powerTestCases[t][i].length; j++) {
                    runPowerTest(t, i, j);
                } // End inner loop.
            } // End outer loop
        } // End test case loop.
    }

    describe('power', function() {
        runPowerTests();
    });


    describe('isLessThan', function() {
        it('should return true when first argument is less than second.', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('3/7');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('4/7');
            frac1.isLessThan(frac2).should.eql(true);
        });

        it('should return false when first argument is equal second.', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('4/7');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('4/7');
            frac1.isLessThan(frac2).should.eql(false);
        });

        it('should return false when first argument is greater than second.', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('5/7');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('4/7');
            frac1.isLessThan(frac2).should.eql(false);
        });
    }); // End isLessThan test.

    describe('isGreaterThan', function() {
        it('should return false when first argument is less than second.', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('3/7');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('4/7');
            frac1.isGreaterThan(frac2).should.eql(false);
        });

        it('should return false when first argument is equal second.', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('4/7');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('4/7');
            frac1.isGreaterThan(frac2).should.eql(false);
        });

        it('should return true when first argument is greater than second.', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('5/7');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('4/7');
            frac1.isGreaterThan(frac2).should.eql(true);
        });
    }); // End isGreaterThan test.

    describe('isLessThanOrEqualTo', function() {
        it('should return true when first argument is less than second.', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('3/7');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('4/7');
            frac1.isLessThanOrEqualTo(frac2).should.eql(true);
        });

        it('should return true when first argument is equal second.', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('4/7');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('4/7');
            frac1.isLessThanOrEqualTo(frac2).should.eql(true);
        });

        it('should return false when first argument is greater than second.', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('5/7');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('4/7');
            frac1.isLessThanOrEqualTo(frac2).should.eql(false);
        });
    }); // End isLessThanOrEqualTo test.

    describe('isGreaterThanOrEqualTo', function() {
        it('should return false when first argument is less than second.', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('3/7');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('4/7');
            frac1.isGreaterThanOrEqualTo(frac2).should.eql(false);
        });

        it('should return true when first argument is equal second.', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('4/7');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('4/7');
            frac1.isGreaterThanOrEqualTo(frac2).should.eql(true);
        });

        it('should return true when first argument is greater than second.', function() {
            var frac1 = new RationalNumber();
            frac1.initializeFromString('5/7');
            var frac2 = new RationalNumber();
            frac2.initializeFromString('4/7');
            frac1.isGreaterThanOrEqualTo(frac2).should.eql(true);
        });
    }); // End isGreaterThanOrEqualTo test.


    describe('factorial', function() {
        it('should compute the factorial of a small positive integer.', function() {
            var smallInteger = new RationalNumber();
            smallInteger.initializeFromString('5');
            var result = smallInteger.factorial();
            (result instanceof RationalNumber).should.eql(true);
            result.numerator.should.eql('120');
            result.denominator.should.eql('1');
        });

        it('should compute the factorial of a big positive integer.', function() {
            var bigInteger = new RationalNumber();
            bigInteger.initializeFromString('700');
            var result = bigInteger.factorial();
            (result instanceof RationalNumber).should.eql(true);
            result.numerator.should.eql('2422040124750272179867875093812352218590983385729207299450679664929938160215647420444519051666484819249321456671497049842327525093874817343838393757631459228450828499972271274140160311057830558463636337124079332447820739281101037112665387537180790257577919273108262916904750405235055060084012219492892375635136296622020023178109619818046179906897450420548912610870589088056503913584562211037693288782960900195074130999799035970711436279339094292032866260496375825461427727555710003007752906141470639574390024988514914264449865006458873226951941899545970333910351588559232940829569276986080222200289966128343931630028789203382654749603473516314765262772257171154686716862814184728741187147936349501653197457455660413134506049122044947052623384682088864790673309569292384215611788014274954905914148362303226200246816441301934846080254998647325270606104512088058712293349862185399243309054299576381718806247238195232604642614329894070636163753672091232751612378348273840757873567717532879242518337119540602943609411629349009566043720836737401090882392975031224612531245642687296717053747734506443314924558119560479901478736209556925161517737110399754730551854066328420014728657896286936523787080206476327157136441318773432751007263108056958251693811280957243202460157111778617472683761623869704457588005158037495665069625778930898095725794710701639238231528115579619120287378689238934335198508665933917257143975277707590597511989345068701735940169672561864713107115016747368992690116082633762172346688969840862517264384000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000');
            result.denominator.should.eql('1');
        }); // End big factorial test case.

        it('should throw an error when trying to compute the factorial of a non-integer', function() {
            var fraction = new RationalNumber();
            fraction.initializeFromString('3/7');
            try {
                var result = fraction.factorial();
                false.should.eql(true); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }
        });

        it('should throw an error when trying to compute the factorial of a negative number', function() {
            var negativeInteger = new RationalNumber();
            negativeInteger.initializeFromString('-3');
            try {
                var result = negativeInteger.factorial();
                false.should.eql(true); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('positive') > -1).should.eql(true);
            }
        });

        it('should throw an error when trying to compute the factorial of a "too big" number', function() {
            var tooBigNumber = new RationalNumber();
            tooBigNumber.initializeFromString('45001');
            try {
                var result = tooBigNumber.factorial();
                false.should.eql(true); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('too big') > -1).should.eql(true);
            }
        });
    }); // End factorial cases.

    describe('modulus', function() {
        it('should compute the remainder for integers.', function() {
            var five = new RationalNumber();
            five.initializeFromString('5');
            var three = new RationalNumber();
            three.initializeFromString('3');
            var two = five.modulus(three);
            two.numerator.should.eql('2');
            two.denominator.should.eql('1');
        });

        it('should compute the remainder for fractions.', function() {
            var five = new RationalNumber();
            five.initializeFromString('5/7');
            var three = new RationalNumber();
            three.initializeFromString('3/7');
            var two = five.modulus(three);
            two.numerator.should.eql('2');
            two.denominator.should.eql('7');
        });

        it('should throw an error when trying to mod by zero.', function() {
            var five = new RationalNumber();
            five.initializeFromString('5');
            var zero = new RationalNumber();
            zero.initializeFromString('0');
            try {
                var result = five.modulus(zero);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('divide by zero') > -1).should.eql(true);
            }
        });
    });


    describe('gcd', function() {
        it('should compute the gcd for integers.', function() {
            var six = new RationalNumber();
            six.initializeFromString('6');
            var three = new RationalNumber();
            three.initializeFromString('3');
            var gcdResult = RationalNumber.gcd(six, three);
            gcdResult.numerator.should.eql('3');
            gcdResult.denominator.should.eql('1');
        });

        it('should compute the gcd for negative integers.', function() {
            var negativeSix = new RationalNumber();
            negativeSix.initializeFromString('-6');
            var three = new RationalNumber();
            three.initializeFromString('3');
            var gcdResult = RationalNumber.gcd(negativeSix, three);
            gcdResult.numerator.should.eql('3');
            gcdResult.denominator.should.eql('1');
        });

        it('should throw an error when the first arg is non-integer.', function() {
            var a = new RationalNumber('1/2');
            var b = new RationalNumber('2');
            try {
                var result = RationalNumber.gcd(a, b);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }
        });

        it('should throw an error when the second arg is non-integer.', function() {
            var a = new RationalNumber('2');
            var b = new RationalNumber('1/2');
            try {
                var result = RationalNumber.gcd(a, b);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }
        });

        it('should throw an error when both args are non-integer.', function() {
            var a = new RationalNumber('2/3');
            var b = new RationalNumber('1/2');
            try {
                var result = RationalNumber.gcd(a, b);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }
        });

        it('should throw an error when second arg is not a rational number object.', function() {
            var a = new RationalNumber('2');
            var b = "5";
            try {
                var result = RationalNumber.gcd(a, b);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('rational') > -1).should.eql(true);
            }
        });

        it('should throw an error when first arg is not a rational number object.', function() {
            var b = new RationalNumber('2');
            var a = "5";
            try {
                var result = RationalNumber.gcd(a, b);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('rational') > -1).should.eql(true);
            }
        });


        it('gcd(0,0) defined as 0.', function() {
            var b = new RationalNumber('0');
            var a = new RationalNumber('0');
            var result = RationalNumber.gcd(a, b);
            result.numerator.should.eql('0');
            result.denominator.should.eql('1');
        });


    });


    describe('lcm', function() {
        it('should compute the lcm for integers.', function() {
            var six = new RationalNumber();
            six.initializeFromString('6');
            var three = new RationalNumber();
            three.initializeFromString('3');
            var lcmResult = RationalNumber.lcm(six, three);
            lcmResult.numerator.should.eql('6');
            lcmResult.denominator.should.eql('1');
        });

        it('should compute the lcm for negative integers.', function() {
            var negativeSix = new RationalNumber();
            negativeSix.initializeFromString('-6');
            var three = new RationalNumber();
            three.initializeFromString('3');
            var lcmResult = RationalNumber.lcm(negativeSix, three);
            lcmResult.numerator.should.eql('6');
            lcmResult.denominator.should.eql('1');
        });

        it('should throw an error when the first arg is non-integer.', function() {
            var a = new RationalNumber('1/2');
            var b = new RationalNumber('2');
            try {
                var result = RationalNumber.lcm(a, b);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }
        });

        it('should throw an error when the second arg is non-integer.', function() {
            var a = new RationalNumber('2');
            var b = new RationalNumber('1/2');
            try {
                var result = RationalNumber.lcm(a, b);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }
        });

        it('should throw an error when both args are non-integer.', function() {
            var a = new RationalNumber('2/3');
            var b = new RationalNumber('1/2');
            try {
                var result = RationalNumber.lcm(a, b);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('integer') > -1).should.eql(true);
            }
        });

        it('should throw an error when second arg is not a rational number object.', function() {
            var a = new RationalNumber('2');
            var b = "5";
            try {
                var result = RationalNumber.lcm(a, b);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('rational') > -1).should.eql(true);
            }
        });

        it('should throw an error when first arg is not a rational number object.', function() {
            var b = new RationalNumber('2');
            var a = "5";
            try {
                var result = RationalNumber.lcm(a, b);
                true.should.eql(false); // Should never get here.
            } catch(error) {
                (error.toString().indexOf('rational') > -1).should.eql(true);
            }
        });


        it('lcm(0,0) defined as 0.', function() {
            var b = new RationalNumber('0');
            var a = new RationalNumber('0');
            var result = RationalNumber.lcm(a, b);
            result.numerator.should.eql('0');
            result.denominator.should.eql('1');
        });


    }); // End lcm block.


});