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
      Translation();
      break;
    // translate protein to DNA;
    case 2:
      BackTranslation();
      break;
    // exit program;
    default:
      std::cout << "Exiting GENiE\n";
      break;
  }
} // processUserChoice

void Translation() {
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

} // Translation

// Translating Protein back to DNA sequence
void BackTranslation() {
  std::string sequence, sequence_copy, aminoAcid;
  bool notValidChoice = false, invalidAminoAcid = false;;
  // prompt user for sequence input
  std::cout << "Input Protein sequence using single-letter Amino Acid code\n> ";
  std::cin >> sequence;
  
  sequence_copy = sequence; // just for safety
  // convert sequence to uppercase letters
  std::transform(sequence_copy.begin(), sequence_copy.end(), sequence_copy.begin(), ::toupper);
  sequence = sequence_copy; // assign back
  
  // check if sequence contains invalid amino acids
  for (auto itr = sequence.begin(); itr != sequence.end(); itr++) {
    aminoAcid = *itr;
    // if amino acid is invalid, exit program
    if (aminoAcid == "J" || aminoAcid == "B" || aminoAcid == "U" || aminoAcid == "0" || 
        aminoAcid == "X" || aminoAcid == "Z" || isdigit(*itr)) {
      std::cout << "Invalid Amino Acid found: " << aminoAcid << std::endl;
      invalidAminoAcid = true;
    } // if 
  } // for

  // if invalid amino acid code found, exit GENiE
  if (invalidAminoAcid) {
    std::cout << "Exiting GENiE\n";
    exit(EXIT_FAILURE);
  } // if
  
  std::shared_ptr<std::string> sequencePtr = std::make_shared<std::string>(sequence);
  BackTranslationSpeciesMenu(sequencePtr);
} // BackTranslation

void BackTranslationSpeciesMenu(std::shared_ptr<std::string> sequencePtr) {
  int choice = 0;
  bool notValidChoice = false;
  std::multimap<std::string, std::string> codonMap;  
  std::map<std::string, double> eColiMap, drosoMap, yeastMap; // store frequency maps for each species  
  // initialize maps for each species
  std::shared_ptr<std::map<std::string, double> > eColiMapPtr = std::make_shared<std::map<std::string, double> >(eColiMap);
  std::shared_ptr<std::map<std::string, double> > drosoMapPtr = std::make_shared<std::map<std::string, double> >(drosoMap);
  std::shared_ptr<std::map<std::string, double> > yeastMapPtr = std::make_shared<std::map<std::string, double> >(yeastMap);
  std::shared_ptr<std::multimap<std::string, std::string> > codonMapPtr = std::make_shared<std::multimap<std::string, std::string> >(codonMap);
  // set keys and values to each map 
  codonMapPtr = initializeCodonMap(codonMapPtr);  
  eColiMapPtr = initializeEColiMap(eColiMapPtr); 
  drosoMapPtr = initializeDrosoMap(drosoMapPtr);
  yeastMapPtr = initializeYeastMap(yeastMapPtr); 
  
  std::cout << "Choose organism to Back Translate Protein:\n" << 
    "1) Escherichia coli (E. coli)\n" <<
    "2) Drosophila melanogaster (Fruit Fly)\n" <<
    "3) Saccharomyces cerevisiae (Yeast)\n> ";
  
  std::cin >> choice;
  notValidChoice = (std::cin.fail() || choice < 1 || choice > 3) ? true : false;
 
  while (notValidChoice) {
    std::cout << "Invalid choice. Enter (1,2,or 3):\n> ";
    std::cin >> choice;
    // check if valid now
    notValidChoice = (std::cin.fail() || choice < 1 || choice > 3) ? true : false;
    std::cin.clear(); // clear input
    std::cin.ignore(256,'\n'); // clear stream
  } // while

  std::shared_ptr<int> choicePtr = std::make_shared<int>(choice);

  if (choice == 1)
    TranslateProteinToDNA(codonMapPtr, eColiMapPtr, sequencePtr);
  else if (choice == 2)
    TranslateProteinToDNA(codonMapPtr, drosoMapPtr, sequencePtr);
  else
    TranslateProteinToDNA(codonMapPtr, yeastMapPtr, sequencePtr);
} // BackTranslationSpeciesMenu

