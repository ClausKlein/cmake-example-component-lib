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
  # VERSION 1.5.1
  GIT_TAG 43fccf1a2f8f3d8dbecd547485c2278035448171
)

option(COMPONENT_TARGETS_ENABLED "Install multiple cmake config target files" NO)
set(PROJECT_NAMESPACE ${PROJECT_NAME})
set(NAMESPACE_HEADER_LOCATION ${CMAKE_CURRENT_LIST_DIR}/include)
set(INCLUDE_INSTALL_DIR include/${PROJECT_NAMESPACE}-${PROJECT_VERSION})
string(TOLOWER ${PROJECT_NAMESPACE} PROJECT_HEADER_LOCATION)
# TBD: needed to be lower case? CK

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
string(TOLOWER ${PROJECT_NAMESPACE}/version.h VERSION_HEADER_LOCATION)
string(TOLOWER ${PROJECT_NAMESPACE}/${PROJECT_NAMESPACE}_export.h EXPORT_HEADER_LOCATION)
# TBD: needed to be lower case? CK

include(GenerateExportHeader)

# TODO: need to generate at source tree! CK
generate_export_header(
  ${PROJECT_NAMESPACE} EXPORT_FILE_NAME ${NAMESPACE_HEADER_LOCATION}/${EXPORT_HEADER_LOCATION}
)

# Note: This needs to be done after all install(TARGETS ...) commands!
# generate and install export targets file
install(
  EXPORT ${PROJECT_NAMESPACE}Targets
  FILE ${PROJECT_NAMESPACE}Targets.cmake
  NAMESPACE ${PROJECT_NAMESPACE}::
  DESTINATION lib/cmake/${PROJECT_NAMESPACE}-${PROJECT_VERSION}
)

if(NOT COMPONENT_TARGETS_ENABLED)
  message(STATUS "Install only 1 cmake config target ${PROJECT_NAMESPACE}Targets.cmake file")

  # Note: the export header will be installed while installing the version header! CK
  packageProject(
    NAME ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    NAMESPACE ${PROJECT_NAMESPACE}
    BINARY_DIR ${PROJECT_BINARY_DIR}
    INCLUDE_DIR ${NAMESPACE_HEADER_LOCATION}
    INCLUDE_DESTINATION ${INCLUDE_INSTALL_DIR}
    VERSION_HEADER ${VERSION_HEADER_LOCATION}
    EXPORT_HEADER ${EXPORT_HEADER_LOCATION}
    COMPATIBILITY SameMajorVersion #XXX DISABLE_VERSION_SUFFIX YES
                  DISABLE_CHECK_REQUIRED_COMPONENTS YES
  )
else()

  # install generated header files
  install(
    DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_HEADER_LOCATION}
    TYPE INCLUDE # or: DESTINATION ${INCLUDE_INSTALL_DIR}
    FILES_MATCHING
    PATTERN "*.h"
  )

  # install source tree header files
  install(
    DIRECTORY include/${PROJECT_HEADER_LOCATION}
    TYPE INCLUDE # or: DESTINATION ${INCLUDE_INSTALL_DIR}
    FILES_MATCHING
    PATTERN "*.h"
  )

  include(CMakePackageConfigHelpers)

  # generate the version file for the config file
  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAMESPACE}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
  )

  # create config file
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAMESPACE}Config.cmake
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAMESPACE}
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )

  # install cmake project config files
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake
                ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake
          DESTINATION lib/cmake/${PROJECT_NAMESPACE}
  )
endif()

# generate the export targets for the build tree. Note: The file created by this command is specific
# to the build tree and should never be installed!
export(
  EXPORT ${PROJECT_NAMESPACE}Targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAMESPACE}Targets.cmake
  NAMESPACE ${PROJECT_NAMESPACE}::
)
