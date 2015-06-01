cmake_minimum_required(VERSION 3.0)

project(PAFTest)

enable_testing()

include_directories("$ENV{ROOTSYS}/include")
link_directories("$ENV{ROOTSYS}/lib")
link_libraries(Core Cint Gpad Rint Hist Proof)

add_library (PAFTest ${PROJECT_SOURCE_DIR}/test_utils/PAFTest.cxx ${PROJECT_SOURCE_DIR}/test_utils/PAFTestExpectedException.cxx ${PROJECT_SOURCE_DIR}/test_utils/PAFTestIException.cxx)
include_directories("test_utils")
link_libraries(PAFTest)

include_directories("$ENV{PAFPATH}/include")
link_directories("$ENV{PAFPATH}/lib")
link_libraries(libPAF.so)

add_subdirectory(variable_container)
