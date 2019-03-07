#ifndef GENE_H
#define GENE_H

#include <iostream>
#include <string>
#include <cctype>
#include <regex>
#include <algorithm>

std::string reverseString(const std::string sequence_);

class DNA {
  std::string sequence;
  std::string reverseSequence;

public:
  // set DNA sequence given a string
  void setSequence(std::string sequence_) {
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

  // get DNA sequence
  std::string getSequence() {
    return sequence;
  }
    
  // get reverse DNA sequence
  std::string getReverseSequence() {
    return reverseSequence;
  }

  // check to see if inputted sequence contains a,c,t, or g
  bool checkSequence(std::string sequence_) {
    std::regex base("(a|c|t|g|A|G|T|C)*");
    
    for (int i = 0; i < sequence_.size(); i++) {
      if (!std::regex_match(sequence_, base))
        return false;
    }

    return true;
  } // checkSequence

  // create complementary pairs
  std::string CreateComplementaryStrand() {
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

  void printSequence() {
    std::cout << sequence << std::endl;
    std::cout << reverseSequence << std::endl;
  } // printSequence()
}; // DNA class

// reverse the given string
std::string reverseString(const std::string sequence_) {
  std::string copy = sequence_; // copy sequence
  int size = sequence_.size(); 

  // Swap character starting from two corners
  for (int i = 0; i < sequence_.size() / 2; i++) 
      std::swap(copy[i], copy[size - i - 1]);    
  
  return copy;
} // setReverseSequence()
#endif
