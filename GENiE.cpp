// Authors: Elvis Le and Alice Pierce
#include "auxilliary.h"

int main() {
  unsigned int userChoice = 0; // keep track of what user chooses to do
  bool notValidChoice; // check if user's choice is valid
  // create title banner and display menu
  CreateTitleBanner();
  std::cin >> userChoice; // take in user's choice

  /*
   * check if input is an integer
   * notValidChoice should be true if use inputs a non-integer
   *  or an integer out of range (1-3) 
   */
  notValidChoice = std::cin.fail() || userChoice < 1 || userChoice > 3 ? 
    true : false;

  // if user did not input valid option, prompt again
  while (notValidChoice) {
    // clear input stream
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    std::cout << "Invalid Option\n> ";
    std::cin >> userChoice;
    
    // check if user input is valid, if valid, break
    notValidChoice = std::cin.fail() || userChoice < 1 || userChoice > 3 ? 
      true : false;
  } // while

  ProcessUserChoice(userChoice);

  return 0;

} // main

