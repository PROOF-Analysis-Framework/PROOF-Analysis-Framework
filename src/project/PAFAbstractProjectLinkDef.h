#ifdef __CINT__
#pragma link C++ class PAFAbstractProject+;

#pragma link C++ function PAFAbstractProject::SetInputParam<bool>(const char*, bool);
#pragma link C++ function PAFAbstractProject::SetInputParam<int>(const char*, int);
#pragma link C++ function PAFAbstractProject::SetInputParam<float>(const char*, float);
#pragma link C++ function PAFAbstractProject::SetInputParam<double>(const char*, double);
#pragma link C++ function PAFAbstractProject::SetInputParam<TObject>(const char*, TObject&);
#pragma link C++ function PAFAbstractProject::SetInputParam<TString>(const char*, TString&);
#pragma link C++ function PAFAbstractProject::SetInputParam<TObject*>(const char*, TObject*);
#pragma link C++ function PAFAbstractProject::SetInputParam<TString*>(const char*, TString*);
#pragma link C++ function PAFAbstractProject::SetInputParam<void*>(const char*, void*);
#endif
