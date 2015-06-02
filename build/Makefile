include ${ROOTSYS}/etc/Makefile.arch

VPATH = ../src:../src/computing:../src/environments:../src/environments/proof_library_upload:../src/packages:../src/project:../src/input_parameters:../src/util:../src/logger:../src/variable_container:../src/computing_helpers/:../src/settings/:../src/paf_tools/:../src/exceptions/:

LINK_DEFS=$(shell find ../src/ -name '*LinkDef.h')

all: libPAF.so paf

install: libPAF.so paf
	@find ../src/ -name '*.h' ! -name '*LinkDef.h' | sed 's/^..\/src\///' | xargs -i sh -c 'mkdir -p `dirname ../include/PAF/{}` && cp ../src/{} ../include/PAF/{}'
	-@mkdir -p ../lib/
	@cp libPAF.so ../lib/libPAF.so
	@cp libPAF.rootmap ../lib/libPAF.rootmap
	@cp paf ../bin/

installosx: libPAF.so paf
	@find ../src/ -name '*.h' ! -name '*LinkDef.h' | sed 's/^..\/src\///' | xargs -I{} sh -c 'mkdir -p `dirname ../include/PAF/{}` && cp ../src/{} ../include/PAF/{}'
	-@mkdir -p ../lib/
	@cp libPAF.so ../lib/libPAF.so
	@cp libPAF.rootmap ../lib/libPAF.rootmap
	@cp paf ../bin/


clean:
	-@rm *.so -f
	-@rm *.cxx -f
	-@rm *.h -f 
	-@rm *.o -f
	-@rm *.pcm -f
	-@rm *.rootmap -f
	-@rm paf -f
	-@rm ../bin/paf
	-@rm -r ../include/
	-@rm -r ../lib/
	
paf : PAFTools.o PAFITool.o PAFAbstractTool.o PAFToolInspectTree.o PAFToolReset.o PAFToolCreateSelector.o PAFIException.o PAFExceptionCommandExpression.o
	@$(CXX) $? $(ROOTLIBS) -o $@
	
libPAF.so: PAFBaseSelectorDict.o PAFBaseSelector.o PAFISelectorDict.o PAFISelector.o PAFChainItemSelectorDict.o PAFChainItemSelector.o PAFChainSelectorDict.o PAFChainSelector.o PAFIExecutionEnvironmentDict.o PAFIExecutionEnvironment.o PAFPROOFEnvironmentDict.o PAFPROOFEnvironment.o PAFPROOFLiteEnvironmentDict.o PAFPROOFLiteEnvironment.o PAFPoDEnvironmentDict.o PAFPoDEnvironment.o PAFPROOFCloudEnvironmentDict.o PAFPROOFCloudEnvironment.o PAFPROOFClusterEnvironmentDict.o PAFPROOFClusterEnvironment.o PAFSequentialEnvironmentDict.o PAFSequentialEnvironment.o PAFPROOFIUploadLibraryDict.o PAFPROOFIUploadLibrary.o PAFPROOFUploadLibrarySharedDirectoryDict.o PAFPROOFUploadLibrarySharedDirectory.o PAFPROOFUploadLibraryTProofUploadDict.o PAFPROOFUploadLibraryTProofUpload.o PAFNamedItemDict.o PAFNamedItem.o PAFStopWatchDict.o PAFStopWatch.o PAFStringUtilDict.o PAFStringUtil.o PAFPackageDict.o PAFPackage.o PAFLibraryDict.o PAFLibrary.o PAFPackageSelectorDict.o PAFPackageSelector.o PAFAbstractProjectDict.o PAFAbstractProject.o PAFProjectDict.o PAFProject.o PAFProjectGenericDict.o PAFProjectGeneric.o PAF.o PAFLogger.o PAFConsoleLogger.o PAFVariableContainerDict.o PAFVariableContainer.o PAFGenericItemVariableContainerDict.o PAFGenericItemVariableContainer.o PAFFindHelperDict.o PAFFindHelper.o PAFISettingsDict.o PAFISettings.o PAFEnvironmentVariableSettingsDict.o PAFEnvironmentVariableSettings.o
ifeq ($(PLATFORM),macosx)
	@$(CXX) $(SOFLAGS)$@ $(ROOTLIBS) -lProof $? -o $@
else
	@$(CXX) $(SOFLAGS) $(ROOTLIBS) -lProof $? -o $@
endif
	@rlibmap -l $@ -c $(LINK_DEFS) > $(addsuffix .rootmap, $(basename $@))

%.o: %.cxx
	@$(CXX) -c $(CXXFLAGS) $< -o $@ 

.SECONDARY:
%Dict.cxx: %.h
	@rootcint -f $@ -c $< $(addsuffix LinkDef.h, $(basename $<))
