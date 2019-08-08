# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_health_metric_collector_node_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED health_metric_collector_node_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(health_metric_collector_node_FOUND FALSE)
  elseif(NOT health_metric_collector_node_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(health_metric_collector_node_FOUND FALSE)
  endif()
  return()
endif()
set(_health_metric_collector_node_CONFIG_INCLUDED TRUE)

# output package information
if(NOT health_metric_collector_node_FIND_QUIETLY)
  message(STATUS "Found health_metric_collector_node: 1.0.0 (${health_metric_collector_node_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'health_metric_collector_node' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  message(WARNING "${_msg}")
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(health_metric_collector_node_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${health_metric_collector_node_DIR}/${_extra}")
endforeach()
