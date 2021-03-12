cmake_minimum_required(VERSION 3.14...3.20)

project(MathFunctionsStandalone LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME fmt
  GIT_TAG 7.1.3
  GITHUB_REPOSITORY fmtlib/fmt # to get an installable target
  OPTIONS "FMT_INSTALL YES"
)

CPMAddPackage(NAME MathFunctions SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
# Not same as! add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/.. MathFunctions)

# ---- Create standalone executable ----

add_executable(MathFunctionsCalculator source/calc.cxx)
set_target_properties(MathFunctionsCalculator PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})
target_link_libraries(MathFunctionsCalculator MathFunctions::MathFunctions fmt::fmt)

add_executable(MathFunctionsStandalone source/main.cxx)
set_target_properties(MathFunctionsStandalone PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})
target_link_libraries(
  MathFunctionsStandalone MathFunctions::Addition MathFunctions::SquareRoot fmt::fmt
)

# ---- run the standalone executable ----
enable_testing()

add_test(NAME MathFunctionsCalculator COMMAND MathFunctionsCalculator 2)

add_test(NAME MathFunctionsStandaloneHint COMMAND MathFunctionsStandalone)
add_test(NAME MathFunctionsStandaloneOops COMMAND MathFunctionsStandalone Oops ...)
add_test(NAME MathFunctionsStandalone COMMAND MathFunctionsStandalone 49.0)
add_test(NAME MathFunctionsStandaloneNaN COMMAND MathFunctionsStandalone -1)
