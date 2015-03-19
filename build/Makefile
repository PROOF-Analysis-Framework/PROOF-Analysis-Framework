include ${ROOTSYS}/etc/Makefile.arch

VPATH = ../src:../src/computing:../src/environments:../src/packages:../src/project:../src/input_parameters:../src/util:../src/logger:../src/variable_container:../src/computing_helpers/:../src/settings/:../src/pafinspecttree/:

LINK_DEFS=$(shell find ../src/ -name '*LinkDef.h')

all: libPAF.so pafinspecttree

install: libPAF.so
	@cp $< $(ROOTSYS)/lib/
	@cp $(addsuffix .rootmap, $(basename $<)) ${ROOTSYS}/lib/

clean:
	-@rm *.so -f
	-@rm *.cxx -f
	-@rm *.h -f 
	-@rm *.o -f
	-@rm *.pcm -f
	-@rm pafinspecttree -f

pafinspecttree : PAFInspectTree.o
	$(CXX) -g $(ROOTLIBS) $? -o $@
	
libPAF.so: PAFBaseSelectorDict.o PAFBaseSelector.o PAFISelectorDict.o PAFISelector.o PAFChainItemSelectorDict.o PAFChainItemSelector.o PAFChainSelectorDict.o PAFChainSelector.o PAFIExecutionEnvironmentDict.o PAFIExecutionEnvironment.o PAFPROOFEnvironmentDict.o PAFPROOFEnvironment.o PAFPROOFLiteEnvironmentDict.o PAFPROOFLiteEnvironment.o PAFPoDEnvironmentDict.o PAFPoDEnvironment.o PAFPROOFCloudEnvironmentDict.o PAFPROOFCloudEnvironment.o PAFPROOFClusterEnvironmentDict.o PAFPROOFClusterEnvironment.o PAFSequentialEnvironmentDict.o PAFSequentialEnvironment.o PAFNamedItemDict.o PAFNamedItem.o PAFStopWatchDict.o PAFStopWatch.o PAFStringUtilDict.o PAFStringUtil.o PAFPackageDict.o PAFPackage.o PAFLibraryDict.o PAFLibrary.o PAFPackageSelectorDict.o PAFPackageSelector.o PAFProjectDict.o PAFProject.o PAF.o PAFLogger.o PAFConsoleLogger.o PAFVariableContainerDict.o PAFVariableContainer.o PAFItemVariableContainerDict.o PAFItemVariableContainer.o PAFGenericItemVariableContainerDict.o PAFGenericItemVariableContainer.o PAFFindHelperDict.o PAFFindHelper.o PAFISettingsDict.o PAFISettings.o PAFEnvironmentVariableSettingsDict.o PAFEnvironmentVariableSettings.o
	@$(CXX) $(SOFLAGS) $(ROOTLIBS) $? -o $@
	rlibmap -l $@ -c $(LINK_DEFS) > $(addsuffix .rootmap, $(basename $@))

%.o: %.cxx
	@$(CXX) -c $(CXXFLAGS) $< -o $@ 

%Dict.cxx: %.h
	@rootcint -f $@ -c $< $(addsuffix LinkDef.h, $(basename $<))
