#
# create a component library like boost
#
add_library(
  SquareRoot SquareRoot.cxx ${NAMESPACE_HEADER_LOCATION}/${PROJECT_NAMESPACE}/SquareRoot.h
)

add_library(${PROJECT_NAMESPACE}::SquareRoot ALIAS SquareRoot)

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
  SquareRoot PUBLIC $<BUILD_INTERFACE:${NAMESPACE_HEADER_LOCATION}> $<INSTALL_INTERFACE:include>
)

# install the target and create export-set
install(
  TARGETS SquareRoot
  EXPORT ${PROJECT_NAMESPACE}Targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include
)

# MAYBE: install public header files
# string(TOLOWER ${PROJECT_NAMESPACE} HEADER_LOCATION)
# install(FILES ${NAMESPACE_HEADER_LOCATION}/${PROJECT_NAMESPACE}/SquareRoot.h
#         DESTINATION include/${PROJECT_NAMESPACE}
# )

if(COMPONENT_TARGETS_ENABLED)
  # generate and install export file
  install(
    EXPORT ${PROJECT_NAMESPACE}Targets
    FILE ${PROJECT_NAMESPACE}SquareRootTargets.cmake
    NAMESPACE ${PROJECT_NAMESPACE}::
    DESTINATION lib/cmake/${PROJECT_NAMESPACE}
  )
endif()
