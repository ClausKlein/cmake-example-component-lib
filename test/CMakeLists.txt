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

# CPMAddPackage( NAME doctest GITHUB_REPOSITORY onqtam/doctest GIT_TAG 2.4.5)

if(TEST_INSTALLED_VERSION)
  find_package(MathFunctions ${PROJECT_VERSION} REQUIRED)
else()
  CPMAddPackage(NAME MathFunctions SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
endif()

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS source/*.cxx)
add_executable(MathFunctionsTests ${sources})
# target_link_libraries(MathFunctionsTests doctest::doctest MathFunctions::MathFunctions)
set_target_properties(MathFunctionsTests PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(MathFunctions PUBLIC -Wall -Wextra -Werror)
  elseif(MSVC)
    target_compile_options(MathFunctions PUBLIC /W4 /WX)
    target_compile_definitions(MathFunctionsTests PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
  endif()
endif()

# ---- Add MathFunctionsTests ----

enable_testing()

add_test(NAME MathFunctionsTests COMMAND MathFunctionsTests -s false)

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE AND NOT MathFunctions_FOUND)
  target_compile_options(MathFunctions PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(MathFunctions PUBLIC -fprofile-arcs -ftest-coverage)
endif()
