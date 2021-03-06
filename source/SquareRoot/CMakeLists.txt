#
# create a component library like boost
#
add_library(SquareRoot STATIC SquareRoot.cxx SquareRoot.h)

add_library(${namespace}::SquareRoot ALIAS SquareRoot)

# add include directories
target_include_directories(
  SquareRoot PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
                    $<INSTALL_INTERFACE:include>
)

# install the target and create export-set
install(
  TARGETS SquareRoot
  # XXX EXPORT SquareRootTargets
  EXPORT ${namespace}Targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include
)

# install header file
string(TOLOWER ${namespace} HEADER_LOCATION)
install(FILES SquareRoot.h DESTINATION include/${HEADER_LOCATION})

if(DEFINED COMPONET_TARGETS_ENABLED)
  # generate and install export file
  install(
    # XXX EXPORT SquareRootTargets
    EXPORT ${namespace}Targets
    FILE ${namespace}SquareRootTargets.cmake
    NAMESPACE ${namespace}::
    DESTINATION lib/cmake/${namespace}
  )
endif()
