/**
	@brief Internal PAF class which allow to work with generic types without specified it to system.
	@file PAFItemVariableContainer.h
	@class PAFItemVariableContainer
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-26
*/

#pragma once

#include "TObject.h"

class PAFItemVariableContainer : public TObject
{
	public:
		PAFItemVariableContainer() : TObject() {}
		virtual ~PAFItemVariableContainer() {}
		
		//TODO Maybe an "IsType" function could facilitate the evolution.
	ClassDef(PAFItemVariableContainer, 1);
};