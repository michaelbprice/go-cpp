cmake_minimum_required(VERSION 3.20)

project(go-cpp CXX)
set(CMAKE_CXX_STANDARD 20)

enable_testing()

################################################################################
# Library
################################################################################

set(GOIMPL_ROOT ${PROJECT_SOURCE_DIR}/goimpl)
file(GLOB GOIMPL_SOURCE_FILES ${GOIMPL_ROOT}/source/*.cpp)
include_directories(${GOIMPL_ROOT}/include)
add_library(goimpl ${GOIMPL_SOURCE_FILES})

################################################################################
# Library test executable
################################################################################

find_package(Catch2 3 CONFIG REQUIRED)

file(GLOB TEST_GOIMPL_SOURCE_FILES ${GOIMPL_ROOT}/tests/*.cpp)
add_executable(goimpl-tests ${TEST_GOIMPL_SOURCE_FILES})
target_link_libraries(goimpl-tests PUBLIC goimpl PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(goimpl-tests REPORTER junit OUTPUT_DIR junit-output)

################################################################################
# Main executable
################################################################################

set(GO_COMMANDLINE_ROOT ${PROJECT_SOURCE_DIR}/go)
add_executable(go ${GO_COMMANDLINE_ROOT}/source/main.cpp)
target_link_libraries(go goimpl)


