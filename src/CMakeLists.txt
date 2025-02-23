add_subdirectory(cli)
add_subdirectory(libemerald)

if (BUILD_GUI)
  add_subdirectory(gui)
endif()
