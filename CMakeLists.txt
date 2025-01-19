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

  ${CMAKE_CURRENT_SOURCE_DIR}/Materials/Color.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Materials/Material.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Materials/Pattern.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Materials/Stripes.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Materials/Gradient.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Materials/Checker.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Materials/Ring.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/Math/Tuple.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Math/Floats.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Math/Matrix.cpp
  
  ${CMAKE_CURRENT_SOURCE_DIR}/Parse/PPM.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/Shapes/Shape.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Shapes/Plane.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Shapes/Sphere.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Shapes/Intersection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Shapes/Ray.cpp
  
  ${CMAKE_CURRENT_SOURCE_DIR}/World/Camera.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/World/Canvas.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/World/Light.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/World/World.cpp
)


set(exsources

  ${CMAKE_CURRENT_SOURCE_DIR}/exercises/001_red_circle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/exercises/002_purple_ball.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/exercises/003_camera.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/exercises/004_plane.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/exercises/005_patterns.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/exercises/006_glass.cpp
)

add_executable(
  ${CMAKE_PROJECT_NAME}
  main.cpp
  ${sources}
  ${exsources}

)

# include exercises only in the main program and not in tests
target_include_directories(
  ${CMAKE_PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/exercises
)

include_directories(
  ${CMAKE_PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/Materials
  ${CMAKE_CURRENT_SOURCE_DIR}/Math
  ${CMAKE_CURRENT_SOURCE_DIR}/Parse
  ${CMAKE_CURRENT_SOURCE_DIR}/Shapes
  ${CMAKE_CURRENT_SOURCE_DIR}/World
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
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Math/Matrix_tests.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Materials/Pattern_tests.cpp
  
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Parse/PPM_test.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Shapes/Intersection_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Shapes/Plane_tests.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Shapes/Sphere_tests.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Shapes/Ray_test.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/tests/World/Camera_tests.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/World/World_tests.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/World/Light_tests.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/World/Canvas_tests.cpp
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