std::shared_ptr<std::multimap<std::string, std::string> > initializeCodonMap(std::shared_ptr<std::multimap<std::string, std::string> > codonMap) {
  codonMap->insert(std::pair<std::string, std::string>("F", "UUU"));  codonMap->insert(std::pair<std::string, std::string>("F", "UUC"));  codonMap->insert(std::pair<std::string, std::string>("L", "UUA"));
  codonMap->insert(std::pair<std::string, std::string>("L", "UUG"));  codonMap->insert(std::pair<std::string, std::string>("L", "CUU"));  codonMap->insert(std::pair<std::string, std::string>("L", "CUC"));
  codonMap->insert(std::pair<std::string, std::string>("L", "CUA"));  codonMap->insert(std::pair<std::string, std::string>("L", "CUG"));  codonMap->insert(std::pair<std::string, std::string>("I", "AUU"));
  codonMap->insert(std::pair<std::string, std::string>("I", "AUC"));  codonMap->insert(std::pair<std::string, std::string>("I", "AUA"));  codonMap->insert(std::pair<std::string, std::string>("M", "AUG"));
  codonMap->insert(std::pair<std::string, std::string>("V", "GUU"));  codonMap->insert(std::pair<std::string, std::string>("V", "GUC"));  codonMap->insert(std::pair<std::string, std::string>("V", "GUA"));
  codonMap->insert(std::pair<std::string, std::string>("V", "GUG"));  codonMap->insert(std::pair<std::string, std::string>("S", "UCU"));  codonMap->insert(std::pair<std::string, std::string>("S", "UCC"));
  codonMap->insert(std::pair<std::string, std::string>("S", "UCA"));  codonMap->insert(std::pair<std::string, std::string>("S", "UCG"));  codonMap->insert(std::pair<std::string, std::string>("P", "CCU"));
  codonMap->insert(std::pair<std::string, std::string>("P", "CCC"));  codonMap->insert(std::pair<std::string, std::string>("P", "CCA"));  codonMap->insert(std::pair<std::string, std::string>("P", "CCG"));
  codonMap->insert(std::pair<std::string, std::string>("T", "ACU"));  codonMap->insert(std::pair<std::string, std::string>("T", "ACC"));  codonMap->insert(std::pair<std::string, std::string>("T", "ACA"));
  codonMap->insert(std::pair<std::string, std::string>("T", "ACG"));  codonMap->insert(std::pair<std::string, std::string>("A", "GCU"));  codonMap->insert(std::pair<std::string, std::string>("A", "GCA"));
  codonMap->insert(std::pair<std::string, std::string>("A", "GCC"));  codonMap->insert(std::pair<std::string, std::string>("A", "GCG"));  codonMap->insert(std::pair<std::string, std::string>("Y", "UAU"));
  codonMap->insert(std::pair<std::string, std::string>("Y", "UAC"));  codonMap->insert(std::pair<std::string, std::string>("H", "CAU"));  codonMap->insert(std::pair<std::string, std::string>("H", "CAC"));
  codonMap->insert(std::pair<std::string, std::string>("Q", "CAA"));  codonMap->insert(std::pair<std::string, std::string>("Q", "CAG"));  codonMap->insert(std::pair<std::string, std::string>("N", "AAU"));
  codonMap->insert(std::pair<std::string, std::string>("N", "AAC"));  codonMap->insert(std::pair<std::string, std::string>("K", "AAA"));  codonMap->insert(std::pair<std::string, std::string>("K", "AAG"));
  codonMap->insert(std::pair<std::string, std::string>("D", "GAU"));  codonMap->insert(std::pair<std::string, std::string>("D", "GAC"));  codonMap->insert(std::pair<std::string, std::string>("E", "GAA"));
  codonMap->insert(std::pair<std::string, std::string>("E", "GAG"));  codonMap->insert(std::pair<std::string, std::string>("C", "UGU"));  codonMap->insert(std::pair<std::string, std::string>("C", "UGC"));
  codonMap->insert(std::pair<std::string, std::string>("W", "UGG"));  codonMap->insert(std::pair<std::string, std::string>("R", "CGU"));  codonMap->insert(std::pair<std::string, std::string>("R", "CGC"));
  codonMap->insert(std::pair<std::string, std::string>("R", "CGA"));  codonMap->insert(std::pair<std::string, std::string>("R", "CGG"));  codonMap->insert(std::pair<std::string, std::string>("S", "AGU"));
  codonMap->insert(std::pair<std::string, std::string>("S", "AGC"));  codonMap->insert(std::pair<std::string, std::string>("R", "AGA"));  codonMap->insert(std::pair<std::string, std::string>("R", "AGG"));
  codonMap->insert(std::pair<std::string, std::string>("G", "GGU"));  codonMap->insert(std::pair<std::string, std::string>("G", "GGC"));  codonMap->insert(std::pair<std::string, std::string>("G", "GGA"));
  codonMap->insert(std::pair<std::string, std::string>("G", "GGG"));  codonMap->insert(std::pair<std::string, std::string>("STOP", "TAA"));  codonMap->insert(std::pair<std::string, std::string>("STOP", "TAG"));
  codonMap->insert(std::pair<std::string, std::string>("STOP", "TGA"));

  return codonMap;
} // initializeCodonMap

