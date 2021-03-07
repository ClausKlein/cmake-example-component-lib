#
# create a component library like boost
#
add_library(MathFunctions STATIC MathFunctions.cxx)

add_library(MathFunctions::MathFunctions ALIAS MathFunctions)

# add include directories
target_include_directories(
  MathFunctions PUBLIC $<BUILD_INTERFACE:${NAMESPACE_HEADER_LOCATION}>
                       $<INSTALL_INTERFACE:include>
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

if(DEFINED COMPONET_TARGETS_ENABLED)
  # generate and install export file
  install(
    EXPORT MathFunctionsTargets
    FILE ${PROJECT_NAMESPACE}MathFunctionsTargets.cmake
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
