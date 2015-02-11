include Makefile.arch

VPATH = ../src:../src/computing:../src/environments:../src/packages:../src/project:../src/input_parameters:../src/util:../src/logger:../src/variable_container:../src/computing_helpers/:../src/settings/:

all: libPAF.so
	@rm *.o
	@rm *.h
	@rm *.cxx	
clean:
	rm *.so
	rm *.cxx
	rm *.h
	rm *.o

libPAF.so: PAFBaseSelectorDict.o PAFBaseSelector.o PAFISelectorDict.o PAFISelector.o PAFChainItemSelectorDict.o PAFChainItemSelector.o PAFChainSelectorDict.o PAFChainSelector.o PAFIExecutionEnvironmentDict.o PAFIExecutionEnvironment.o PAFPROOFEnvironmentDict.o PAFPROOFEnvironment.o PAFPROOFLiteEnvironmentDict.o PAFPROOFLiteEnvironment.o PAFPoDEnvironmentDict.o PAFPoDEnvironment.o PAFSequentialEnvironmentDict.o PAFSequentialEnvironment.o PAFNamedItemDict.o PAFNamedItem.o PAFPackageDict.o PAFPackage.o PAFLibraryDict.o PAFLibrary.o PAFPackageSelectorDict.o PAFPackageSelector.o PAFProjectDict.o PAFProject.o PAF.o PAFLogger.o PAFConsoleLogger.o PAFVariableContainerDict.o PAFVariableContainer.o PAFItemVariableContainerDict.o PAFItemVariableContainer.o PAFGenericItemVariableContainerDict.o PAFGenericItemVariableContainer.o PAFFindHelperDict.o PAFFindHelper.o PAFISettingsDict.o PAFISettings.o PAFEnvironmentVariableSettingsDict.o PAFEnvironmentVariableSettings.o
	@$(CXX) $(SOFLAGS) $(ROOTLIBS) $? -o $@

%.o: %.cxx
	@$(CXX) -fPIC -c $(CXXFLAGS) $< -o $@ 

%Dict.cxx: %.h
	@rootcint -f $@ -c $< $(addsuffix LinkDef.h, $(basename $<))
