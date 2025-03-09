find_package(Qt6 COMPONENTS Widgets Concurrent REQUIRED)

set(CMAKE_AUTOMOC ON)
file(GLOB_RECURSE SOURCES "*.cpp")
add_executable(shuffler-gui WIN32 ${SOURCES})
target_include_directories(shuffler-gui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(shuffler-gui libemerald Qt6::Widgets)
set_target_properties(shuffler-gui PROPERTIES OUTPUT_NAME Shuffler-GUI)

# Copy Qt DLLs
# we use windeployqt to copy our dll dependencies into the same folder
# that the executable is built into
if (MSVC)
  get_target_property(QT6_WIDGETS_LIB Qt6::Widgets LOCATION)
  get_filename_component(QT6_BIN_DIR ${QT6_WIDGETS_LIB} PATH)
  set(QT6_WINDEPLOYQT_EXECUTABLE "${QT6_BIN_DIR}/windeployqt.exe")

  add_custom_command(TARGET shuffler-gui POST_BUILD COMMAND ${QT6_WINDEPLOYQT_EXECUTABLE} --no-compiler-runtime --no-opengl-sw --no-translations --no-network --no-svg --no-system-d3d-compiler --release $<TARGET_FILE_DIR:shuffler-gui>)

  # Also run it on install
  install(FILES $<TARGET_FILE_DIR:shuffler-gui>/ DESTINATION .)
endif()