std::shared_ptr<std::map<std::string, double> > initializeEColiMap(std::shared_ptr<std::map<std::string, double> > eColiMap) {
  (*eColiMap)["UUU"] = 0.58;  (*eColiMap)["UUC"] = 0.42;  (*eColiMap)["UUA"] = 0.14;
  (*eColiMap)["UUG"] = 0.13;  (*eColiMap)["UCU"] = 0.17;  (*eColiMap)["UCC"] = 0.15;
  (*eColiMap)["UCA"] = 0.14;  (*eColiMap)["UCG"] = 0.14;  (*eColiMap)["UAU"] = 0.59;
  (*eColiMap)["UAC"] = 0.41;  (*eColiMap)["UGU"] = 0.46;  (*eColiMap)["UGC"] = 0.54;
  (*eColiMap)["UGG"] = 1.0;  (*eColiMap)["CUU"] = 0.12;  (*eColiMap)["CUC"] = 0.10;
  (*eColiMap)["CUA"] = 0.04;  (*eColiMap)["CUG"] = 0.47;  (*eColiMap)["CCU"] = 0.18;
  (*eColiMap)["CCC"] = 0.13;  (*eColiMap)["CCA"] = 0.20;  (*eColiMap)["CCG"] = 0.49;
  (*eColiMap)["CAU"] = 0.57;  (*eColiMap)["CAC"] = 0.43;  (*eColiMap)["CAA"] = 0.34;
  (*eColiMap)["CAG"] = 0.66;  (*eColiMap)["CGU"] = 0.36;  (*eColiMap)["CGC"] = 0.36;
  (*eColiMap)["CGA"] = 0.07;  (*eColiMap)["CGG"] = 0.11;  (*eColiMap)["AUU"] = 0.49;
  (*eColiMap)["AUC"] = 0.39;  (*eColiMap)["AUA"] = 0.11;  (*eColiMap)["AUG"] = 1.0;
  (*eColiMap)["ACU"] = 0.19;  (*eColiMap)["ACC"] = 0.40;  (*eColiMap)["ACA"] = 0.17;
  (*eColiMap)["ACG"] = 0.25;  (*eColiMap)["AAU"] = 0.49;  (*eColiMap)["AAC"] = 0.51;
  (*eColiMap)["AAA"] = 0.74;  (*eColiMap)["AAG"] = 0.26;  (*eColiMap)["AGU"] = 0.16;
  (*eColiMap)["AGC"] = 0.25;  (*eColiMap)["AGA"] = 0.07;  (*eColiMap)["AGG"] = 0.04;
  (*eColiMap)["GUU"] = 0.28;  (*eColiMap)["GUC"] = 0.20;  (*eColiMap)["GUA"] = 0.17;
  (*eColiMap)["GUG"] = 0.35;  (*eColiMap)["GCU"] = 0.18;  (*eColiMap)["GCC"] = 0.26;
  (*eColiMap)["GCA"] = 0.23;  (*eColiMap)["GCG"] = 0.33;  (*eColiMap)["GAU"] = 0.63;
  (*eColiMap)["GAC"] = 0.37;  (*eColiMap)["GAA"] = 0.68;  (*eColiMap)["GAG"] = 0.32;
  (*eColiMap)["GGU"] = 0.35;  (*eColiMap)["GGC"] = 0.37;  (*eColiMap)["GGA"] = 0.13;
  (*eColiMap)["GGG"] = 0.15;  (*eColiMap)["TAG"] = 0.09;  (*eColiMap)["TAA"] = 0.61;
  (*eColiMap)["TGA"] = 0.30;

  return eColiMap;
} // initializeEColiMap

