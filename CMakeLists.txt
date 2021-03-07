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

CPMAddPackage(
  NAME fmt
  GIT_TAG 7.1.3
  GITHUB_REPOSITORY fmtlib/fmt # to get an installable target
  OPTIONS "FMT_INSTALL YES"
)

# XXX set(COMPONET_TARGETS_ENABLED YES)
set(PROJECT_NAMESPACE ${PROJECT_NAME})
if(NOT DEFINED COMPONET_TARGETS_ENABLED)
  message(STATUS "Install only 1 cmake Component ${PROJECT_NAMESPACE}Targets.cmake config file")
  set(NAMESPACE_HEADER_LOCATION ${CMAKE_CURRENT_LIST_DIR}/include)

  add_subdirectory(source/Addition)
  add_subdirectory(source/SquareRoot)
  add_subdirectory(source/MathFunctions)

  # NO! include(source/CMakeLists.txt)

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

  # generate the export targets for the build tree. Note: This needs to be done after the all
  # install(TARGETS ...) commands!
  export(
    EXPORT MathFunctionsTargets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsTargets.cmake
    NAMESPACE MathFunctions::
  )

  # install cmake project config files
  install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake
          ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake
          ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsTargets.cmake
    DESTINATION lib/cmake/MathFunctions
  )
else()
  # ---- Add source files ----

  # Note: globbing sources is considered bad practice as CMake's generators may not detect new files
  # automatically. Keep that in mind when changing files, or explicitly mention them here.
  file(GLOB_RECURSE headers CONFIGURE_DEPENDS include/*.h)
  file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/MathFunctions/*.cxx)

  # ---- Create library ----

  # Note: for header-only libraries change all PUBLIC flags to INTERFACE and create an interface
  # target! EITHER: add_library(MathFunctions INTERFACE) OR:
  add_library(MathFunctions ${headers} ${sources})
  set_target_properties(MathFunctions PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})

  # for SameMajorVersion upgrade stategie
  set_target_properties(MathFunctions PROPERTIES SOVERSION 1 VERSION ${PROJECT_VERSION})

  # being a cross-platform target, we enforce standards conformance on MSVC:
  target_compile_options(MathFunctions PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive>")

  # Link dependencies EITHER:
  target_link_libraries(MathFunctions PRIVATE $<BUILD_INTERFACE:fmt::fmt-header-only>)
  # OR: target_link_libraries(MathFunctions PUBLIC fmt::fmt)

  set(INCLUDE_INSTALL_DIR include/${PROJECT_NAME}-${PROJECT_VERSION})
  target_include_directories(
    MathFunctions BEFORE PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>
  )

  # ---- Create an installable target ----
  # this allows users to install and find the library via `find_package()`.

  # the location where the project's version header will be placed should match the project's
  # regular header paths
  string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)
  string(TOLOWER ${PROJECT_NAME}/MathFunctions_export.h EXPORT_HEADER_LOCATION)

  # TODO: should be done in packageProject()
  include(GenerateExportHeader)
  generate_export_header(
    ${PROJECT_NAME} EXPORT_FILE_NAME PackageProjectInclude/${EXPORT_HEADER_LOCATION}
  )
  # Note: the export header will be installed while installing the version header! CK

  packageProject(
    NAME ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    NAMESPACE ${PROJECT_NAME}
    BINARY_DIR ${PROJECT_BINARY_DIR}
    INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
    INCLUDE_DESTINATION ${INCLUDE_INSTALL_DIR}
    VERSION_HEADER ${VERSION_HEADER_LOCATION}
    COMPATIBILITY SameMajorVersion
    # Note: not needed DEPENDENCIES "fmt 7.1.3"
  )
endif()
