file(GLOB_RECURSE SOURCES "*.cpp")
add_executable(shuffler ${SOURCES})
add_dependencies(shuffler emerald data)
