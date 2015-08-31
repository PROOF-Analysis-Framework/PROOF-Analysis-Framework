# CMakeLists.txt for PAF library. It creates a library with dictionary with its rootmap.
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(PAF)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
# Check if ROOTSYS is defined and in that case include it

if(NOT DEFINED ENV{ROOTSYS})
  message("ERROR: Could not find ROOTSYS environment variable.")
  message("       Have you set up your ROOT environment?")
  message("       This is typically done by issuing the following command")
  message("       $ source /path_to_root/bin/thisroot.sh")
  message(FATAL_ERROR "Exiting!")
endif(NOT DEFINED ENV{ROOTSYS})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/etc/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/cmake/modules)

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net Proof)

#---Define the Standard macros for ROOT---
include(RootNewMacros)
if(NOT DEFINED ROOT_ARCHITECTURE)
  include(CheckCompiler)
endif()

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

# Add some folders to include directories to user by ROOT dictionary generator and compiler.
include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS} ${includes})

# Add some flags to compiler.
add_definitions(${ROOT_CXX_FLAGS})

# Generate the dictionary files.
root_generate_dictionary(G__PAF ${headers} LINKDEF LinkDef.hxx)

# Compile all the files in sources variable and the dictionary.
root_linker_library(PAF ${sources_paflibrary} G__PAF.cxx LIBRARIES Proof DEPENDENCIES Hist Proof Gpad)

# Compile paf tool.
root_executable(paf ${sources_paftools} LIBRARIES PAF)

install (FILES ${headers}
         DESTINATION ${CMAKE_SOURCE_DIR}/include/)
       
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/libPAF.so
         DESTINATION ${CMAKE_SOURCE_DIR}/lib/)
         
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/paf
         DESTINATION ${CMAKE_SOURCE_DIR}/bin/
         PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ)

# Get ROOT Version Major number by calling root-config
exec_program("root-config --version|cut -f 1 -d." OUTPUT_VARIABLE ROOT_VERSION_MAJOR)
message("-- ROOT Major version: " ${ROOT_VERSION_MAJOR})
         
if(${ROOT_VERSION_MAJOR} MATCHES "6")
	install (FILES ${CMAKE_CURRENT_BINARY_DIR}/libPAF.rootmap
		DESTINATION ${CMAKE_SOURCE_DIR}/lib/)
         
	install (FILES ${CMAKE_CURRENT_BINARY_DIR}/G__PAF_rdict.pcm
		DESTINATION ${CMAKE_SOURCE_DIR}/lib/)
endif(${ROOT_VERSION_MAJOR} MATCHES "6")

if(${ROOT_VERSION_MAJOR} MATCHES "5")
  #The lib dir is not automatically there and it is needed
  file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/)
  execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/lib/)
  execute_process(
    COMMAND rlibmap -o ${CMAKE_SOURCE_DIR}/lib/libPAF.rootmap -l ${CMAKE_SOURCE_DIR}/lib/libPAF.so -c ${CMAKE_SOURCE_DIR}/inc/LinkDef.hxx)
endif(${ROOT_VERSION_MAJOR} MATCHES "5")

