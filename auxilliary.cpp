#include "auxilliary.h"

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

  std::shared_ptr<std::string> templateDNAPtr = std::make_shared<std::string>(templateDNA.getSequence());
  // get the 5'-3' of the complementary strand because reading frames are read from 5'-3' instead of 3'-5'
  std::shared_ptr<std::string> complementaryDNAPtr = std::make_shared<std::string>(complementaryDNA.getReverseSequence());
  
  TranslateToProtein(templateDNAPtr, complementaryDNAPtr);

} // DoDNAToProtein

// find open reading frames to translate
void TranslateToProtein(std::shared_ptr<std::string> strand1, std::shared_ptr<std::string> strand2) {
  std::string openReadingFrame1, openReadingFrame2, finalOpenReadingFrame;
  std::vector<DNA> strandVector; // store multiple reading frames
  DNA dnaToBeTranscribed;
  // iterate through strand to find start codon (ATG_ and stop codons (TAA, TAG, or TGA)
  // DNA Template
  std::cout << "Attempting to find reading frames from DNA template strand...\n";
  openReadingFrame1 = FindOpenReadingFrame(strand1);
  openReadingFrame1.size() == 0 ? 
    std::cout << "No Open Reading Frame found for DNA template strand\n" : std::cout << std::endl;
  DNA templateDNA;
  templateDNA.setSequence(openReadingFrame1);

  // DNA complementary 
  std::cout << "Attempting to find reading frames from DNA complementary strand...\n";
  openReadingFrame2 = FindOpenReadingFrame(strand2);
  openReadingFrame2.size() == 0 ? 
    std::cout << "No Open Reading Frame found for DNA complementary strand\n" : std::cout << std::endl;  
  DNA complementaryDNA;
  complementaryDNA.setSequence(openReadingFrame2);

  // if both template and complementary reading frame are equal in size, push to vector
  if (openReadingFrame1.size() == openReadingFrame2.size()) {
    strandVector.push_back(templateDNA);
    strandVector.push_back(complementaryDNA);
  } // if
  else {
    finalOpenReadingFrame = (openReadingFrame1.size() > openReadingFrame2.size() ?
        openReadingFrame1 : openReadingFrame2);
    dnaToBeTranscribed.setSequence(finalOpenReadingFrame);
    strandVector.push_back(dnaToBeTranscribed);
  } // else

  PrintReadingFrames(strandVector);
  TranscribeToRNA(strandVector);
} // TranslateToProtein

// Find Open Reading Frames of strand to attempt translation to Protein
std::string FindOpenReadingFrame(std::shared_ptr<std::string> strand) {
  std::string openReadingFrame;
  int size = strand->size(), pos= 0, endPos = 0, itr = 0, count = 0;
  bool isATGPresent = false; // keep track if start codon is present in strand
  // creating shared pointers for ease of passing through functions
  std::shared_ptr<int> countPtr = std::make_shared<int>(count), 
    posPtr = std::make_shared<int>(pos), endPosPtr = std::make_shared<int>(endPos);
  std::shared_ptr<bool> isATGPresentPtr = std::make_shared<bool>(isATGPresent);
  std::shared_ptr<std::string> openReadingFramePtr = std::make_shared<std::string>(openReadingFrame);

  for (int i = 0; i < size && itr < size; i = itr) {
    std::string codon = strand->substr(i, 3); // creating substring of length three

    // create shared pointers to get passed to helper function to find start and stop codons
    std::shared_ptr<std::string> codonPtr = std::make_shared<std::string>(codon);
    std::shared_ptr<int> iPtr = std::make_shared<int>(i);
    
    FindStartCodon(countPtr, codonPtr, isATGPresentPtr, posPtr, iPtr); // find occurence of start codon
    FindStopCodon(strand, countPtr, codonPtr, isATGPresentPtr, 
        posPtr, endPosPtr, iPtr, openReadingFramePtr); // find the stop codons

    // if a start codon is found, increment by 3 since codons are of length 3
    if (isATGPresent)
      itr += 3;
    else // continue incrementing one base at a time to find start codon
      itr++;

  } // for

  return *openReadingFramePtr;
} // FindOpenReadingFrame()

void FindStartCodon(std::shared_ptr<int> count, std::shared_ptr<std::string> codon, std::shared_ptr<bool> isATGPresent, std::shared_ptr<int> pos, std::shared_ptr<int> i) {
  // if start codon is found within strand
  if (*codon == "ATG") {
    if (*count == 0) {
      *pos = *i;
      *isATGPresent = true;
    } // if

    (*count)++;
  } // if
} // FindStartCodon

void FindStopCodon(std::shared_ptr<std::string> strand, std::shared_ptr<int> count, std::shared_ptr<std::string> codon, std::shared_ptr<bool> isATGPresent, std::shared_ptr<int> pos, std::shared_ptr<int> endPos, std::shared_ptr<int> i,
    std::shared_ptr<std::string> openReadingFrame) {
  std::string possibleOpenReadingFrame;
  int openReadingFrameSize1 = 0, openReadingFrameSize2 = 0;

  if (*codon == "TAA" || *codon == "TAG" || *codon == "TGA") {
    *endPos = *i;

    // if there was an ATG present, get the sequence between start codon and stop codon
    if (*isATGPresent) {
      std::cout << "Found possible Open Reading Frame: ";
      possibleOpenReadingFrame = strand->substr(*pos, *endPos - *pos + 3);
      openReadingFrameSize1 = possibleOpenReadingFrame.size(); // keep track if largest reading frame to translate

      // hold the substring with largest reading frame
      if (openReadingFrameSize1 > openReadingFrameSize2)
        *openReadingFrame = possibleOpenReadingFrame;
      
      // store for future comparisons of possible reading frames
      openReadingFrameSize2 = openReadingFrameSize1;
      std::cout << possibleOpenReadingFrame << std::endl;
      
      // reset search for ATG
      *isATGPresent = false;
      *count = 0;
    } // if
  } // if

} // FindStopCodon

void PrintReadingFrames(std::vector<DNA> strandVector) {
  std::cout << "Final Open Reading Frame(s): ";
  
  int vectorIteration = 0;
  for (auto itr = strandVector.begin(); itr != strandVector.end(); itr++) {
    std::cout << itr->getSequence() << std::endl;
    // formatting purposes for showing multiple final open reading frames
    if (vectorIteration != strandVector.size() - 1)
      std::cout << "                             "; 
    
    vectorIteration++;
  } // for
} // PrintReadingFrames

void TranscribeToRNA(std::vector<DNA> strandVector) {
  for (auto itr = strandVector.begin(); itr != strandVector.end(); itr++) {
    itr->transcribeToRNA();
  } // for
} // TranscribeToRNA
