# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ShieldManager_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ShieldManager_autogen.dir\\ParseCache.txt"
  "ShieldManager_autogen"
  )
endif()
