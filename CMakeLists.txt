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
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.5.0
)

set(COMPONENT_TARGETS_ENABLED NO)
set(PROJECT_NAMESPACE ${PROJECT_NAME})
set(NAMESPACE_HEADER_LOCATION ${PROJECT_SOURCE_DIR}/include)

if(NOT COMPONENT_TARGETS_ENABLED)
  message(STATUS "Install only 1 cmake config target ${PROJECT_NAMESPACE}Targets.cmake file")
endif()

# ---- Add components libraries here ----

add_subdirectory(source/Addition)
add_subdirectory(source/SquareRoot)
add_subdirectory(source/MathFunctions)

# ---------------------------------------

include(GenerateExportHeader)

# Note: depends on target MathFunctions! CK
string(TOLOWER ${PROJECT_NAME}/${PROJECT_NAMESPACE}_export.h EXPORT_HEADER_LOCATION)

# Note: need to generate at source tree! CK
generate_export_header(
  ${PROJECT_NAMESPACE} EXPORT_FILE_NAME ${PROJECT_SOURCE_DIR}/include/${EXPORT_HEADER_LOCATION}
)

# install generated header files
string(TOLOWER ${PROJECT_NAMESPACE} HEADER_LOCATION)
install(
  DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/${HEADER_LOCATION}
  TYPE INCLUDE # or: DESTINATION include/${PROJECT_NAMESPACE}
  FILES_MATCHING
  PATTERN "*.h"
)

# install source tree header files
install(
  DIRECTORY include/${HEADER_LOCATION}
  TYPE INCLUDE # or: DESTINATION include/${PROJECT_NAMESPACE}
  FILES_MATCHING
  PATTERN "*.h"
)

# Note: This needs to be done after all install(TARGETS ...) commands! generate and install export
# file
install(
  EXPORT ${PROJECT_NAMESPACE}Targets
  FILE ${PROJECT_NAMESPACE}Targets.cmake
  NAMESPACE ${PROJECT_NAMESPACE}::
  DESTINATION lib/cmake/${PROJECT_NAMESPACE}
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

# generate the export targets for the build tree. Note: The file created by this command is specific
# to the build tree and should never be installed!
export(
  EXPORT ${PROJECT_NAMESPACE}Targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAMESPACE}Targets.cmake
  NAMESPACE ${PROJECT_NAMESPACE}::
)

# install cmake project config files
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake
        DESTINATION lib/cmake/MathFunctions
)
