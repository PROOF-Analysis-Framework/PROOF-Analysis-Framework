///////////////////////////////////////////////////////////////////////
//
//    FILE: TCounterUI.h
//   CLASS: TCounterUI
// AUTHORS: I. Gonzalez Caballero, A.Y. Rodriguez Marrero
//    DATE: 2010
//
// CONTENT: This is a class that can be used to count things in a
//          PROOF environment. It should behave in most cases as an
//          unsigned int
//
///////////////////////////////////////////////////////////////////////

#ifndef TCounterUI_h
#define TCounterUI_h 1

#include <TNamed.h>
#include <TCollection.h>

class TCounterUI: public TNamed {

  friend ostream& operator<<(ostream&, const TCounterUI&);

 public:
  //  TCounterUI(unsigned int c = 0):counter(c) {}
  TCounterUI(const char* name="", const char* title="", 
	     unsigned int c = 0):TNamed(name,title),counter(c) {}
  ~TCounterUI() {}

  void Increment(unsigned int inc=1) {counter+=inc;}
  void SetValue(unsigned int c = 0) {counter = c;}
  unsigned int GetValue() const {return counter;}

  // Used by Proof in the merging
  Int_t Merge(TCollection *li);

  //Operators
  /*
    unsigned int operator+(const TCounterUI& c) const {return counter+c.counter;}
    int operator-(const TCounterUI& c) const {return counter-c.counter;}
    unsigned int operator*(const TCounterUI& c) const {return counter*c.counter;}
    unsigned int operator/(const TCounterUI& c) const {return counter/c.counter;}}
  */
  unsigned int operator++() {return ++counter;}
  unsigned int operator++(int) {return (counter++);}
  unsigned int operator--() {return --counter;}
  unsigned int operator--(int) {return (counter--);}
  unsigned int operator+=(unsigned int c) {return counter+=c;}
  unsigned int operator-=(unsigned int c) {return counter+=c;}
  unsigned int operator+=(int c) {return counter+=c;}
  unsigned int operator-=(int c) {return counter+=c;}
  bool operator==(unsigned int c) const {return (counter==c);}
  bool operator!=(unsigned int c) const {return (counter!=c);}

  operator unsigned int() {return counter;}

 protected:
  unsigned int counter;

  ClassDef(TCounterUI,1);
};


// Operators with unsigned ints
inline unsigned int operator+(unsigned int c, const TCounterUI& counter) {
  return counter.GetValue()+c;
}
inline unsigned int operator+(const TCounterUI& counter, unsigned int c) {
  return counter.GetValue()+c;
}
inline int operator-(unsigned int c, const TCounterUI& counter) {
  return c-counter.GetValue();
}
inline int operator-(const TCounterUI& counter, unsigned int c) {
  return counter.GetValue()-c;
}
inline unsigned int operator*(unsigned int c, const TCounterUI& counter) {
  return counter.GetValue()*c;
}
inline unsigned int operator*(const TCounterUI& counter, unsigned int c) {
  return counter.GetValue()*c;
}
inline unsigned int operator/(unsigned int c, const TCounterUI& counter) {
  return c/counter.GetValue();
}
inline unsigned int operator/(const TCounterUI& counter, unsigned int c) {
  return counter.GetValue()/c;
}

// Operators with ints
inline unsigned int operator+(int c, const TCounterUI& counter) {
  return counter.GetValue()+c;
}
inline unsigned int operator+(const TCounterUI& counter, int c) {
  return counter.GetValue()+c;
}
inline int operator-(int c, const TCounterUI& counter) {
  return c - counter.GetValue();
}
inline int operator-(const TCounterUI& counter, int c) {
  return counter.GetValue() - c;
}
inline unsigned int operator*(int c, const TCounterUI& counter) {
  return counter.GetValue()*c;
}
inline unsigned int operator*(const TCounterUI& counter, int c) {
  return counter.GetValue()*c;
}
inline unsigned int operator/(int c, const TCounterUI& counter) {
  return c/counter.GetValue();
}
inline unsigned int operator/(const TCounterUI& counter, int c) {
  return counter.GetValue()/c;
}


//Operators with doubles
inline double operator+(double c, const TCounterUI& counter) {
  return counter.GetValue()+c;
}
inline double operator+(const TCounterUI& counter, double c) {
  return counter.GetValue()+c;
}
inline double operator-(double c, const TCounterUI& counter) {
  return c - counter.GetValue();
}
inline double operator-(const TCounterUI& counter, double c) {
  return counter.GetValue() - c;
}
inline double operator*(double c, const TCounterUI& counter) {
  return counter.GetValue()*c;
}
inline double operator*(const TCounterUI& counter, double c) {
  return counter.GetValue()*c;
}
inline double operator/(double c, const TCounterUI& counter) {
  return c/counter.GetValue();
}
inline double operator/(const TCounterUI& counter, double c) {
  return counter.GetValue()/c;
}


// Operators with float
inline float operator+(float c, const TCounterUI& counter) {
  return counter.GetValue()+c;
}
inline float operator+(const TCounterUI& counter, float c) {
  return counter.GetValue()+c;
}
inline float operator-(float c, const TCounterUI& counter) {
  return c - counter.GetValue();
}
inline float operator-(const TCounterUI& counter, float c) {
  return counter.GetValue() - c;
}
inline float operator*(float c, const TCounterUI& counter) {
  return counter.GetValue()*c;
}
inline float operator*(const TCounterUI& counter, float c) {
  return counter.GetValue()*c;
}
inline float operator/(float c, const TCounterUI& counter) {
  return c/counter.GetValue();
}
inline float operator/(const TCounterUI& counter, float c) {
  return counter.GetValue()/c;
}


ostream& operator<<(ostream& os, const TCounterUI& c);

#endif
