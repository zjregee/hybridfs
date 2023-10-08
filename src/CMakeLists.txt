add_subdirectory(disk_bitmap)
add_subdirectory(disk_hash_table)

add_library(hybridfs STATIC ${ALL_OBJECT_FILES})

set(HYBRIDFS_LIBS
    hybridfs_disk_bitmap
    hybridfs_disk_hash_table
)

set(HYBRIDFS_THIRDPARTY_LIBS
    spdlog
    murmur3
)

target_link_libraries(hybridfs ${HYBRIDFS_LIBS} ${HYBRIDFS_THIRDPARTY_LIBS})

target_include_directories(
    hybridfs PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)