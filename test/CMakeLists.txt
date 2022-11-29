cmake_minimum_required(VERSION 3.21...3.25)

project(
  MathFunctionsTests
  VERSION 1
  LANGUAGES CXX
)

# ---- Options ----

option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.10.0")

CPMAddPackage(
  NAME ut
  GITHUB_REPOSITORY boost-ext/ut
  GIT_TAG v1.1.9
  OPTIONS "BOOST_UT_DISABLE_MODULE ON"
)

if(TEST_INSTALLED_VERSION)
  find_package(
    MathFunctions ${PROJECT_VERSION}
    COMPONENTS Addition SquareRoot
    REQUIRED
  )
else()
  CPMAddPackage(NAME MathFunctions SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
  # Not same as! add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/.. MathFunctions)
endif()

CPMAddPackage(
  NAME Format.cmake
  GITHUB_REPOSITORY TheLartians/Format.cmake
  VERSION 1.7.0
  OPTIONS # skip cmake formatting
          "FORMAT_SKIP_CMAKE ON"
)

# ---- Create binary ----

add_executable(MathFunctionsTests source/main.cxx)
target_link_libraries(
  MathFunctionsTests Boost::ut MathFunctions::Addition MathFunctions::SquareRoot
)
set_target_properties(MathFunctionsTests PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})

# ---- Add MathFunctionsTests ----

enable_testing()

add_test(NAME MathFunctionsTests COMMAND MathFunctionsTests 2.0)
