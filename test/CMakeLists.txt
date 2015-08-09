# CMakeLists.txt for PAF library. It creates a library with dictionary with its rootmap.
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(PAFTest)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

add_definitions(${ROOT_CXX_FLAGS})

# Retrieve all the source files into sources variable.
file(GLOB_RECURSE sources_paflibrary src/*.cxx)

# Retrieve all the header files into headers variable.
file(GLOB_RECURSE headers inc/*.h)

# Look for all directories of headers and put in includes variable.
SET(includes inc/)
FOREACH(header ${headers})
	GET_FILENAME_COMPONENT(dir_path ${header} PATH)
	SET(includes ${includes} ${dir_path})
ENDFOREACH()
LIST(REMOVE_DUPLICATES includes)

# Retrieve all the source files to use in paf tool.
file(GLOB_RECURSE sources_paftools src/paf_tools/*.cxx)

# Add some folders to include directories to user by ROOT dictioanry generator and compiler.
include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS} ${includes})

# Add some flags to compiler.
add_definitions(${ROOT_CXX_FLAGS})

enable_testing()

ROOT_LINKER_LIBRARY(PAFTest ${PROJECT_SOURCE_DIR}/test_utils/PAFTest.cxx ${PROJECT_SOURCE_DIR}/test_utils/PAFTestExpectedException.cxx ${PROJECT_SOURCE_DIR}/test_utils/PAFTestIException.cxx
	DEPENDENCIES Tree Hist Proof Gpad XMLIO Physics)

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
