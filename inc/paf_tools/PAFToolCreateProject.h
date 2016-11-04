/**
	@brief PAF tool class to create the skeleton of a PAF Project.
	@file PAFToolCreateProject.h
	@class PAFToolCreateProject
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2016-11-04
 */

#pragma once

#include "PAFAbstractTool.h"

class PAFToolCreateProject : public PAFAbstractTool
{
	public:
		PAFToolCreateProject();
		virtual ~PAFToolCreateProject() {}

		virtual void ExecuteTool(TList* params);

	protected:
		void CreateFileTemplated(const TString& iFileName, const TString& oFileName, 
					 const TString& from, const TString& to) const;

};
