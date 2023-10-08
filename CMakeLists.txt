cmake_minimum_required(VERSION 3.16.3)

project(hybridfs CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Werror")

add_compile_options(-DCMAKE_BUILD_TYPE=Release)

LINK_LIBRARIES(pthread)

set(HYBRIDFS_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)
set(HYBRIDFS_THIRD_PARTY_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/third_party
    ${PROJECT_SOURCE_DIR}/third_party/spdlog/include
)

include_directories(${HYBRIDFS_SRC_INCLUDE_DIR} ${HYBRIDFS_THIRD_PARTY_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(third_party)