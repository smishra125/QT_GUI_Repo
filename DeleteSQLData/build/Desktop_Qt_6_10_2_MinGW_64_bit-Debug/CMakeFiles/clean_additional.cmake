# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DeleteDataSQLData_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DeleteDataSQLData_autogen.dir\\ParseCache.txt"
  "DeleteDataSQLData_autogen"
  )
endif()
