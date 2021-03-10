#
# create a component library like boost
#
add_library(
  Addition Addition.cxx ${NAMESPACE_HEADER_LOCATION}/${PROJECT_HEADER_LOCATION}/Addition.h
)

add_library(${PROJECT_NAMESPACE}::Addition ALIAS Addition)

# Note: for SameMajorVersion upgrade stategie
set_target_properties(
  Addition
  PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR}
             VERSION ${PROJECT_VERSION}
             VISIBILITY_INLINES_HIDDEN ${BUILD_SHARED_LIBS}
             CMAKE_VISIBILITY_INLINES_HIDDEN ${BUILD_SHARED_LIBS}
)

# add include directories
target_include_directories(
  Addition PUBLIC $<BUILD_INTERFACE:${NAMESPACE_HEADER_LOCATION}> $<INSTALL_INTERFACE:include>
)

# install the target and create export-set
install(
  TARGETS Addition
  EXPORT ${PROJECT_NAMESPACE}Targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include
)

# MAYBE: install public header files
# string(TOLOWER ${PROJECT_NAMESPACE} HEADER_LOCATION)
# install(FILES ${NAMESPACE_HEADER_LOCATION}/${PROJECT_NAMESPACE}/Addition.h
#         DESTINATION include/${HEADER_LOCATION}
# )

if(COMPONENT_TARGETS_ENABLED)
  # generate and install export file
  install(
    EXPORT ${PROJECT_NAMESPACE}Targets
    FILE ${PROJECT_NAMESPACE}AdditionTargets.cmake
    NAMESPACE ${PROJECT_NAMESPACE}::
    DESTINATION lib/cmake/${PROJECT_NAMESPACE}
  )
endif()
