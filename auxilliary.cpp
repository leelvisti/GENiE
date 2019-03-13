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

std::map<std::string, std::string> CreateAminoAcidCodonMap() {
  std::map<std::string, std::string> threeLetterMap;
  threeLetterMap["UUU"] = "Phe";  threeLetterMap["UUC"] = "Phe"; 
  threeLetterMap["UUA"] = "Leu";  threeLetterMap["UUG"] = "Leu";
  threeLetterMap["UCU"] = "Ser";  threeLetterMap["UCC"] = "Ser";  threeLetterMap["UCA"] = "Ser";
  threeLetterMap["UCG"] = "Ser";  threeLetterMap["UAU"] = "Tyr";  threeLetterMap["UAC"] = "Tyr";
  threeLetterMap["UGU"] = "Cys";  threeLetterMap["UGC"] = "Cys";  threeLetterMap["UGG"] = "Trp";
  threeLetterMap["CUU"] = "Leu";  threeLetterMap["CUC"] = "Leu";  threeLetterMap["CUA"] = "Leu";
  threeLetterMap["CUG"] = "Leu";  threeLetterMap["CCU"] = "Pro";  threeLetterMap["CCC"] = "Pro";
  threeLetterMap["CCA"] = "Pro";  threeLetterMap["CCG"] = "Pro";  threeLetterMap["CAU"] = "His";
  threeLetterMap["CAC"] = "His";  threeLetterMap["CAA"] = "Gln";  threeLetterMap["CAG"] = "Gln";
  threeLetterMap["CGU"] = "Arg";  threeLetterMap["CGC"] = "Arg";  threeLetterMap["CGA"] = "Arg";
  threeLetterMap["CGG"] = "Arg";  threeLetterMap["AUU"] = "Ile";  threeLetterMap["AUC"] = "Ile";
  threeLetterMap["AUA"] = "Ile";  threeLetterMap["AUG"] = "Met";  threeLetterMap["ACU"] = "Thr";
  threeLetterMap["ACC"] = "Thr";  threeLetterMap["ACA"] = "Thr";  threeLetterMap["ACG"] = "Thr";  
  threeLetterMap["AAU"] = "Asn";  threeLetterMap["AAC"] = "Asn";  threeLetterMap["AAA"] = "Lys";
  threeLetterMap["AAG"] = "Lys";  threeLetterMap["AGU"] = "Ser";  threeLetterMap["AGC"] = "Ser";
  threeLetterMap["AGA"] = "Arg";  threeLetterMap["AGG"] = "Arg";  threeLetterMap["GUU"] = "Val";
  threeLetterMap["GUC"] = "Val";  threeLetterMap["GUA"] = "Val";  threeLetterMap["GUG"] = "Val";
  threeLetterMap["GCU"] = "Ala";  threeLetterMap["GCC"] = "Ala";  threeLetterMap["GCA"] = "Ala";
  threeLetterMap["GCG"] = "Ala";  threeLetterMap["GAU"] = "Asp";  threeLetterMap["GAC"] = "Asp";  
  threeLetterMap["GAA"] = "Glu";  threeLetterMap["GAG"] = "Glu";  threeLetterMap["GGU"] = "Gly";
  threeLetterMap["GGC"] = "Gly";  threeLetterMap["GGA"] = "Gly";  threeLetterMap["GGG"] = "Gly";
  
  return threeLetterMap;
}

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
  std::map<std::string, std::string> aminoAcidMap = CreateAminoAcidCodonMap();
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
  
  // create vector pointer
  std::shared_ptr<std::vector<DNA> > strandVectorPtr = std::make_shared<std::vector<DNA> >(strandVector);
  std::shared_ptr<std::map<std::string, std::string> > aminoAcidMapPtr = std::make_shared<std::map<std::string, std::string> >(aminoAcidMap);
  PrintReadingFrames(strandVector); // print reading frames
  TranscribeToRNA(strandVectorPtr); // transcribe reading frames to mRNA
  TranslateMRNAtoProtein(strandVectorPtr, aminoAcidMap); // translate mRNA to Protein
} // TranslateToProtein

// Find Open Reading Frames of strand to attempt translation to Protein
std::string FindOpenReadingFrame(std::shared_ptr<std::string> strand) {
  std::string openReadingFrame, possibleOpenReadingFrame;
  int size = strand->size();
  int pos = 0, endPos = 0, itr = 0; // dictates what i will be in next iteration
  int orfSize = 0, orfSize2 = 0; // keep track of reading frame size
  int count = 0;
  bool isAtgPresent = false;

  for (int i = 0; i < size && itr < size; i = itr) {
    std::string codon = strand->substr(i, 3);

    if (codon == "ATG") {
      if (count == 0) {
        pos = i;
        isAtgPresent = true;
      } // if
      count++;
    } // if

    if (codon == "TAA" || codon == "TAG" || codon == "TGA") {
      endPos = i;
      
      // if there was an ATG prior, get the sequence between the ATG and stop codon
      if (isAtgPresent) {
        std::cout << "Found Possible Open Reading Frame: ";
        possibleOpenReadingFrame = strand->substr(pos, endPos - pos + 3);
        
        orfSize = possibleOpenReadingFrame.size(); // keep track if largest reading frame

        if (orfSize > orfSize2)
          openReadingFrame = possibleOpenReadingFrame;

        orfSize2 = orfSize;
        std::cout << possibleOpenReadingFrame << std::endl;
        
        isAtgPresent = false; // reset reading frame finder
        count = 0;
      } // if
    } // if

    if (isAtgPresent)
      itr += 3; // increment by three if ATG present
    else // continue incrementing by one until an ATG is found
      itr++;

  } // for

  return openReadingFrame;
} // FindOpenReadingFrame()

void PrintReadingFrames(std::vector<DNA> strandVector) {
  std::cout << "\nFinal Open Reading Frame(s): ";
  
  int vectorIteration = 0;
  for (auto itr = strandVector.begin(); itr != strandVector.end(); itr++) {
    std::cout << itr->getSequence() << std::endl;
    // formatting purposes for showing multiple final open reading frames
    if (vectorIteration != strandVector.size() - 1)
      std::cout << "                             "; 
    
    vectorIteration++;
  } // for
} // PrintReadingFrames

// turn DNA to mRNA
void TranscribeToRNA(std::shared_ptr<std::vector<DNA> > strandVector) {
  for (auto itr = strandVector->begin(); itr != strandVector->end(); itr++) {
    itr->transcribeToRNA();
  } // for
} // TranscribeToRNA

// convert mRNA sequence to Protein sequence
void TranslateMRNAtoProtein(std::shared_ptr<std::vector<DNA> > strandVector, std::map<std::string, std::string> map) {
  int choice = 0; 
  for (auto itr = strandVector->begin(); itr != strandVector->end(); itr++) {
    std::cout << "Splice introns from mRNA sequence (1 - yes, 2 - no)\n> ";
    std::cin >> choice;
    std::shared_ptr<int> choicePtr = std::make_shared<int>(choice);
    CheckIfChoiceInRange(choicePtr);
    itr->translateMRNAToProtein(choice, map);
  } // for
} // TranslateMRNAtoProtein

// check if user inputs valid integer choice
// will need to check if input is indeed a number and not any other character
void CheckIfChoiceInRange(std::shared_ptr<int> choicePtr) {
  while (*choicePtr < 1 || *choicePtr > 2) {
    std::cout << "Invalid Option. Enter choice (1 - yes, 2 - no)\n> "; 
    std::cin >> *choicePtr;
  }
} // CheckIfChoiceInRange
