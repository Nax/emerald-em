cmake_minimum_required(VERSION 3.10)

project(Emerald-EM)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build the ROM
set(EMERALD_ROM "${CMAKE_SOURCE_DIR}/emerald/pokeemerald.gba")
add_custom_target(
    emerald ALL
    COMMAND make -j32 rom
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/emerald
    COMMENT "Building the ROM"
    USES_TERMINAL
    VERBATIM
)
