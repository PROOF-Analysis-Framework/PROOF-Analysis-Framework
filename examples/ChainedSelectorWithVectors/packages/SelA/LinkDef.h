/* This file is only needed if selectors are chained and they need to pass
   around objects of classes different from the basic types.
   In that situation we need to generate a few dictionaries. In principle it is
   enough to have PAFGenericItemVariableContainer<myclass>
*/
#ifdef __CLING__

// Since we are passing a TLorentzVector as a parameter we need this. 
// In addition we need to include "TLorentzVector.h" in the header file
// of the selector
#pragma link C++ class PAFGenericItemVariableContainer<TLorentzVector>+;

// Since we are passing a std::vector<TLorentzVector> as a parameter we 
// need this.
// In addition we need to include "TLorentzVector.h" (should be already
// included for the reason described above) and <vector> in the header file
// of the selector
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<TLorentzVector>>+;

// Finally we need to manually tell ROOT to generate the dictionary for the 
// selector class SelA. If LinkDef.h is not present this dictionary is 
// automatically generated.
#pragma link C++ class SelA+;


#endif
