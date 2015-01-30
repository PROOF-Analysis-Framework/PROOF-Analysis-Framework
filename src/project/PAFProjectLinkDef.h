#ifdef __CINT__
#pragma link C++ class PAFProject+;

#pragma link C++ function PAFProject::SetInputParam<bool>(const char*, bool);
#pragma link C++ function PAFProject::SetInputParam<int>(const char*, int);
#pragma link C++ function PAFProject::SetInputParam<float>(const char*, float);
#pragma link C++ function PAFProject::SetInputParam<double>(const char*, double);
#pragma link C++ function PAFProject::SetInputParam<TObject>(const char*, TObject&);
#pragma link C++ function PAFProject::SetInputParam<TString>(const char*, TString&);
#pragma link C++ function PAFProject::SetInputParam<TObject*>(const char*, TObject*);
#pragma link C++ function PAFProject::SetInputParam<TString*>(const char*, TString*);
#pragma link C++ function PAFProject::SetInputParam<void*>(const char*, void*);
#endif
