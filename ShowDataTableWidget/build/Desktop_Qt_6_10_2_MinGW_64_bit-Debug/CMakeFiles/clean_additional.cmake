# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ShowDataTableWidget_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ShowDataTableWidget_autogen.dir\\ParseCache.txt"
  "ShowDataTableWidget_autogen"
  )
endif()
