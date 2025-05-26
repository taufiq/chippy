cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Chippy VERSION 1.0)

# Debug flags configuration
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# SDL3 configuration
set(SDL3_VENDORED ON)
set(SDLTTF_VENDORED ON)


add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

add_executable(chippy main.cpp Window.cpp Box.cpp Text.cpp TextManager.cpp Canvas.cpp)

set(PROGRAM_PERMISSIONS_DEFAULT
    OWNER_WRITE OWNER_READ OWNER_EXECUTE)

# Ensure debug information is included
set_target_properties(chippy PROPERTIES
    COMPILE_FLAGS "-g -O0"
    DEBUG_POSTFIX "d"
)

file(COPY roms DESTINATION ${PROJECT_BINARY_DIR})

target_link_libraries(chippy PRIVATE SDL3_ttf::SDL3_ttf SDL3::SDL3)

# Add SDL3 include directories
target_include_directories(chippy PUBLIC 
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/vendored/SDL/include"
    "${PROJECT_SOURCE_DIR}/vendored/SDL_ttf/include"
)
