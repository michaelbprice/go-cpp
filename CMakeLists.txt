cmake_minimum_required(VERSION 3.20)

project(go-cpp CXX)

include_directories(${PROJECT_SOURCE_DIR}/source)
file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/*.cpp)
add_executable(go ${SOURCE_FILES})
target_compile_features(go PRIVATE cxx_std_20)