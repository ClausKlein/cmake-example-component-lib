# only activate options for top level project
if(NOT PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  return()
endif()

# ---------------------------------------------------------------------------
# SECTION: LIBS
# ---------------------------------------------------------------------------
# Note: same postfix as fmt and spdlog! CK
set(CMAKE_DEBUG_POSTFIX d)

option(BUILD_SHARED_LIBS "Build shared libraries" YES)

# build the dynamic libraries and executables together at bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# ---------------------------------------------------------------------------

if(NOT DEFINED CMAKE_CXX_STANDARD)
  option(CXX_STANDARD_REQUIRED "Require c++ standard" YES)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_EXTENSIONS NO)
endif()

# this reduce build time if using Nina generators
option(CMAKE_DEPENDS_IN_PROJECT_ONLY "do NOT use system header files for dependency checking" YES)
if(NOT MSVC)
  if(CMAKE_DEPENDS_IN_PROJECT_ONLY)
    set(CMAKE_DEPFILE_FLAGS_C
        "-MMD"
        CACHE STRING "dependency flag" FORCE
    )
    set(CMAKE_DEPFILE_FLAGS_CXX
        "-MMD"
        CACHE STRING "dependency flag" FORCE
    )
  else()
    set(CMAKE_DEPFILE_FLAGS_C
        "-MD"
        CACHE STRING "dependency flag" FORCE
    )
    set(CMAKE_DEPFILE_FLAGS_CXX
        "-MD"
        CACHE STRING "dependency flag" FORCE
    )
  endif()

  option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
  if(ENABLE_TEST_COVERAGE AND "${CMAKE_BUILD_TYPE}" STREQUAL Debug)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
  endif()
endif()

option(CMAKE_EXPORT_COMPILE_COMMANDS "support clang-tidy, cppcheck, ..." YES)
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

include(${CMAKE_CURRENT_LIST_DIR}/WarningsAsErrors.cmake)
