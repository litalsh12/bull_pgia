/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */


#include <iostream>
using namespace std;

#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
#include "badkan.hpp"
#define COMMA ,

using namespace bullpgia;

int main() {

	badkan::TestCase testcase;
	int grade=0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0) {

		// BASIC TESTS - DO NOT CHANGE
    ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"},c98a7{"98a7"},c123{"123"},c1111{"1111"};
		ConstantGuesser g1234{"1234"}, g12345{"12345"}, g9999{"9999"},g98a7{"98a7"},g123{"123"},g1111{"1111"}; 


		testcase.setname("Calculate bull and pgia")
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1234"), "4,0")      // 4 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1034"), "3,0")			 // 3 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1039"), "2,0")			 // 2 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","6214"), "2,1")      // 2 bull, 1 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","3214"), "2,2")      // 2 bull, 2 pgia
   	.CHECK_OUTPUT(calculateBullAndPgia("1234","8039"), "1,0")			 // 1 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","8139"), "1,1")			 // 1 bull, 1 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","4139"), "1,2")			 // 1 bull, 2 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","2314"), "1,3")      // 1 bull, 3 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","9876"), "0,0")      // 0 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","9871"), "0,1")      // 0 bull, 1 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","9326"), "0,2")      // 0 bull, 2 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","3821"), "0,3")      // 0 bull, 3 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","4321"), "0,4")      // 0 bull, 4 pgia

		.CHECK_OUTPUT(calculateBullAndPgia("980","980"), "3,0")      // 3 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("980","930"), "2,0")      // 2 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("980","584"), "1,0")      // 1 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("980","904"), "1,1")      // 1 bull, 1 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("980","089"), "1,2")      // 1 bull, 2 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("980","543"), "0,0")      // 0 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("980","593"), "0,1")      // 0 bull, 1 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("980","048"), "0,2")      // 0 bull, 2 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("980","809"), "0,3")      // 0 bull, 3 pgia

		.CHECK_OUTPUT(calculateBullAndPgia("654321","654321"), "6,0")    // 0 bull, 6 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("654321","657321"), "5,0")    // 5 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("654321","894321"), "4,0")    // 4 bull, 0 pgia
	
		.CHECK_OUTPUT(calculateBullAndPgia("654321","123456"), "0,6")    // 0 bull, 6 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("654321","123000"), "0,3")    // 0 bull, 3 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("654321","666666"), "1,5")    // 1 bull, 5 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("654321","615243"), "3,3")    // 3 bull, 3 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("654321","098790"), "0,0")    // 0 bull, 0 pgia
	
		.CHECK_THROWS(calculateBullAndPgia("654asa321","098ss0"))
		.CHECK_THROWS(calculateBullAndPgia("6542234","012"))
		.CHECK_THROWS(calculateBullAndPgia("abc","abc"))
		.CHECK_THROWS(calculateBullAndPgia("654_34","098123"))
		.CHECK_THROWS(calculateBullAndPgia("65 63","6563"))
		.CHECK_THROWS(calculateBullAndPgia("6321","abcd"))
		.CHECK_THROWS(calculateBullAndPgia("6321","6 321"))
		.CHECK_THROWS(calculateBullAndPgia("654","0+k"))
		;

		testcase.setname("Play with dummy choosers and guessers")
		.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)      // guesser wins in one turn.
		.CHECK_EQUAL(play(c1234, g9999, 4, 100), 101)    // guesser loses by running out of turns 
		.CHECK_EQUAL(play(c1234, g12345, 4, 100), 101)   // guesser loses technically by making an illegal guess (too long).
		.CHECK_EQUAL(play(c12345, g1234, 4, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
		
		;

		testcase.setname("Play with smart guesser");
		RandomChooser randy;
		SmartGuesser smarty;
		for (uint i=0; i<100; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 4, 100)<=10, true);  // smarty should always win in at most 10 turns!
		}
		for (uint i=0; i<100; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 3, 100)<=10, true);  // smarty should always win in at most 10 turns!
		}		
		for (uint i=0; i<100; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 8, 100)<=10, true);  // smarty should always win in at most 10 turns!
		}		
    grade = testcase.grade();
	} else {
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: "  << grade << endl;
	return 0;
}

