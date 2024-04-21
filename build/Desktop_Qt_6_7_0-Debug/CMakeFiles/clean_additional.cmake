# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/CSE165Platformer_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/CSE165Platformer_autogen.dir/ParseCache.txt"
  "CSE165Platformer_autogen"
  )
endif()
