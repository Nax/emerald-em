file(GLOB_RECURSE SOURCES "*.cpp")
add_executable(shuffler ${SOURCES})
add_dependencies(shuffler emerald data)

add_custom_target(
  data-copy ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/data ${CMAKE_BINARY_DIR}/bin/data
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/emerald/pokeemerald.gba ${CMAKE_BINARY_DIR}/bin/data/rom.gba
  COMMENT "Copying data files"
  VERBATIM
)

add_dependencies(data-copy shuffler)
