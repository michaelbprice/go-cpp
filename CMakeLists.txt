cmake_minimum_required(VERSION 3.20)

project(go-cpp CXX)
set(CMAKE_CXX_STANDARD 20)
include_directories(${PROJECT_SOURCE_DIR}/source)

enable_testing()

################################################################################
# Library
################################################################################

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/*.cpp)
list(REMOVE_ITEM SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/main.cpp)
add_library(goimpl ${SOURCE_FILES})

################################################################################
# Main executable
################################################################################

add_executable(go ${PROJECT_SOURCE_DIR}/source/main.cpp)
target_link_libraries(go goimpl)


################################################################################
# Test executable
################################################################################

find_package(Catch2 3 CONFIG REQUIRED)

file(GLOB TEST_SOURCE_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)
add_executable(go-tests ${TEST_SOURCE_FILES})
target_link_libraries(go-tests PUBLIC goimpl PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(go-tests)