std::shared_ptr<std::map<std::string, double> > initializeDrosoMap(std::shared_ptr<std::map<std::string, double> > drosoMap) {
  (*drosoMap)["UUU"] = 0.37;  (*drosoMap)["UUC"] = 0.63;  (*drosoMap)["UUA"] = 0.05;
  (*drosoMap)["UUG"] = 0.18;  (*drosoMap)["UCU"] = 0.08;  (*drosoMap)["UCC"] = 0.24;
  (*drosoMap)["UCA"] = 0.09;  (*drosoMap)["UCG"] = 0.20;  (*drosoMap)["UAU"] = 0.37;
  (*drosoMap)["UAC"] = 0.63;  (*drosoMap)["UGU"] = 0.29;  (*drosoMap)["UGC"] = 0.71;
  (*drosoMap)["UGG"] = 1.00;  (*drosoMap)["CUU"] = 0.10;  (*drosoMap)["CUC"] = 0.15;
  (*drosoMap)["CUA"] = 0.09;  (*drosoMap)["CUG"] = 0.43;  (*drosoMap)["CCU"] = 0.13;
  (*drosoMap)["CCC"] = 0.33;  (*drosoMap)["CCA"] = 0.25;  (*drosoMap)["CCG"] = 0.29;
  (*drosoMap)["CAU"] = 0.40;  (*drosoMap)["CAC"] = 0.60;  (*drosoMap)["CAA"] = 0.30;
  (*drosoMap)["CAG"] = 0.70;  (*drosoMap)["CGU"] = 0.16;  (*drosoMap)["CGC"] = 0.33;
  (*drosoMap)["CGA"] = 0.15;  (*drosoMap)["CGG"] = 0.15;  (*drosoMap)["AUU"] = 0.34;
  (*drosoMap)["AUC"] = 0.47;  (*drosoMap)["AUA"] = 0.19;  (*drosoMap)["AUG"] = 1.0;
  (*drosoMap)["ACU"] = 0.17;  (*drosoMap)["ACC"] = 0.38;  (*drosoMap)["ACA"] = 0.19;
  (*drosoMap)["ACG"] = 0.26;  (*drosoMap)["AAU"] = 0.44;  (*drosoMap)["AAC"] = 0.56;
  (*drosoMap)["AAA"] = 0.29;  (*drosoMap)["AAG"] = 0.71;  (*drosoMap)["AGU"] = 0.14;
  (*drosoMap)["AGC"] = 0.25;  (*drosoMap)["AGA"] = 0.09;  (*drosoMap)["AGG"] = 0.11;
  (*drosoMap)["GUU"] = 0.18;  (*drosoMap)["GUC"] = 0.24;  (*drosoMap)["GUA"] = 0.11;
  (*drosoMap)["GUG"] = 0.47;  (*drosoMap)["GCU"] = 0.19;  (*drosoMap)["GCC"] = 0.45;
  (*drosoMap)["GCA"] = 0.17;  (*drosoMap)["GCG"] = 0.19;  (*drosoMap)["GAU"] = 0.53;
  (*drosoMap)["GAC"] = 0.47;  (*drosoMap)["GAA"] = 0.33;  (*drosoMap)["GAG"] = 0.67;
  (*drosoMap)["GGU"] = 0.21;  (*drosoMap)["GGC"] = 0.43;  (*drosoMap)["GGA"] = 0.29;
  (*drosoMap)["GGG"] = 0.07;  (*drosoMap)["TAA"] = 0.42;  (*drosoMap)["TAG"] = 0.32;
  (*drosoMap)["TGA"] = 0.26;

  return drosoMap;
} // initializeDrosoMap

