cmake_minimum_required(VERSION 3.20)

option(USE_DYNAMIC_DEBUGGING "Enable dynamic debugging flags" OFF)  #TODO: Should describe flags that are not compatible.

project(go-cpp CXX)
set(CMAKE_CXX_STANDARD 20)
include_directories(${PROJECT_SOURCE_DIR}/source)

if (USE_DYNAMIC_DEBUGGING STREQUAL "ON")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /dynamicdeopt /O2 /Gw")
endif()

enable_testing()

################################################################################
# Library
################################################################################

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/*.cpp)
list(REMOVE_ITEM SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/main.cpp)
add_library(goimpl ${SOURCE_FILES})

if (USE_DYNAMIC_DEBUGGING STREQUAL "ON")
    set_target_properties(goimpl PROPERTIES
        STATIC_LIBRARY_OPTIONS "/dynamicdeopt"
    )
endif()

################################################################################
# Main executable
################################################################################

add_executable(go ${PROJECT_SOURCE_DIR}/source/main.cpp)
target_link_libraries(go goimpl)

if (USE_DYNAMIC_DEBUGGING STREQUAL "ON")
    target_link_options(go PRIVATE
        "/dynamicdeopt"
    )
endif()

################################################################################
# Test executable
################################################################################

find_package(Catch2 3 CONFIG REQUIRED)

file(GLOB TEST_SOURCE_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)
add_executable(go-tests ${TEST_SOURCE_FILES})
target_link_libraries(go-tests PUBLIC goimpl PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(go-tests REPORTER junit OUTPUT_DIR junit-output)

################################################################################
# Install logic
################################################################################

# Install headers
install(DIRECTORY ${PROJECT_SOURCE_DIR}/source/
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.tpp")

# Install static library
install(TARGETS goimpl
        ARCHIVE DESTINATION lib/$<CONFIG>
        LIBRARY DESTINATION lib/$<CONFIG>)

if (USE_DYNAMIC_DEBUGGING STREQUAL "ON")
    # Install alt.lib files for Dynamic Debugging support
    install(FILES $<TARGET_FILE_DIR:goimpl>/goimpl.alt.lib
            DESTINATION lib/$<CONFIG>
    )
endif()

# Install executables
install(TARGETS go go-tests
        RUNTIME DESTINATION bin/$<CONFIG>)