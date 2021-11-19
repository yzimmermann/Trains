#include <iostream>
#include <istream>
#include "ebnf_helpers.h"

bool composition(std::istream& is);
bool compositions(std::istream& is);
bool open(std::istream& is);
bool loco(std::istream& is);
bool cars(std::istream& is);
bool train(std::istream& is);


bool composition(std::istream& is){
  if(consume(is, '<') && open(is) && loco(is) && consume(is, '>') ){
    return true;
  }
  return false;
}


bool compositions(std::istream& is){
  if(composition(is)){
    while(composition(is));
    return true;
  }
  return false;
}


bool cars(std::istream& is){
  if(consume(is, '-')){
    return true;
  }
  
  if(consume(is, '(') && cars(is) && consume(is, ')')){
    return true;
  }
  
  return false;
  
}


bool loco(std::istream& is){
  if(consume(is, '*')){
    loco(is);
    return true;
  }
  return false;
}

bool open(std::istream& is){
  if(loco(is) && cars(is)){
    return true;
  }
  return false;
}


bool train(std::istream& is) {
  //Naive Approach
  //   if (consume(is, '[') && (open(is) != compositions(is)) && consume(is, ']')){
  //     return true;
  //   }
  //   return false;
  
  if (consume(is, '[')){
    if (lookahead(is) == '*'){
      if (open(is) && consume(is, ']')){
        return true;
      }
    }else if(lookahead(is) == '<'){
      if(compositions(is) && consume(is, ']')){
        return true;
      }
    }
  }
  return false;
}


int main() {
    // Do not edit this function
    std::cerr << "please enter a train formation:\n";

    if (train(std::cin)) {
        std::cout << "valid\n";
    } else {
        std::cout << "invalid\n";
    }
    return 0;
}
