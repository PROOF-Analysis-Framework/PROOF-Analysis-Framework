
#ifdef __CINT__
#pragma link C++ class PAFBaseSelector+;
#pragma link C++ class PAFISelector+;
#pragma link C++ class PAFChainItemSelector+;
#pragma link C++ class PAFChainSelector+;
#pragma link C++ class PAFFindHelper+;
#pragma link C++ class PAFAbstractType+;

#pragma link C++ class PAFArrayPrimitiveType<UChar_t>+;
#pragma link C++ class PAFArrayPrimitiveType<Char_t>+;
#pragma link C++ class PAFArrayPrimitiveType<Double_t>+;
#pragma link C++ class PAFArrayPrimitiveType<Float_t>+;
#pragma link C++ class PAFArrayPrimitiveType<Int_t>+;
#pragma link C++ class PAFArrayPrimitiveType<Long_t>+;
#pragma link C++ class PAFArrayPrimitiveType<Bool_t>+;
#pragma link C++ class PAFArrayPrimitiveType<Short_t>+;

#pragma link C++ class PAFElementType+;

#pragma link C++ class PAFElementVectorType<UChar_t>+;
#pragma link C++ class PAFElementVectorType<Char_t>+;
#pragma link C++ class PAFElementVectorType<Double_t>+;
#pragma link C++ class PAFElementVectorType<Float_t>+;
#pragma link C++ class PAFElementVectorType<Int_t>+;
#pragma link C++ class PAFElementVectorType<Long_t>+;
#pragma link C++ class PAFElementVectorType<Bool_t>+;
#pragma link C++ class PAFElementVectorType<Short_t>+;

#pragma link C++ class PAFIType+;

#pragma link C++ class PAFPrimitiveType<UChar_t>+;
#pragma link C++ class PAFPrimitiveType<Char_t>+;
#pragma link C++ class PAFPrimitiveType<Double_t>+;
#pragma link C++ class PAFPrimitiveType<Float_t>+;
#pragma link C++ class PAFPrimitiveType<Int_t>+;
#pragma link C++ class PAFPrimitiveType<Long_t>+;
#pragma link C++ class PAFPrimitiveType<Bool_t>+;
#pragma link C++ class PAFPrimitiveType<Short_t>+;

#pragma link C++ class PAFTObjectType+;

#pragma link C++ class PAFTypesFactory+;

#pragma link C++ class PAFIExecutionEnvironment+;
#pragma link C++ class PAFPoDEnvironment+;
#pragma link C++ class PAFPROOFCloudEnvironment+;
#pragma link C++ class PAFPROOFClusterEnvironment+;
#pragma link C++ class PAFPROOFEnvironment+;
#pragma link C++ class PAFPROOFLiteEnvironment+;
#pragma link C++ class PAFSequentialEnvironment+;

#pragma link C++ class PAFPROOFIUploadLibrary+;
#pragma link C++ class PAFPROOFUploadLibrarySharedDirectory+;
#pragma link C++ class PAFPROOFUploadLibraryTProofUpload+;

#pragma link C++ class PAFLibrary+;
#pragma link C++ class PAFPackage+;
#pragma link C++ class PAFPackageSelector+;

#pragma link C++ class PAFIProgressUpdated+;
#pragma link C++ class PAFProgressUpdatedLogger+;

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

#pragma link C++ class PAFEnvironmentVariableSettings+;
#pragma link C++ class PAFISettings+;
#pragma link C++ class PAFManualSettings+;

#pragma link C++ class PAFNamedItem+;
#pragma link C++ class PAFStopWatch+;
#pragma link C++ class PAFStringUtil+;

#pragma link C++ class PAFVariableContainer+;

#pragma link C++ class PAFGenericItemVariableContainer<Char_t>+;
#pragma link C++ class PAFGenericItemVariableContainer<UChar_t>+;
#pragma link C++ class PAFGenericItemVariableContainer<Short_t>+;
#pragma link C++ class PAFGenericItemVariableContainer<UShort_t>+;
#pragma link C++ class PAFGenericItemVariableContainer<Int_t>+;
#pragma link C++ class PAFGenericItemVariableContainer<UInt_t>+;
#pragma link C++ class PAFGenericItemVariableContainer<Long_t>+;
#pragma link C++ class PAFGenericItemVariableContainer<ULong_t>+;
#pragma link C++ class PAFGenericItemVariableContainer<Float_t>+;
#pragma link C++ class PAFGenericItemVariableContainer<Double_t>+;
#pragma link C++ class PAFGenericItemVariableContainer<Bool_t>+;
#pragma link C++ class PAFGenericItemVariableContainer<Byte_t>+;
#pragma link C++ class PAFGenericItemVariableContainer<Real_t>+;
#pragma link C++ class PAFGenericItemVariableContainer<Text_t>+;

#pragma link C++ class PAFGenericItemVariableContainer<std::vector<Char_t>*>+;
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<UChar_t>*>+;
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<Short_t>*>+;
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<UShort_t>*>+;
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<Int_t>*>+;
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<UInt_t>*>+;
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<Long_t>*>+;
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<ULong_t>*>+;
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<Float_t>*>+;
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<Double_t>*>+;
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<Bool_t>*>+;
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<Byte_t>*>+;
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<Real_t>*>+;
#pragma link C++ class PAFGenericItemVariableContainer<std::vector<Text_t>*>+;

#pragma link C++ class PAFGenericItemVariableContainer<TObject>+;
#pragma link C++ class PAFGenericItemVariableContainer<TObject*>+;
#pragma link C++ class PAFGenericItemVariableContainer<TString>+;
#pragma link C++ class PAFGenericItemVariableContainer<TString*>+;
#pragma link C++ class PAFGenericItemVariableContainer<char*>+;
#pragma link C++ class PAFGenericItemVariableContainer<const char*>+;
#pragma link C++ class PAFGenericItemVariableContainer<void*>+;

#endif
