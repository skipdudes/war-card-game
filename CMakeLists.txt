# Project info
cmake_minimum_required(VERSION 3.21)
project("war")
set(CMAKE_C_STANDARD 17)

# Bundle Microsoft Visual C++ redistributables
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Project files and data
file(GLOB_RECURSE PROJECT_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_executable(${PROJECT_NAME} ${PROJECT_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
