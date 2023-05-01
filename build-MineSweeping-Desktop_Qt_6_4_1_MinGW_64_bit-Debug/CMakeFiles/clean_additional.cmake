# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MineSweeping_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MineSweeping_autogen.dir\\ParseCache.txt"
  "MineSweeping_autogen"
  )
endif()
