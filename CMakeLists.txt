cmake_minimum_required(VERSION 3.16.3)

project(hybridfs CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Werror")

add_compile_options(-DCMAKE_BUILD_TYPE=Release)

set(HYBRIDFS_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)

add_subdirectory(src)
add_subdirectory(third_party)