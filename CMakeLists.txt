cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(moba-sniffer VERSION 0.1.0)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0)

configure_file(config.h.in config.h)

link_directories("${PROJECT_SOURCE_DIR}/modules/lib-lib-cs2interface")

set(URLIB_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/modules/lib-cs2interface")

add_subdirectory(${CMAKE_SOURCE_DIR}/modules/lib-cs2interface)
add_executable(
    moba-sniffer

    src/main.cpp
    src/frmmain.cpp
    src/ctrllokcontrol.cpp
    src/feedbackchecker.cpp
    src/ctrlincomingcommands.cpp
    src/ctrlcontrol.cpp
    src/ctrlmonitor.cpp
    src/ctrlconfig.cpp
)

install(TARGETS moba-sniffer)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

target_include_directories(moba-sniffer PUBLIC "${PROJECT_BINARY_DIR}")

target_link_libraries(moba-sniffer mobacommon)
target_link_libraries(moba-sniffer z)
target_link_libraries(moba-sniffer ncurses)
target_link_libraries(moba-sniffer ${CMAKE_SOURCE_DIR}/modules/lib-cs2interface/libmoba-lib-cs2interface.a)
target_link_libraries(moba-sniffer ${GTKMM_LIBRARIES})

link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/modules/lib-cs2interface/src)

include(GNUInstallDirs)

# Installation der .desktop Datei
install(FILES moba-sniffer.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

# Installation des Icons
install(FILES pixmaps/scalable/apps/moba-sniffer.svg
        DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

# Optional: Icon-Cache aktualisieren nach der Installation
install(CODE "execute_process(COMMAND gtk-update-icon-cache -f -t ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATADIR}/icons/hicolor)")
