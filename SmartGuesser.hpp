#pragma once
#include "Guesser.hpp"
#include<string>
using std::string;
namespace bullpgia {
class SmartGuesser: public bullpgia::Guesser 
{
		string myGuess;
	public:
		SmartGuesser() 
		{		
			this->myGuess="";	
		 }

		    string guess() override;
		   
};
 }