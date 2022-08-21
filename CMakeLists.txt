cmake_minimum_required(VERSION 3.20)

project(go-cpp CXX)
set(CMAKE_CXX_STANDARD 20)

################################################################################
# Main executable
################################################################################

include_directories(${PROJECT_SOURCE_DIR}/source)
file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/*.cpp)
add_executable(go ${SOURCE_FILES})


################################################################################
# Test executable
################################################################################

find_package(Catch2 3 CONFIG REQUIRED)

file(GLOB TEST_SOURCE_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)
add_executable(go-tests ${TEST_SOURCE_FILES})
target_link_libraries(go-tests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)