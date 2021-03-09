cmake_minimum_required(VERSION 3.14...3.20)

project(
  MathFunctionsTests
  VERSION 1
  LANGUAGES CXX
)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME ut
  GITHUB_REPOSITORY boost-ext/ut
  GIT_TAG 1cc75c234d4005031cee581102a4a6c8b680df0a
)

if(TEST_INSTALLED_VERSION)
  find_package(
    MathFunctions ${PROJECT_VERSION}
    COMPONENTS Addition SquareRoot
    REQUIRED
  )
else()
  CPMAddPackage(NAME MathFunctions SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
  # same as: add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/.. MathFunctions)
endif()

CPMAddPackage(
  NAME Format.cmake
  GITHUB_REPOSITORY TheLartians/Format.cmake
  VERSION 1.6
  OPTIONS # enable cmake formatting
          "FORMAT_CHECK_CMAKE ON"
)

# ---- Create binary ----

add_executable(MathFunctionsTests source/main.cxx)
# target_link_libraries(MathFunctionsTests doctest::doctest MathFunctions::MathFunctions)
target_link_libraries(
  MathFunctionsTests Boost::ut MathFunctions::Addition MathFunctions::SquareRoot
)
set_target_properties(MathFunctionsTests PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})

# ---- Add MathFunctionsTests ----

enable_testing()

add_test(NAME MathFunctionsTests COMMAND MathFunctionsTests 2.0)

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE AND NOT MathFunctions_FOUND)
  target_compile_options(MathFunctions PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(MathFunctions PUBLIC -fprofile-arcs -ftest-coverage)
endif()
