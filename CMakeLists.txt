cmake_minimum_required(VERSION 3.10)

project(Emerald-EM)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17")

# Build the ROM
set(EMERALD_ROM "${CMAKE_SOURCE_DIR}/emerald/pokeemerald.gba")
set(EMERALD_SYM "${CMAKE_SOURCE_DIR}/emerald/pokeemerald.sym")
set(DATA_FILES "")

add_custom_target(
  emerald ALL
  COMMAND make -j32 rom
  BYPRODUCTS ${EMERALD_ROM} ${EMERALD_SYM}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/emerald
  COMMENT "Building the ROM"
  USES_TERMINAL
  VERBATIM
)

macro(build_lang lang)
  file(GLOB_RECURSE _lang_sources "${CMAKE_SOURCE_DIR}/data/text/${lang}/*.txt")
  set(_lang_output "${CMAKE_BINARY_DIR}/data/${lang}.bin")

  add_custom_command(
    OUTPUT ${_lang_output}
    COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/make_lang.py ${lang}
    DEPENDS ${EMERALD_SYM} ${_lang_sources} ${CMAKE_SOURCE_DIR}/scripts/make_lang.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building ${lang} data"
    VERBATIM
  )
  list(APPEND DATA_FILES ${_lang_output})
endmacro()

build_lang("en_US")
build_lang("fr_FR")

# Offsets
set(OFFSETS_FILE "${CMAKE_BINARY_DIR}/data/offsets.bin")
add_custom_command(
  OUTPUT ${OFFSETS_FILE}
  COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/make_offsets.py
  DEPENDS ${EMERALD_SYM} ${CMAKE_SOURCE_DIR}/scripts/make_offsets.py
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Building offsets"
  VERBATIM
)
list(APPEND DATA_FILES ${OFFSETS_FILE})

include_directories(src)
add_subdirectory(src)

# Copy data
add_custom_target(
  data ALL
  DEPENDS ${DATA_FILES} ${EMERALD_ROM}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/data ${CMAKE_BINARY_DIR}/bin/data
  COMMAND ${CMAKE_COMMAND} -E copy ${EMERALD_ROM} ${CMAKE_BINARY_DIR}/bin/emerald-em.gba
  COMMENT "Copying data files"
  VERBATIM
)
