add_library(
    hybridfs_disk_bitmap
    OBJECT
    bitmap_page.cpp
    disk_bitmap.cpp
)

set(ALL_OBJECT_FILES ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:hybridfs_disk_bitmap> PARENT_SCOPE)