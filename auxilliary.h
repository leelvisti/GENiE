#ifndef AUXILLIARY_H
#define AUXILLIARY_H

#include "gene.h"

void CreateTitleBanner();
void ProcessUserChoice(const unsigned int userChoice);
void DoDNAToProtein();
void DoProteinToDNA();

// Create title banner and display menu
void CreateTitleBanner() {
  std::cout << 
    "  ____   ___   _____   __   ___\n"
    " / ___| |  _| |   | | (__) |  _|\n"
    "| |  _  | |_  |   | | |  | | |_\n"
    "| |_| | |  _| | |   | |  | |  _|\n"
   " \\____| |___| |_|___| |__| |___|\n\n";
  
  /*
   * Prompt user with options to choose
   * 1) program will do DNA to protein translation
   * 2) program will do protein to DNA translation
   * 3) program exits
   */
  std::cout << "What would you like to do:\n"
    "1) DNA-Protein Translation\n"
    "2) Protein-DNA Back Translation\n"
    "3) Exit GENiE\n"
    "> ";
} // createTitleBanner

// Do the option that user chose
void ProcessUserChoice(const unsigned int userChoice) {
  switch (userChoice) {
    // translate DNA to protein;
    case 1:
      DoDNAToProtein();
      break;
    // translate protein to DNA;
    case 2:
      std::cout << "Protein-DNA\n";
      // translateProteinToDNA();
      break;
    // exit program;
    default:
      std::cout << "Exiting GENiE\n";
      break;
  }
} // processUserChoice

void DoDNAToProtein() {
  std::string sequence, complementarySequence;
  DNA templateDNA, complementaryDNA; 
  // prompt user for sequence input
  std::cout << "Input DNA sequence 5\' to 3\'\n> ";
  std::cin >> sequence;
  templateDNA.setSequence(sequence);
  complementarySequence = templateDNA.CreateComplementaryStrand();
  complementaryDNA.setSequence(complementarySequence);
 
  // display alignments between template and complementary strands
  std::cout << "5' " << templateDNA.getSequence() << " 3'\n";
  std::cout << "   ";
  
  for (unsigned int i = 0; i < templateDNA.getSequence().size(); i++)
    std::cout << "|";

  std::cout << "\n3' " << complementaryDNA.getSequence() << " 5'\n";
} // DoDNAToProtein

#endif
