cmake_minimum_required(VERSION 3.0)
project(arcade)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")

include_directories(core)
include_directories(common)


add_executable(arcade
        core/main.cpp
        common/Event.hpp
        common/Color.hpp
        common/Object.hpp
        common/IDisplay.hpp
        common/IDisplay.hpp
        common/IGame.hpp)

TARGET_LINK_LIBRARIES(arcade dl)

#add_subdirectory(librairies/template)
#add_dependencies(arcade template)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "lib")
set_target_properties(template PROPERTIES PREFIX "")

add_custom_command(TARGET arcade POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:arcade>
        ${PROJECT_SOURCE_DIR}/$<TARGET_FILE_NAME:arcade>)
