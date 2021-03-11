#
# create a component library like boost
#
add_library(
  MathFunctions MathFunctions.cxx
                ${NAMESPACE_HEADER_LOCATION}/${PROJECT_HEADER_LOCATION}/MathFunctions.h
)

add_library(MathFunctions::MathFunctions ALIAS MathFunctions)

# Note: for SameMajorVersion upgrade stategie
set_target_properties(
  MathFunctions
  PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR}
             VERSION ${PROJECT_VERSION}
             VISIBILITY_INLINES_HIDDEN ${BUILD_SHARED_LIBS}
             CMAKE_VISIBILITY_INLINES_HIDDEN ${BUILD_SHARED_LIBS}
)

# add include directories
target_include_directories(
  MathFunctions PUBLIC $<BUILD_INTERFACE:${NAMESPACE_HEADER_LOCATION}>
                       $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>
)

# install the target and create export-set
install(
  TARGETS MathFunctions
  EXPORT MathFunctionsTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include
)

# MAYBE: install public header files
# install(FILES ${NAMESPACE_HEADER_LOCATION}/${PROJECT_NAMESPACE}/MathFunctions.h
#         DESTINATION ${INCLUDE_INSTALL_DIR}/${PROJECT_NAMESPACE}
# )

if(COMPONENT_TARGETS_ENABLED)
  # generate and install export file
  install(
    EXPORT MathFunctionsTargets
    FILE ${PROJECT_NAMESPACE}MathFunctionsTargets.cmake
    NAMESPACE MathFunctions::
    DESTINATION lib/cmake/MathFunctions
  )
endif()
