#pragma once

#include "TTree.h"
#include "TFile.h"

void PrintMessage(const char* message);
void PrintHelp();
void PrintVariable(const char* type, const char* name);
void PrintVariables(TTree* tree, const char* branchName);
TTree* GetTree(TFile* rootFile, const char* treeName);
TTree* GetAutoTree(TFile* rootFile);

int main(int argc, const char* argv[]);