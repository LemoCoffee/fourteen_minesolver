cmake_minimum_required(VERSION 3.15)
project(fourteen_minesolver VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add debug symbols and optimization flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Source files for the main application
set(APP_SOURCES
    src/main.cpp
    src/board.cpp
    src/tile.cpp
    src/variantBasic.cpp
    src/variantQuadrant.cpp
    src/variant.cpp
)

# Create main executable
add_executable(fourteen_minesolver ${APP_SOURCES})

# ============================================================================
# GoogleTest Setup
# ============================================================================
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP FALSE
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Test executable
add_executable(test_basic
    src/tests/basic_game.cpp
    src/board.cpp
    src/tile.cpp
    src/variantBasic.cpp
    src/variantQuadrant.cpp
    src/variant.cpp
)

# Link gtest to test executable
target_link_libraries(test_basic
    GTest::gtest
    GTest::gtest_main
)

# Register tests
add_test(NAME BasicGameTest COMMAND test_basic)

# Add custom targets for convenience
add_custom_target(run_tests COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
add_custom_target(run COMMAND ${CMAKE_BINARY_DIR}/fourteen_minesolver)


