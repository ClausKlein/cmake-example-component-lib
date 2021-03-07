#
# create a component library like boost
#
add_library(SquareRoot STATIC SquareRoot.cxx)

add_library(${PROJECT_NAMESPACE}::SquareRoot ALIAS SquareRoot)

# add include directories
target_include_directories(
  SquareRoot PUBLIC $<BUILD_INTERFACE:${NAMESPACE_HEADER_LOCATION}> $<INSTALL_INTERFACE:include>
)

# install the target and create export-set
install(
  TARGETS SquareRoot
  EXPORT ${PROJECT_NAMESPACE}Targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include
)

# install header file
# string(TOLOWER ${PROJECT_NAMESPACE} HEADER_LOCATION)
# install(FILES ${NAMESPACE_HEADER_LOCATION}/${PROJECT_NAMESPACE}/SquareRoot.h DESTINATION include/${PROJECT_NAMESPACE})

if(DEFINED COMPONENT_TARGETS_ENABLED)
  # generate and install export file
  install(
    EXPORT ${PROJECT_NAMESPACE}Targets
    FILE ${PROJECT_NAMESPACE}SquareRootTargets.cmake
    NAMESPACE ${PROJECT_NAMESPACE}::
    DESTINATION lib/cmake/${PROJECT_NAMESPACE}
  )
endif()
