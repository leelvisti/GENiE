// Authors: Elvis Le and Alice Pierce
#include <iostream>

void createTitleBanner();

int main() {
  // variable decalrations
  unsigned int userChoice = 0; // keep track of what user chooses to do
  bool notValidChoice; // check if user's choice is valid
  /*
   * Prompt user with options to choose
   * 1) program will do DNA to protein translation
   * 2) program will do protein to DNA translation
   * 3) program exits
   */
  createTitleBanner();
  std::cout << "What would you like to do:\n"
    "1) DNA-Protein Translation\n"
    "2) Protein-DNA Back Translation\n"
    "3) Exit GENiE\n";

  std::cout << "> ";
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

  switch (userChoice) {
    case 1:
      std::cout << "DNA-Protein\n";
      break;
    case 2:
      std::cout << "Protein-DNA\n";
      break;
    default:
      std::cout << "Exiting GENiE\n";
      break;
  }
  return 0;

} // main

void createTitleBanner() {
  std::cout << 
    "  ____   ___   _____   __   ___\n"
    " / ___| |  _| |   | | (__) |  _|\n"
    "| |  _  | |_  |   | | |  | | |_\n"
    "| |_| | |  _| | |   | |  | |  _|\n"
    " \\____| |___| |_|___| |__| |___|\n\n";
} // createTitleBanner
