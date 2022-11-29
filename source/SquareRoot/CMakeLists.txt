#
# create a component library like boost
#
add_library(
  SquareRoot SquareRoot.cxx ${NAMESPACE_HEADER_LOCATION}/${PROJECT_HEADER_LOCATION}/SquareRoot.h
)

add_library(${PROJECT_NAMESPACE}::SquareRoot ALIAS SquareRoot) # NOTE: needed! CK

# Note: for SameMajorVersion upgrade stategie
set_target_properties(
  SquareRoot
  PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR}
             VERSION ${PROJECT_VERSION}
             VISIBILITY_INLINES_HIDDEN ${BUILD_SHARED_LIBS}
             CMAKE_VISIBILITY_INLINES_HIDDEN ${BUILD_SHARED_LIBS}
)

# add include directories
target_include_directories(
  SquareRoot
  PUBLIC $<BUILD_INTERFACE:${NAMESPACE_HEADER_LOCATION}>
         $<BUILD_INTERFACE:${PROJECT_VERSION_INCLUDE_DIR}>
         $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>
)

# NOTE: Need to install the target and create export-set manually! CK
install(
  TARGETS SquareRoot
  EXPORT ${PROJECT_NAMESPACE}Targets
  ARCHIVE DESTINATION lib/${PROJECT_NAMESPACE}-${PROJECT_VERSION} # XXX VERSION_SUFFIX
  LIBRARY DESTINATION lib/${PROJECT_NAMESPACE}-${PROJECT_VERSION} # XXX VERSION_SUFFIX
  RUNTIME DESTINATION bin/${PROJECT_NAMESPACE}-${PROJECT_VERSION} # XXX VERSION_SUFFIX
  INCLUDES
  DESTINATION ${INCLUDE_INSTALL_DIR}
)

# MAYBE: install public header files
# string(TOLOWER ${PROJECT_NAMESPACE} HEADER_LOCATION)
# install(FILES ${NAMESPACE_HEADER_LOCATION}/${PROJECT_NAMESPACE}/SquareRoot.h
#         DESTINATION ${INCLUDE_INSTALL_DIR}/${PROJECT_NAMESPACE}
# )

# if(COMPONENT_TARGETS_ENABLED)
#   # NOTE: generate and install export file for this target
#   install(
#     EXPORT ${PROJECT_NAMESPACE}Targets
#     FILE ${PROJECT_NAMESPACE}SquareRootTargets.cmake
#     NAMESPACE ${PROJECT_NAMESPACE}::
#     DESTINATION lib/cmake/${PROJECT_NAMESPACE}
#   )
# endif()