std::shared_ptr<std::map<std::string, double> > initializeYeastMap(std::shared_ptr<std::map<std::string, double> > yeastMap) {
  (*yeastMap)["UUU"] = 0.59;  (*yeastMap)["UUC"] = 0.41;  (*yeastMap)["UUA"] = 0.28;
  (*yeastMap)["UUG"] = 0.29;  (*yeastMap)["UCU"] = 0.26;  (*yeastMap)["UCC"] = 0.16;
  (*yeastMap)["UCA"] = 0.21;  (*yeastMap)["UCG"] = 0.10;  (*yeastMap)["UAU"] = 0.56;
  (*yeastMap)["UAC"] = 0.44;  (*yeastMap)["UGU"] = 0.63;  (*yeastMap)["UGC"] = 0.37;
  (*yeastMap)["UGG"] = 1.0;  (*yeastMap)["CUU"] = 0.13;  (*yeastMap)["CUC"] = 0.06;
  (*yeastMap)["CUA"] = 0.14;  (*yeastMap)["CUG"] = 0.11;  (*yeastMap)["CCU"] = 0.31;
  (*yeastMap)["CCC"] = 0.15;  (*yeastMap)["CCA"] = 0.41;  (*yeastMap)["CCG"] = 0.12;
  (*yeastMap)["CAU"] = 0.64;  (*yeastMap)["CAC"] = 0.36;  (*yeastMap)["CAA"] = 0.69;
  (*yeastMap)["CAG"] = 0.31;  (*yeastMap)["CGU"] = 0.15;  (*yeastMap)["CGC"] = 0.06;
  (*yeastMap)["CGA"] = 0.07;  (*yeastMap)["CGG"] = 0.04;  (*yeastMap)["AUU"] = 0.46;
  (*yeastMap)["AUC"] = 0.26;  (*yeastMap)["AUA"] = 0.27;  (*yeastMap)["AUG"] = 1.0;
  (*yeastMap)["ACU"] = 0.35;  (*yeastMap)["ACC"] = 0.22;  (*yeastMap)["ACA"] = 0.30;
  (*yeastMap)["ACG"] = 0.13;  (*yeastMap)["AAU"] = 0.59;  (*yeastMap)["AAC"] = 0.41;
  (*yeastMap)["AAA"] = 0.58;  (*yeastMap)["AAG"] = 0.42;  (*yeastMap)["AGU"] = 0.16;
  (*yeastMap)["AGC"] = 0.11;  (*yeastMap)["AGA"] = 0.48;  (*yeastMap)["AGG"] = 0.21;
  (*yeastMap)["GUU"] = 0.39;  (*yeastMap)["GUC"] = 0.21;  (*yeastMap)["GUA"] = 0.21;
  (*yeastMap)["GUG"] = 0.19;  (*yeastMap)["GCU"] = 0.38;  (*yeastMap)["GCC"] = 0.22;
  (*yeastMap)["GCA"] = 0.29;  (*yeastMap)["GCG"] = 0.11;  (*yeastMap)["GAU"] = 0.65;
  (*yeastMap)["GAC"] = 0.35;  (*yeastMap)["GAA"] = 0.71;  (*yeastMap)["GAG"] = 0.29;
  (*yeastMap)["GGU"] = 0.47;  (*yeastMap)["GGC"] = 0.19;  (*yeastMap)["GGA"] = 0.22;
  (*yeastMap)["GGG"] = 0.12;  (*yeastMap)["TAA"] = 0.48;  (*yeastMap)["TAG"] = 0.24;
  (*yeastMap)["TGA"] = 0.29;

  return yeastMap;
} // initializeYeastMap

