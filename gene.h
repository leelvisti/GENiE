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
  std::string mRNASequence;
public:
  void setSequence(std::string sequence_);
  std::string getSequence();
  std::string getReverseSequence();
  bool checkSequence(std::string sequence_);
  std::string CreateComplementaryStrand();
  void printSequence();
  void transcribeToRNA();
}; // DNA class

#endif
