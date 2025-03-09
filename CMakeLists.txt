cmake_minimum_required(VERSION 3.10)

project(Emerald-EM)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(USE_DOCKER_DEFAULT OFF)
set(BUILD_GUI_DEFAULT OFF)

if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17")
else()
  set(USE_DOCKER_DEFAULT ON)
  set(BUILD_GUI_DEFAULT ON)
endif()

option(EXTERNAL_DATA "" "")
option(USE_DOCKER "" "${USE_DOCKER_DEFAULT}")
option(ORIGINAL_ROM "Path to the original ROM" "")
option(BUILD_GUI "Build the GUI" "${BUILD_GUI_DEFAULT}")

set(BASEROM_STAMP "${CMAKE_BINARY_DIR}/baserom.stamp")
set(EMERALD_ROM "${CMAKE_SOURCE_DIR}/emerald/pokeemerald.gba")
set(EMERALD_SYM "${CMAKE_SOURCE_DIR}/emerald/pokeemerald.sym")

if (NOT EXTERNAL_DATA)
  find_package(Python3 REQUIRED)
  if (USE_DOCKER)
    file(GLOB_RECURSE BASEROM_SOURCES "${CMAKE_SOURCE_DIR}/emerald/*")
    list(REMOVE_ITEM BASEROM_SOURCES "${EMERALD_ROM}")
    list(REMOVE_ITEM BASEROM_SOURCES "${EMERALD_SYM}")
    add_custom_command(
      OUTPUT "${BASEROM_STAMP}"
      COMMAND docker build . -t emerald-em-builder
      COMMAND docker run --rm -v "${CMAKE_SOURCE_DIR}/emerald:/emerald" emerald-em-builder make -j32 rom
      COMMAND "${CMAKE_COMMAND}" -E touch "${BASEROM_STAMP}"
      BYPRODUCTS ${EMERALD_ROM} ${EMERALD_SYM}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      COMMENT "Building the ROM (using docker)"
      DEPENDS ${BASEROM_SOURCES}
      USES_TERMINAL
      VERBATIM
    )
    add_custom_target(emerald DEPENDS "${BASEROM_STAMP}")
  else()
    file(GLOB_RECURSE BASEROM_SOURCES "${CMAKE_SOURCE_DIR}/emerald/*")
    list(REMOVE_ITEM BASEROM_SOURCES "${EMERALD_ROM}")
    list(REMOVE_ITEM BASEROM_SOURCES "${EMERALD_SYM}")
    add_custom_command(
      OUTPUT "${BASEROM_STAMP}"
      COMMAND make -j32 rom
      COMMAND "${CMAKE_COMMAND}" -E touch "${BASEROM_STAMP}"
      BYPRODUCTS ${EMERALD_ROM} ${EMERALD_SYM}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/emerald
      COMMENT "Building the ROM"
      DEPENDS ${BASEROM_SOURCES}
      USES_TERMINAL
      VERBATIM
    )
    add_custom_target(emerald DEPENDS "${BASEROM_STAMP}")
  endif()

  # Build the ROM
  set(DATA_FILES "")

  macro(build_lang lang)
    file(GLOB_RECURSE _lang_sources "${CMAKE_SOURCE_DIR}/data/text/${lang}/*.txt")
    set(_lang_output "${CMAKE_BINARY_DIR}/data/${lang}.bin")

    add_custom_command(
      OUTPUT ${_lang_output}
      COMMAND "${Python3_EXECUTABLE}" ${CMAKE_SOURCE_DIR}/scripts/make_lang.py ${lang}
      DEPENDS emerald ${EMERALD_ROM} ${EMERALD_SYM} ${_lang_sources} ${CMAKE_SOURCE_DIR}/scripts/make_lang.py
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
    COMMAND "${Python3_EXECUTABLE}" ${CMAKE_SOURCE_DIR}/scripts/make_offsets.py
    DEPENDS emerald ${EMERALD_ROM} ${EMERALD_SYM} ${CMAKE_SOURCE_DIR}/scripts/make_offsets.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building offsets"
    VERBATIM
  )
  list(APPEND DATA_FILES ${OFFSETS_FILE})

  # Delta
  set(DELTA_FILE "${CMAKE_BINARY_DIR}/data/delta.bin")
  add_custom_command(
    OUTPUT ${DELTA_FILE}
    COMMAND "${Python3_EXECUTABLE}" ${CMAKE_SOURCE_DIR}/scripts/make_delta.py "${ORIGINAL_ROM}" "${EMERALD_ROM}" "${DELTA_FILE}"
    DEPENDS emerald ${EMERALD_ROM} ${CMAKE_SOURCE_DIR}/scripts/make_delta.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building delta"
    VERBATIM
  )
  list(APPEND DATA_FILES ${DELTA_FILE})

  # Copy data
  add_custom_target(
    data ALL
    DEPENDS emerald ${DATA_FILES}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/data $<TARGET_FILE_DIR:shuffler-cli>/data
    COMMENT "Copying data files"
    VERBATIM
  )
else()
  # Copy data
  add_custom_target(
    data ALL
    DEPENDS ${EXTERNAL_DATA}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${EXTERNAL_DATA} $<TARGET_FILE_DIR:shuffler-cli>/data
    COMMENT "Copying data files"
    VERBATIM
  )
endif()

include_directories(src)
add_subdirectory(src)

if (WIN32)
  install(TARGETS shuffler-cli DESTINATION .)
  install(TARGETS shuffler-gui DESTINATION .)
  install(FILES $<TARGET_RUNTIME_DLLS:shuffler-cli> DESTINATION .)
  install(FILES $<TARGET_RUNTIME_DLLS:shuffler-gui> DESTINATION .)
  if (EXTERNAL_DATA)
    install(DIRECTORY ${EXTERNAL_DATA}/ DESTINATION ./data)
  else()
    install(DIRECTORY ${CMAKE_BINARY_DIR}/data DESTINATION .)
  endif()
  set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION .)
  include(InstallRequiredSystemLibraries)
endif()
