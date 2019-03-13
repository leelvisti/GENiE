#ifndef GENE_H
#define GENE_H

#include <iostream>
#include <string>
#include <cctype>
#include <regex>
#include <algorithm>
#include <map>
std::string reverseString(const std::string sequence_);

class DNA {
  std::string sequence;
  std::string reverseSequence;
  std::string mRNASequence;
public:
  DNA();
  void setSequence(std::string sequence_);
  void setRNASequence(std::string sequence_);
  std::string getSequence();
  std::string getReverseSequence();
  std::string getRNASequence();
  bool checkSequence(std::string sequence_);
  std::string CreateComplementaryStrand();
  void printSequence();
  void transcribeToRNA();
  void translateMRNAToProtein(int choice, std::map<std::string, std::string> map);
  void spliceIntrons();
  bool branchPointInIntronFound(const std::string strand);
}; // DNA class

#endif
