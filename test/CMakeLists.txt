# CMakeLists.txt for PAF library. It creates a library with dictionary with its rootmap.
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(PAFTest)

# Check PAF has been configured
if(NOT DEFINED ENV{PAFPATH})
  message("ERROR: Could not find PAFPATH environment variable.")
  message("       Have you set up your PAF environment?")
  message("       This is typically done by issuing the following command")
  message("       $ source /path_to_paf/PAF_setup.sh")
  message(FATAL_ERROR "Exiting!")
endif(NOT DEFINED ENV{PAFPATH})

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
LIST(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/etc/cmake)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/cmake/modules)

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
FIND_PACKAGE(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net Proof)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
INCLUDE(${ROOT_USE_FILE})


#---Define the Standard macros for ROOT---
#include(RootNewMacros)
#if(NOT DEFINED ROOT_ARCHITECTURE)
#  include(CheckCompiler)
#endif()

#---Set Link and include directories------
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)
include_directories(${ROOT_INCLUDE_DIRS})
link_directories(${ROOT_LIBRARY_DIRS})
link_libraries(${ROOT_LIBRARIES} ${ROOT_Proof_LIBRARY})

# Retrieve all the source files into sources variable.
file(GLOB_RECURSE sources_paflibrary src/*.cxx)

# Retrieve all the header files into headers variable.
file(GLOB_RECURSE headers inc/*.h)

# Look for all directories of headers and put in includes variable.
set(includes inc/)
foreach(header ${headers})
	get_filename_component(dir_path ${header} PATH)
	set(includes ${includes} ${dir_path})
endforeach()
list(REMOVE_DUPLICATES includes)

# Retrieve all the source files to use in paf tool.
file(GLOB_RECURSE sources_paftools src/paf_tools/*.cxx)

# Add some folders to include directories to user by ROOT dictioanry generator and compiler.
include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS} ${includes})

# Add some flags to compiler.
add_definitions(${ROOT_CXX_FLAGS})

enable_testing()

root_linker_library(PAFTest ${PROJECT_SOURCE_DIR}/test_utils/PAFTest.cxx ${PROJECT_SOURCE_DIR}/test_utils/PAFTestExpectedException.cxx ${PROJECT_SOURCE_DIR}/test_utils/PAFTestIException.cxx
	DEPENDENCIES Tree Hist Proof Gpad XMLIO Physics RIO)

include_directories("test_utils")
link_libraries(PAFTest)

include_directories("$ENV{PAFPATH}/include")
link_directories("$ENV{PAFPATH}/lib")
link_libraries(libPAF.so)

add_subdirectory(computing)
add_subdirectory(computing_helpers)
add_subdirectory(environments)
add_subdirectory(packages)
add_subdirectory(project)
add_subdirectory(util)
add_subdirectory(variable_container)
