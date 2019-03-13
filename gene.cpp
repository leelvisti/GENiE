#include "gene.h"

DNA::DNA() :sequence(""), reverseSequence(""), mRNASequence("") {}

// set DNA sequence given a string
void DNA::setSequence(std::string sequence_) {
  std::string sequence_copy = sequence_;
  // check if sequence is valid
  bool isValidSequence = checkSequence(sequence_copy);
 
  while (!isValidSequence) {
    std::cout << "Invalid base found in sequence. Type DNA sequence 5\'- 3\'\n> ";
    std::cin >> sequence_copy;

    isValidSequence = checkSequence(sequence_copy);
  } // while

  // convert to upper case letters
  std::transform(sequence_copy.begin(), sequence_copy.end(), sequence_copy.begin(), ::toupper);
  // set dna sequence
  sequence = sequence_copy;
  // set reverse dna sequence
  reverseSequence = reverseString(sequence_copy);
} // setSequence()

void DNA::setRNASequence(std::string sequence_) {
  mRNASequence = sequence_;
}

// get DNA sequence
std::string DNA::getSequence() {
  return sequence;
}
  
// get reverse DNA sequence
std::string DNA::getReverseSequence() {
  return reverseSequence;
}

std::string DNA::getRNASequence() {
  return mRNASequence; 
}

// check to see if inputted sequence contains a,c,t, or g
bool DNA::checkSequence(std::string sequence_) {
  std::regex base("(a|c|t|g|A|G|T|C)*");
  
  for (int i = 0; i < sequence_.size(); i++) {
    if (!std::regex_match(sequence_, base))
      return false;
  }

  return true;
} // checkSequence

// create complementary pairs
std::string DNA::CreateComplementaryStrand() {
  std::string complentaryStrand;
  
  // A-T are complementary, C-G are complementary
  for (int i = 0; i < sequence.size(); i++) {
    if (sequence[i] == 'A')
      complentaryStrand.append("T");
    else if (sequence[i] == 'T')
      complentaryStrand.append("A");
    else if (sequence[i] == 'C')
      complentaryStrand.append("G");
    else if (sequence[i] == 'G')
      complentaryStrand.append("C");
  } // for

  return complentaryStrand;
} // CreateComplementaryStrand

void DNA::printSequence() {
  std::cout << sequence << std::endl;
  std::cout << reverseSequence << std::endl;
} // printSequence()

// reverse the given string
std::string reverseString(const std::string sequence_) {
  std::string copy = sequence_; // copy sequence
  int size = sequence_.size(); 

  // Swap character starting from two corners
  for (int i = 0; i < sequence_.size() / 2; i++) 
      std::swap(copy[i], copy[size - i - 1]);    
  
  return copy;
} // setReverseSequence()

// transcribe DNA strand to mRNA sequence
void DNA::transcribeToRNA() {
  mRNASequence = sequence;
  for (int i = 0; i < mRNASequence.size(); i++) {
    if (mRNASequence[i] == 'T')
      mRNASequence[i] = 'U';
  } // for
  
  std::cout << "mRNA sequence: " << mRNASequence << std::endl;
} // TranscribeToRNA

// translate mRNA to Protein
void DNA::translateMRNAToProtein(int choice, std::map<std::string, std::string> map) {
  if (choice == 1) 
    spliceIntrons(); 

  std::cout << "\nTranslating mRNA to Protein sequence...\n";
  std::cout << "   mRNA: " << mRNASequence << std::endl << "         ";
  for (unsigned int i = 9; i < mRNASequence.size() + 9; i += 3) {
    std::cout << " | ";
  } // for

  std::cout << std::endl << "Protein: ";
  // find the codon's corresponding amino acid
  for (unsigned int i = 0; i < mRNASequence.size(); i += 3) {
    std::string triplet = mRNASequence.substr(i,3);
    auto itr = map.find(triplet);
    // make sure itr found something in map
    if (itr != map.end())
      std::cout << itr->second;
    if (triplet == "UAG" || triplet == "UAA" || triplet == "UGA")
      std::cout << "STOP";
  } // for
  
  std::cout << std::endl;
} // translateMRNAToProtein

// splice introns from mRNA
void DNA::spliceIntrons() {
  int pos = 0, endPos = 0, count = 0, maxIntronSize = mRNASequence.size() - 6;
  std::string noStartStopCodinStrand = mRNASequence.substr(3, maxIntronSize); // just get the part of sequence with start and stop codon
  std::string intron, matureMRNA = "AUG";
  bool isGuPresent = false;
  std::cout << "\nFinding Introns from " << mRNASequence << std::endl;

  for (unsigned int i = 0; i < noStartStopCodinStrand.size(); i += 3) {
    std::string intronSite = noStartStopCodinStrand.substr(i,3);

    if (intronSite == "GUA" || intronSite == "GUU" || intronSite == "GUG" || intronSite == "GUC") {
      if (count == 0) {
        pos = i;
        isGuPresent = true;
      } // if finding first intorn site
      
      count++;
    } // if
    // add intron site to mature mRNA sequence
    if (!isGuPresent)
      matureMRNA.append(intronSite);

    if (intronSite == "AAG" || intronSite == "UAG" || intronSite == "GAG" || intronSite == "CAG") {
      endPos = i;
      // if start of intron was found
      if (isGuPresent) {
        intron = noStartStopCodinStrand.substr(pos, endPos - pos + 3);

        if (branchPointInIntronFound(intron)) {
          std::cout << "Found intron: " << intron << std::endl;
          isGuPresent = false;
          count = 0;
        } // if
      } // if start of intron was found
    } // if
  } // for
  
  matureMRNA.append(mRNASequence.substr(mRNASequence.size() - 3, 3));
  mRNASequence = matureMRNA;
  std::cout << "Splicing Introns...\nMature mRNA: " << mRNASequence << std::endl;;

} // spliceIntrons

bool DNA::branchPointInIntronFound(const std::string strand) {
  for (unsigned int i = 2; i < strand.size() - 2; i++)
    if (strand[i] == 'A')
      return true;

  return false;
} // branchPointInIntronFound
