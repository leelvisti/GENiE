#ifndef AUXILLIARY_H
#define AUXILLIARY_H

#include "gene.h"
#include <memory>
#include <vector>

void CreateTitleBanner();
std::map<std::string, std::string> CreateAminoAcidCodonMap();
void ProcessUserChoice(const unsigned int userChoice);
void DoDNAToProtein();
void DoProteinToDNA();
void TranslateToProtein(std::shared_ptr<std::string> strand1, std::shared_ptr<std::string> strand2);
std::string FindOpenReadingFrame(std::shared_ptr<std::string> strand);
void PrintReadingFrames(std::vector<DNA> strandVector);
void TranscribeToRNA(std::shared_ptr<std::vector<DNA> > strandVector);
void TranslateMRNAtoProtein(std::shared_ptr<std::vector<DNA> > strandVector, std::map<std::string, std::string> map);
void CheckIfChoiceInRange(std::shared_ptr<int> choicePtr);
#endif
