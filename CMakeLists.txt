# CMakeLists.txt for PAF library. It creates a library with dictionary with its rootmap.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
PROJECT(PAF)

# Some checks
if(NOT DEFINED ENV{ROOTSYS})
  message("ERROR: Could not find ROOTSYS environment variable.")
  message("       Have you set up your ROOT environment?")
  message("       This is typically done by issuing the following command")
  message("       $ source /path_to_root/bin/thisroot.sh")
  message(FATAL_ERROR "Exiting!")
endif(NOT DEFINED ENV{ROOTSYS})

if(NOT EXISTS $ENV{ROOTSYS}/cmake/ROOTConfig.cmake)
       message("ERROR: It seems your ROOT distribution was not built with cmake, since we")
       message("       could not find the file:")
       message("       $ENV{ROOTSYS}/ROOTConfig.cmake")
       message("")
       message("       PAF current build system requires that cmake was used to buid ROOT.")
       message("       If this is a false positive let us know.")
       message("")
       message(FATAL_ERROR "Exiting!")
endif(NOT EXISTS $ENV{ROOTSYS}/cmake/ROOTConfig.cmake)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
# This option is not supported. The lines below may help to find the way to support this.
# LIST(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)
# LIST(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/cmake/modules)
# include(RootNewMacros)
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
LIST(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
FIND_PACKAGE(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
INCLUDE(${ROOT_USE_FILE})

ADD_DEFINITIONS(${ROOT_CXX_FLAGS})

# Retrieve all the source files into sources variable.
FILE(GLOB_RECURSE sources_paflibrary src/*.cxx)

# Retrieve all the header files into headers variable.
FILE(GLOB_RECURSE headers inc/*.h)

# Look for all directories of headers and put in includes variable.
SET(includes inc/)
FOREACH(header ${headers})
	GET_FILENAME_COMPONENT(dir_path ${header} PATH)
	SET(includes ${includes} ${dir_path})
ENDFOREACH()
LIST(REMOVE_DUPLICATES includes)

# Retrieve all the source files to use in paf tool.
FILE(GLOB_RECURSE sources_paftools src/paf_tools/*.cxx)

# Add some folders to include directories to user by ROOT dictionary generator and compiler.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS} ${includes})

# Add some flags to compiler.
ADD_DEFINITIONS(${ROOT_CXX_FLAGS})

# Generate the dictionary files.
ROOT_GENERATE_DICTIONARY(G__PAF ${headers} LINKDEF LinkDef.hxx)

# Compile all the files in sources variable and the dictionary.
ROOT_LINKER_LIBRARY(PAF ${sources_paflibrary} G__PAF.cxx DEPENDENCIES Hist Proof Gpad)

# Compile paf tool.
ROOT_EXECUTABLE(paf ${sources_paftools} LIBRARIES PAF)

INSTALL (FILES ${headers}
         DESTINATION ${CMAKE_SOURCE_DIR}/include/)
       
INSTALL (FILES ${CMAKE_CURRENT_BINARY_DIR}/libPAF.so
         DESTINATION ${CMAKE_SOURCE_DIR}/lib/)
         
INSTALL (FILES ${CMAKE_CURRENT_BINARY_DIR}/paf
         DESTINATION ${CMAKE_SOURCE_DIR}/bin/
         PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ)

MESSAGE("-- ROOT Major version: " ${ROOT_VERSION_MAJOR})
         
IF(${ROOT_VERSION_MAJOR} MATCHES "6")
	INSTALL (FILES ${CMAKE_CURRENT_BINARY_DIR}/libPAF.rootmap
		DESTINATION ${CMAKE_SOURCE_DIR}/lib/)
         
	INSTALL (FILES ${CMAKE_CURRENT_BINARY_DIR}/G__PAF_rdict.pcm
		DESTINATION ${CMAKE_SOURCE_DIR}/lib/)
ENDIF(${ROOT_VERSION_MAJOR} MATCHES "6")

IF(${ROOT_VERSION_MAJOR} MATCHES "5")
  #The lib dir is not automatically there and it is needed
  file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/)
  execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/lib/)
  EXECUTE_PROCESS(
    COMMAND rlibmap -o ${CMAKE_SOURCE_DIR}/lib/libPAF.rootmap -l ${CMAKE_SOURCE_DIR}/lib/libPAF.so -c ${CMAKE_SOURCE_DIR}/inc/LinkDef.hxx)
ENDIF(${ROOT_VERSION_MAJOR} MATCHES "5")

