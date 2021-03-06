#
# create a component library like boost
#
add_library(Addition STATIC Addition.cxx Addition.h)

add_library(${namespace}::Addition ALIAS Addition)

# add include directories
target_include_directories(
  Addition PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
                  $<INSTALL_INTERFACE:include>
)

# install the target and create export-set
install(
  TARGETS Addition
  # XXX EXPORT AdditionTargets
  EXPORT ${namespace}Targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include
)

# install header file
string(TOLOWER ${namespace} HEADER_LOCATION)
install(FILES Addition.h DESTINATION include/${HEADER_LOCATION})

if(DEFINED COMPONET_TARGETS_ENABLED)
  # generate and install export file
  install(
    # XXX EXPORT AdditionTargets
    EXPORT ${namespace}Targets
    FILE ${namespace}AdditionTargets.cmake
    NAMESPACE ${namespace}::
    DESTINATION lib/cmake/${namespace}
  )
endif()
