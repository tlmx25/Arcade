cmake_minimum_required(VERSION 3.0)
project(arcade)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")

include_directories(core)
include_directories(common)


add_executable(arcade
        core/main.cpp
        core/Core.cpp
        core/Core.hpp
        core/CLibEncapsulation.cpp)

TARGET_LINK_LIBRARIES(arcade dl)

add_subdirectory(librairies/sfml)
add_subdirectory(librairies/ncurses)
add_subdirectory(librairies/sdl2)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "lib")

add_custom_command(TARGET arcade POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:arcade>
        ${PROJECT_SOURCE_DIR}/$<TARGET_FILE_NAME:arcade>)
