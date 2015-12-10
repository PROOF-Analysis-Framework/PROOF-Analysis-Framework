/**
	@brief Internal PAF class to abstract some common implemtation of concretes PAFITypes.
	@file PAFAbstractType.cxx
	@class PAFAbstractType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-06-17
 */

#include "PAFAbstractType.h"
#include "TBranch.h"
#include "TString.h"

#include "PAF.h"

ClassImp(PAFAbstractType);

PAFAbstractType::PAFAbstractType()
	: fLeaf(0)
{

}

PAFAbstractType::PAFAbstractType(TLeaf* leaf)
	: fLeaf(leaf)
{

}

PAFAbstractType::~PAFAbstractType()
{
	delete fLeaf;
}

void PAFAbstractType::SetTLeaf(TLeaf* leaf)
{
	delete fLeaf;
	fLeaf = leaf;
}

TLeaf* PAFAbstractType::GetLeaf()
{
	return fLeaf;
}

int PAFAbstractType::GetNData()
{
	EnableBranch();
	return fLeaf->GetNdata();
}

void PAFAbstractType::EnableBranch()
{
	TBranch* branch = fLeaf->GetBranch();
	if (branch->TestBit(kDoNotProcess))
	{
		PAF_DEBUG("PAFChainItemSelector", TString::Format("Loading variable: %s", fLeaf->GetName()).Data());
		branch->SetStatus(kTRUE);
		branch->GetEntry(branch->GetReadEntry());
	}
}

