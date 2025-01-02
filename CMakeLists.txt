cmake_minimum_required(VERSION 3.14)
# From GoogleTest Quickstart

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# create compile_commands.json 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project
project(trace-rays)

enable_testing()

set(sources ${sources}

    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Tuple.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Floats.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Math/Matrix.cpp
)

add_executable(
    ${CMAKE_PROJECT_NAME}
    main.cpp
    ${sources}

)

include_directories(
  ${CMAKE_PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/Math
)



# Tests
include(FetchContent)
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(test_sources ${test_sources}

  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Math/Tuple_tests.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Math/Floats_tests.cpp
)

add_executable(
    ${CMAKE_PROJECT_NAME}_test 
    main_test.cpp
    ${sources}
    ${test_sources}
)

target_link_libraries( 
    ${CMAKE_PROJECT_NAME}_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME}_test)
