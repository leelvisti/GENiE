#ifndef AUXILLIARY_H
#define AUXILLIARY_H

#include "gene.h"
#include <memory>
#include <vector>

void CreateTitleBanner();
void ProcessUserChoice(const unsigned int userChoice);
void DoDNAToProtein();
void DoProteinToDNA();
void TranslateToProtein(std::shared_ptr<std::string> strand1, std::shared_ptr<std::string> strand2);
std::string FindOpenReadingFrame(std::shared_ptr<std::string> strand);
void FindStartCodon(std::shared_ptr<int> count, std::shared_ptr<std::string> codon, std::shared_ptr<bool> isATGPresent,
    std::shared_ptr<int> pos, std::shared_ptr<int> i);
void FindStopCodon(std::shared_ptr<std::string> strand, std::shared_ptr<int> count, std::shared_ptr<std::string> codon, std::shared_ptr<bool> isATGPresent,
    std::shared_ptr<int> pos, std::shared_ptr<int> endPos, std::shared_ptr<int> i, std::shared_ptr<std::string> openReadingFrame);
void PrintReadingFrames(std::vector<DNA> strandVector);
void TranscribeToRNA(std::vector<DNA> strandVector);
#endif
