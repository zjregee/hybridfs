add_library(
    hybridfs_disk_hash_table
    OBJECT
    bucket_page.cpp
    directory_page.cpp
    directory_region.cpp
    disk_extendible_hash_table.cpp
)

set(ALL_OBJECT_FILES ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:hybridfs_disk_hash_table> PARENT_SCOPE)