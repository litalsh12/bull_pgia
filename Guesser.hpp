  
#pragma once
#include <string>
using std::string;
namespace bullpgia{

class Guesser{
 protected:
 uint length;
 
 public:
 virtual string guess(){};
 virtual void startNewGame(uint length){};
 virtual void learn(string ans){};

};
}
