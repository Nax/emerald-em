file(GLOB_RECURSE SOURCES "*.cpp")
add_executable(shuffler ${SOURCES})
add_dependencies(shuffler emerald data)
target_include_directories(shuffler PRIVATE "${CMAKE_SOURCE_DIR}")
