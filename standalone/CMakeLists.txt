cmake_minimum_required(VERSION 3.14...3.20)

project(MathFunctionsStandalone LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

#CPMAddPackage(
#  NAME cxxopts
#  GITHUB_REPOSITORY jarro2783/cxxopts
#  VERSION 2.2.0
#  OPTIONS "CXXOPTS_BUILD_EXAMPLES Off" "CXXOPTS_BUILD_TESTS Off"
#)

CPMAddPackage(
  NAME fmt
  GIT_TAG 7.1.3
  GITHUB_REPOSITORY fmtlib/fmt # to get an installable target
  OPTIONS "FMT_INSTALL YES"
)

CPMAddPackage(NAME MathFunctions SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
# Not same as! add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/.. MathFunctions)

# ---- Create standalone executable ----

set(sources source/main.cxx)

add_executable(MathFunctionsStandalone ${sources})
set_target_properties(MathFunctionsStandalone PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})

# WORKAROUND missing ALIAS target error! CK
#if(NOT TARGET cxxopts::cxxopts)
#  add_library(cxxopts::cxxopts ALIAS cxxopts)
#endif()

target_link_libraries(
  MathFunctionsStandalone MathFunctions::Addition MathFunctions::SquareRoot fmt::fmt
)

# ---- run the standalone executable ----
enable_testing()
add_test(NAME MathFunctionsStandalone COMMAND MathFunctionsStandalone 49.0)
