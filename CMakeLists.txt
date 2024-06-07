cmake_minimum_required(VERSION 3.10)

project(Emerald-EM)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build the ROM
set(EMERALD_ROM "${CMAKE_SOURCE_DIR}/emerald/pokeemerald.gba")
set(EMERALD_SYM "${CMAKE_SOURCE_DIR}/emerald/pokeemerald.sym")

add_custom_target(
  emerald ALL
  COMMAND make -j32 rom
  BYPRODUCTS ${EMERALD_ROM} ${EMERALD_SYM}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/emerald
  COMMENT "Building the ROM"
  USES_TERMINAL
  VERBATIM
)

add_custom_target(data ALL)

function(build_lang lang)
  set(TARGET "data-lang-${lang}")
  set(TARGET_OUTPUT "${CMAKE_BINARY_DIR}/data/${lang}.bin")
  file(GLOB_RECURSE LANG_SOURCES "${CMAKE_SOURCE_DIR}/data/text/${lang}/*")
  add_custom_command(
    OUTPUT ${TARGET_OUTPUT}
    COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/make_lang.py ${lang}
    DEPENDS ${EMERALD_SYM} ${LANG_SOURCES} ${CMAKE_SOURCE_DIR}/scripts/make_lang.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building ${lang} data"
    VERBATIM
  )
  add_custom_target(
    ${TARGET}
    DEPENDS ${TARGET_OUTPUT}
  )
  add_dependencies(data ${TARGET})
endfunction()

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
add_custom_target(
  data-offsets
  DEPENDS ${OFFSETS_FILE}
)
add_dependencies(data data-offsets)

include_directories(src)
add_subdirectory(src)