// Begin to translate protein back to DNA
void TranslateProteinToDNA(std::shared_ptr<std::multimap<std::string, std::string> > codonMapPtr, 
    std::shared_ptr<std::map<std::string, double> > frequencyMapPtr, std::shared_ptr<std::string> sequencePtr) {
  std::string aminoAcid, codon, highestFrequencyCodon, rnaSequence, dnaSequence;
  std::multimap<double, std::string> mostProbableCodon; // stores frequency of codons per amino acids to find the most probable
  
  // display chart
  std::cout << "Amino Acid: " << std::setw(20) << "Codons: " << 
    std::setw(20) << "Frequency" << std::endl;
  
  for (unsigned int i = 0; i < sequencePtr->size(); i++) {
    int codonCount = 0;
    aminoAcid = (*sequencePtr)[i];

    std::cout << std::left << std::setw(24) << std::setfill(' ') << aminoAcid;

    auto codonMapItr = codonMapPtr->find(aminoAcid); // find amino acid inside codonMap
    int numberOfCodons = codonMapPtr->count(aminoAcid); // check to see if amino acid has multiple codons that make it

    for (unsigned int j = 0; j < numberOfCodons; j++) {
      codonCount++; // keep track of numbers of codons for amino acid
      codon = codonMapItr->second; // set to codon of amino acid
      auto frequencyMapItr = frequencyMapPtr->find(codon); // find frequency of codon
     
      // if theres only one codon that makes amino acid
      // this is more for displaying correctly to table
      if (codonCount == 1)
        std::cout << std::left << std::setw(18) << std::setfill(' ') << frequencyMapItr->first;
      else // codonCount > 1
        std::cout  << "                        " << std::left << std::setw(18) << frequencyMapItr->first;

      std::cout << frequencyMapItr->second << std::endl;
      mostProbableCodon.insert(std::pair<double, std::string>(frequencyMapItr->second, frequencyMapItr->first));
      std::shared_ptr<std::multimap<double, std::string> > mostProbableCodonPtr = std::make_shared<std::multimap<double, std::string> >(mostProbableCodon);
      highestFrequencyCodon = FindMaxFrequencyCodon(mostProbableCodonPtr);
      ++codonMapItr;
    } // for

    rnaSequence.append(highestFrequencyCodon); // append most probably codon for its respected amino acid
    mostProbableCodon.clear(); // clear map for next amino acid
  } // for

  // STOP codon appended
  auto frequencyMapItr = frequencyMapPtr->find("STOP");
  mostProbableCodon.insert(std::pair<double, std::string>(frequencyMapItr->second, frequencyMapItr->first));
  std::shared_ptr<std::multimap<double, std::string> > mostProbableCodonPtr = std::make_shared<std::multimap<double, std::string> >(mostProbableCodon);
  highestFrequencyCodon = FindMaxFrequencyCodon(mostProbableCodonPtr); // find the most probable codon of STOP codon
  rnaSequence.append(highestFrequencyCodon);

  dnaSequence = transcribeRNAToDNA(rnaSequence);
  std::cout << "Protein:  " << sequencePtr->append("[STOP]") << " -> RNA: " << rnaSequence << " -> DNA: " << dnaSequence << std::endl;
  
} // TranslateProteinToDNA

std::string FindMaxFrequencyCodon(std::shared_ptr<std::multimap<double, std::string> > mostProbableCodonPtr) {
  double temp = 0.0;
  std::string codon;
  
  for (auto itr = mostProbableCodonPtr->begin(); itr != mostProbableCodonPtr->end(); itr++) {
    if (itr->first == 1.0) {
      codon = itr->second;
      temp = 0.0;
    } // if
    else if (itr->first > temp) {
      codon = itr->second;
      temp = itr->first;
    } // else frequency is larger
  } // for

  return codon;
} // FindMaxFrequencyCodon

std::string transcribeRNAToDNA(const std::string rnaSequence) {
  std::string dnaSequence = rnaSequence;
  for (unsigned int i = 0; i < dnaSequence.size(); i++) {
    if (dnaSequence[i] == 'U')
      dnaSequence[i] = 'T';
  } // for

  return dnaSequence;
} // transcribeRNAToDNA

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
  if (openReadingFrame1.size() == 0) {  
    std::cout << "No Open Reading Frame found for DNA template strand\nExiting GENiE\n";
  }
  else
    std::cout << std::endl;  
  DNA templateDNA;
  
  templateDNA.setSequence(openReadingFrame1);

  // DNA complementary 
  std::cout << "Attempting to find reading frames from DNA complementary strand...\n";
  openReadingFrame2 = FindOpenReadingFrame(strand2);
  if (openReadingFrame2.size() == 0) {  
    std::cout << "No Open Reading Frame found for DNA complementary strand\nExiting GENiE\n";
  }
  else
    std::cout << std::endl;  
  
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
