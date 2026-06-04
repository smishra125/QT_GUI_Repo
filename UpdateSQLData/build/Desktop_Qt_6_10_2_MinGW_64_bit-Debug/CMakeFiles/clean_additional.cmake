# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\UpdateSQLData_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\UpdateSQLData_autogen.dir\\ParseCache.txt"
  "UpdateSQLData_autogen"
  )
endif()
