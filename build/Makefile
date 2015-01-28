include Makefile.arch

VPATH = ../src:../src/computing:../src/environments:../src/packages:../src/project:../src/input_parameters:../src/util:../src/logger:../src/variable_container:

all: libPAF.so
	@rm *.o
	@rm *.h
	@rm *.cxx	
clean:
	rm *.so
	rm *.cxx
	rm *.h
	rm *.o

libPAF.so: PAFBaseSelectorDict.o PAFBaseSelector.o PAFISelectorDict.o PAFISelector.o PAFChainItemSelectorDict.o PAFChainItemSelector.o PAFChainSelectorDict.o PAFChainSelector.o PAFIExecutionEnvironmentDict.o PAFIExecutionEnvironment.o PAFPROOFEnvironmentDict.o PAFPROOFEnvironment.o PAFPROOFLiteEnvironmentDict.o PAFPROOFLiteEnvironment.o PAFPoDEnvironmentDict.o PAFPoDEnvironment.o PAFNamedContainerDict.o PAFNamedContainer.o PAFPackageDict.o PAFPackage.o PAFLibraryDict.o PAFLibrary.o PAFPackageSelectorDict.o PAFPackageSelector.o PAFPackageTSelectorDict.o PAFPackageTSelector.o PAFProjectDict.o PAFProject.o MakeSimpleSelector.o PAF.o PAFLogger.o PAFConsoleLogger.o PAFVariableContainerDict.o PAFVariableContainer.o PAFItemVariableContainerDict.o PAFItemVariableContainer.o PAFGenericItemVariableContainerDict.o PAFGenericItemVariableContainer.o
	@$(CXX) $(SOFLAGS) $(ROOTLIBS) $? -o $@

%.o: %.cxx
	@$(CXX) -fPIC -c $(CXXFLAGS) $< -o $@ 

%Dict.cxx: %.h
	@rootcint -f $@ -c $< $(addsuffix LinkDef.h, $(basename $<))
