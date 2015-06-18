/**
	@brief Implementation of PAFIExecutionEnvironment to work over diferents PROOF environments.
	@file PAFPROOFEnvironment.cxx
	@class PAFPROOFEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFPROOFEnvironment.h"

#include "TString.h"

#include "proof_library_upload/PAFPROOFUploadLibrarySharedDirectory.h"

#include "../settings/PAFEnvironmentVariableSettings.h"

PAFPROOFIUploadLibrary*	DEFAULT_PROOFUPLOADLIBRARY = new PAFPROOFUploadLibrarySharedDirectory();

PAFPROOFEnvironment::PAFPROOFEnvironment()
{
	InitMembers();
}

PAFPROOFEnvironment::~PAFPROOFEnvironment()
{
	delete fSession;
}

void PAFPROOFEnvironment::InitMembers()
{
	fPROOFUploadLibrary = DEFAULT_PROOFUPLOADLIBRARY;
}

void PAFPROOFEnvironment::Initialise()
{
	fSession = doCreateTProof();
	fPROOFUploadLibrary->SetSession(fSession);
	LoadPAF();
}

void PAFPROOFEnvironment::Dispose()
{
	fSession->Close();
}

void PAFPROOFEnvironment::AddInput(TObject* obj)
{
	fSession->AddInputData(obj);
}

void PAFPROOFEnvironment::AddFeedback(const char* name)
{
	fSession->AddFeedback(name);
}

TDrawFeedback* PAFPROOFEnvironment::CreateDrawFeedback()
{
	return fSession->CreateDrawFeedback();
}

PAFIProgressUpdated* 	fProgressUpdated;
void PAFPROOFEnvironment::SetProgressUpdated(PAFIProgressUpdated* progressUpdated)
{
	fProgressUpdated = progressUpdated;
}

PAFIProgressUpdated* PAFPROOFEnvironment::GetProgressUpdated()
{
	return fProgressUpdated;
}

void UpdateProgress(Long64_t tot, Long64_t proc, Float_t proctime, Long64_t bytes)
{
	fProgressUpdated->ProgressUpdated(tot, proc);
}

void PAFPROOFEnvironment::Process(PAFBaseSelector* selector, Long64_t nentries)
{
	fSession->SetPrintProgress(UpdateProgress);
	fSession->Process(selector, nentries);
}

void PAFPROOFEnvironment::Process(PAFBaseSelector* selector, TDSet* dataFiles, Long64_t firstEvent, Long64_t nEvents)
{
	fSession->Process(dataFiles, selector, "", nEvents, firstEvent);
}

void PAFPROOFEnvironment::SetPROOFUpload(PAFPROOFIUploadLibrary* proofUploadLibrary)
{
	delete fPROOFUploadLibrary;
	fPROOFUploadLibrary = proofUploadLibrary;
}

PAFPROOFIUploadLibrary* PAFPROOFEnvironment::GetPROOFUpload()
{
	return fPROOFUploadLibrary;
}

bool PAFPROOFEnvironment::UploadPackage(PAFPackage* package)
{
	return fSession->UploadPackage(package->GetParFileName(), TProof::kRemoveOld) == 0;
}

bool PAFPROOFEnvironment::EnablePackage(PAFPackage* package)
{
	return fSession->EnablePackage(package->GetName().Data()) == 0;
}

bool PAFPROOFEnvironment::LoadLibrary(PAFLibrary* library)
{
	return fPROOFUploadLibrary->UploadLibrary(library);
}

void PAFPROOFEnvironment::LoadPAF()
{
	//FIXME This smells too bad.
	PAFISettings* settings = new PAFEnvironmentVariableSettings();
	
	fSession->Exec("TH1* th1 = 0"); //TODO Remove this trick. Needed in Ubuntu.
	PAFLibrary paf(settings, "$PAFPATH/lib/libPAF.so");
	LoadLibrary(&paf);
}


