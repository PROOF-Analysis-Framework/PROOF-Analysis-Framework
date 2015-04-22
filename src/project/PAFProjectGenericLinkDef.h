#ifdef __CINT__
#pragma link C++ class PAFProjectGeneric+;

#pragma link C++ function PAFProjectGeneric::SetInputParam<bool>(const char*, bool);
#pragma link C++ function PAFProjectGeneric::SetInputParam<int>(const char*, int);
#pragma link C++ function PAFProjectGeneric::SetInputParam<float>(const char*, float);
#pragma link C++ function PAFProjectGeneric::SetInputParam<double>(const char*, double);
#pragma link C++ function PAFProjectGeneric::SetInputParam<TObject>(const char*, TObject&);
#pragma link C++ function PAFProjectGeneric::SetInputParam<TString>(const char*, TString&);
#pragma link C++ function PAFProjectGeneric::SetInputParam<TObject*>(const char*, TObject*);
#pragma link C++ function PAFProjectGeneric::SetInputParam<TString*>(const char*, TString*);
#pragma link C++ function PAFProjectGeneric::SetInputParam<void*>(const char*, void*);
#endif
