/**
	@brief Factory method pattern to create PAF types from TLeafs.
	@file PAFTypesFactory.cxx
	@class PAFTypesFactory
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-06-17
*/

#include "PAFTypesFactory.h"

#include "PAFPrimitiveType.h"
#include "PAFTObjectType.h"
#include "PAFElementType.h"
#include "PAFElementVectorType.h"

#include "../../PAF.h"

#include "TLeafB.h"
#include "TLeafC.h"
#include "TLeafD.h"
#include "TLeafElement.h"
#include "TLeafF.h"
#include "TLeafI.h"
#include "TLeafL.h"
#include "TLeafO.h"
#include "TLeafObject.h"
#include "TLeafS.h"

PAFIType* PAFTypesFactory::GetPAFType(TLeaf* leaf)
{
	if(leaf == NULL)
	{
		return NULL;
	}
	else if (leaf->IsA() == TLeafB::Class())
	{
		return new PAFPrimitiveType<UChar_t>(leaf);
	}
	else if (leaf->IsA() == TLeafC::Class())
	{
		return new PAFPrimitiveType<Char_t>(leaf);
	}
	else if (leaf->IsA() == TLeafD::Class())
	{
		return new PAFPrimitiveType<Double_t>(leaf);
	}
	else if (leaf->IsA() == TLeafElement::Class())
	{
		TString tType(leaf->GetTypeName());

		//TODO vector is the first conditional and nested should be all of this.
		//TODO Other types is not controlled yet (char, uchar, short, ushort, uint, ulong).
		if(tType.EqualTo("vector<double>"))
		{
			return new PAFElementVectorType<double>(leaf);
		}
		else if(tType.EqualTo("vector<float>"))
		{
			return new PAFElementVectorType<float>(leaf);
		}
		else if(tType.EqualTo("vector<int>"))
		{
			return new PAFElementVectorType<int>(leaf);		
		}
		else if(tType.EqualTo("vector<long>"))
		{
			return new PAFElementVectorType<long>(leaf);		
		}
		else if(tType.EqualTo("vector<bool>"))
		{
			return new PAFElementVectorType<bool>(leaf);		
		}
		
		return new PAFElementType(leaf);
	}
	else if (leaf->IsA() == TLeafF::Class())
	{
		return new PAFPrimitiveType<Float_t>(leaf);
	}
	else if (leaf->IsA() == TLeafI::Class())
	{
		return new PAFPrimitiveType<Int_t>(leaf);
	}
	else if (leaf->IsA() == TLeafL::Class())
	{
		return new PAFPrimitiveType<Long_t>(leaf);
	}
	else if (leaf->IsA() == TLeafO::Class())
	{
		return new PAFPrimitiveType<Bool_t>(leaf);
	}
	else if (leaf->IsA() == TLeafObject::Class())
	{
		return new PAFTObjectType(leaf);
	}
	else if (leaf->IsA() == TLeafS::Class())
	{
		return new PAFPrimitiveType<Short_t>(leaf);
	}
	else
	{
		return NULL;
	}
}

