/**
	@brief Header of PAF which will hold PAF variables and PAF relevant methods.  
	@file PAF.h
	@class PAF
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-25
 */

#pragma once

void PAF_DEBUG(const char* module, const char* msg);
void PAF_INFO(const char* module, const char* msg);
void PAF_WARN(const char* module, const char* msg);
void PAF_ERROR(const char* module, const char* msg);
void PAF_FATAL(const char* module, const char* msg);
