cmake_minimum_required(VERSION 3.14...3.20)

# ---- Project ----

# Note: update this to your new project's name and version
project(
  MathFunctions
  VERSION 1.0.0
  LANGUAGES CXX
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) \
and run CMake from there."
  )
endif()

# ---- Project settings ----

include(cmake/options.cmake)

# ---- Add dependencies via CPM ----
# see https://github.com/cpm-cmake/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY ClausKlein/PackageProject.cmake
  # VERSION CK1.6.0
  GIT_TAG 4ac95860ba72bb0eb324c4d63e35fb59be3bd50d
)

set(COMPONENT_TARGETS_ENABLED NO) # Note: DO not set! CK
set(PROJECT_NAMESPACE ${PROJECT_NAME})
set(PROJECT_VERSION_INCLUDE_DIR ${PROJECT_BINARY_DIR}/PackageProjectInclude)
include_directories(${PROJECT_VERSION_INCLUDE_DIR})

set(NAMESPACE_HEADER_LOCATION ${CMAKE_CURRENT_LIST_DIR}/include)
set(INCLUDE_INSTALL_DIR include/${PROJECT_NAMESPACE}-${PROJECT_VERSION}) # XXX VERSION_SUFFIX
string(TOLOWER ${PROJECT_NAMESPACE} PROJECT_HEADER_LOCATION)
# TODO: needed to be lower case? CK

# ---- Add components libraries here ----

add_subdirectory(source/Addition)
add_subdirectory(source/SquareRoot)

# NO! add_subdirectory(source/MathFunctions)
add_library(${PROJECT_NAME} source/MathFunctions/MathFunctions.cxx)
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${NAMESPACE_HEADER_LOCATION}>
                         $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>
)

# Note: for SameMajorVersion upgrade stategie
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR}
             VERSION ${PROJECT_VERSION}
             VISIBILITY_INLINES_HIDDEN ${BUILD_SHARED_LIBS}
             CMAKE_VISIBILITY_INLINES_HIDDEN ${BUILD_SHARED_LIBS}
)

# ---- Create an installable target ----
# this allows users to install and find the libraries via `find_package()`.

# the location where the project's version header will be placed should match the project's regular
# header paths
string(TOLOWER ${PROJECT_NAMESPACE}/version.h PROJECT_VERSION_HEADER)
string(TOLOWER ${PROJECT_NAMESPACE}/${PROJECT_NAMESPACE}_export.h PROJECT_EXPORT_HEADER)
# TODO: needed to be lower case? CK

# Note: This needs to be done after all install(TARGETS ...) commands!
# generate and install export targets file
install(
  EXPORT ${PROJECT_NAMESPACE}Targets
  FILE ${PROJECT_NAMESPACE}Targets.cmake
  NAMESPACE ${PROJECT_NAMESPACE}::
  DESTINATION lib/cmake/${PROJECT_NAMESPACE}-${PROJECT_VERSION} # XXX VERSION_SUFFIX
)

# Note: the export header will be installed while installing the version header! CK
packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAMESPACE}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${NAMESPACE_HEADER_LOCATION}
  INCLUDE_DESTINATION ${INCLUDE_INSTALL_DIR}
  VERSION_HEADER ${PROJECT_VERSION_HEADER}
  EXPORT_HEADER ${PROJECT_EXPORT_HEADER}
  COMPATIBILITY SameMajorVersion # XXX DISABLE_VERSION_SUFFIX NOT YET! CK
                DISABLE_CHECK_REQUIRED_COMPONENTS YES
)

# generate the export targets for the build tree. Note: The file created by this command is specific
# to the build tree and should never be installed!
export(
  EXPORT ${PROJECT_NAMESPACE}Targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAMESPACE}Targets.cmake
  NAMESPACE ${PROJECT_NAMESPACE}::
)
