cmake_minimum_required(VERSION 3.15...3.20)

# Note: set version PROJECT_VERSION her! CK
project(
  MathFunctions
  VERSION 1.2.3
  LANGUAGES CXX
)

# Determine if the project is built as a subproject (using add_subdirectory) or if it is the master
# project.
set(MASTER_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MASTER_PROJECT ON)

  # specify the C++ standard
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED True)
endif()

# create library
add_library(MathFunctions STATIC MathFunctions.cxx MathFunctions.h)

add_library(MathFunctions::MathFunctions ALIAS MathFunctions)

# add include directories
target_include_directories(
  MathFunctions PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
)

# install the target and create export-set
install(
  TARGETS MathFunctions
  EXPORT MathFunctionsTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include
)

# Note: install header file to lower case namespace location! CK
install(FILES MathFunctions.h DESTINATION include/mathfunctions)

if(DEFINED COMPONET_TARGETS_ENABLED)
  # generate and install export file
  install(
    EXPORT MathFunctionsTargets
    FILE ${namespace}MathFunctionsTargets.cmake
    NAMESPACE MathFunctions::
    DESTINATION lib/cmake/MathFunctions
  )
endif()

set_property(TARGET MathFunctions PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET MathFunctions PROPERTY SOVERSION 3)
set_property(TARGET MathFunctions PROPERTY INTERFACE_MathFunctions_MAJOR_VERSION 3)
set_property(
  TARGET MathFunctions
  APPEND
  PROPERTY COMPATIBLE_INTERFACE_STRING MathFunctions_MAJOR_VERSION
)

if(MASTER_PROJECT OR DEFINED COMPONET_TARGETS_ENABLED)
  include(CMakePackageConfigHelpers)

  # generate the version file for the config file
  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
  )

  # create config file
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake
    INSTALL_DESTINATION lib/cmake/MathFunctions
  )

  # install config files
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake
                ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake
          DESTINATION lib/cmake/MathFunctions
  )

  # generate the export targets for the build tree. Note: This needs to be done after the all
  # install(TARGETS ...) commands!
  export(
    EXPORT MathFunctionsTargets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/MathFunctionsTargets.cmake
    NAMESPACE MathFunctions::
  )
endif()
