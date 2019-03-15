#ifndef AUXILLIARY_H
#define AUXILLIARY_H

#include "gene.h"
#include <memory>
#include <vector>

void CreateTitleBanner();
std::map<std::string, std::string> CreateAminoAcidCodonMap();
void ProcessUserChoice(const unsigned int userChoice);
void Translation();
void BackTranslation();
void BackTranslationSpeciesMenu(std::shared_ptr<std::string> sequencePtr);
void TranslateProteinToDNA(std::shared_ptr<std::multimap<std::string, std::string> > codonMapPtr, std::shared_ptr<std::map<std::string, double> > frequencyMapPtr, std::shared_ptr<std::string> sequencePtr);
std::shared_ptr<std::multimap<std::string, std::string> > initializeCodonMap(std::shared_ptr<std::multimap<std::string, std::string> > codonMap);
std::shared_ptr<std::map<std::string, double> > initializeEColiMap(std::shared_ptr<std::map<std::string, double> > eColiMap);
std::shared_ptr<std::map<std::string, double> > initializeDrosoMap(std::shared_ptr<std::map<std::string, double> > drosoMap);
std::shared_ptr<std::map<std::string, double> > initializeYeastMap(std::shared_ptr<std::map<std::string, double> > yeastMap);
void DoProteinToDNA();
void TranslateToProtein(std::shared_ptr<std::string> strand1, std::shared_ptr<std::string> strand2);
std::string FindOpenReadingFrame(std::shared_ptr<std::string> strand);
void PrintReadingFrames(std::vector<DNA> strandVector);
void TranscribeToRNA(std::shared_ptr<std::vector<DNA> > strandVector);
void TranslateMRNAtoProtein(std::shared_ptr<std::vector<DNA> > strandVector, std::map<std::string, std::string> map);
void CheckIfChoiceInRange(std::shared_ptr<int> choicePtr);
#endif
