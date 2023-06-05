cmake_minimum_required(VERSION 3.20)

project(moba-sniffer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(config.h.in config.h)

add_subdirectory(${CMAKE_SOURCE_DIR}/modules/lib-cs2interface)
add_executable(
    moba-sniffer 

    src/handler.cpp
    src/main.cpp
    src/s88sniffer.cpp
)

install(TARGETS moba-sniffer)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

target_include_directories(moba-sniffer PUBLIC "${PROJECT_BINARY_DIR}")

target_link_libraries(moba-sniffer mobacommon)
target_link_libraries(moba-sniffer z)
target_link_libraries(moba-sniffer ncurses)
target_link_libraries(moba-sniffer ${CMAKE_SOURCE_DIR}/modules/lib-cs2interface/libmoba-cs2interface.a)

include_directories(${CMAKE_SOURCE_DIR}/modules/lib-cs2interface/src)