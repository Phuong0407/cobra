cmake_minimum_required(VERSION 3.16)

project(cobra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(core STATIC ${SRC_FILES})

target_include_directories(core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE core)
