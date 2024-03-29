cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(moba-sniffer VERSION 0.1.0)

configure_file(config.h.in config.h)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/modules/lib-cs2interface/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

link_directories("${PROJECT_SOURCE_DIR}/modules/lib-lib-cs2interface")

set(URLIB_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/modules/lib-cs2interface")

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
target_link_libraries(moba-sniffer ${CMAKE_SOURCE_DIR}/modules/lib-cs2interface/libmoba-lib-cs2interface.a)


include_directories(${CMAKE_SOURCE_DIR}/modules/lib-cs2interface/src)
