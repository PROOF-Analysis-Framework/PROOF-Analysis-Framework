///////////////////////////////////////////////////////////////////////
//
//    FILE: TCounterUI.C
//   CLASS: TCounterUI
// AUTHORS: I. Gonzalez Caballero, A.Y. Rodriguez Marrero
//    DATE: 2010
//
///////////////////////////////////////////////////////////////////////

#include "TCounterUI.h"
#include <iostream>

#if !defined(__CINT__)
ClassImp(TCounterUI);
#endif

Int_t TCounterUI::Merge(TCollection *li) {
  if (!li) 
    return 0;
  if (li->IsEmpty()) 
    return (Int_t) li->GetEntries();

  TIter next(li);
  TCounterUI* n = (TCounterUI*)next();
  while(n) {
    counter+=n->counter;
    n = (TCounterUI*)next();
  }

  return 0;
}

ostream& operator<<(ostream& os, const TCounterUI& c) {
  os << c.counter;
  return os;
}
