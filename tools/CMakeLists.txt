add_executable(mkfs mkfs.cpp)

target_link_libraries(mkfs hybridfs)

set_target_properties(mkfs PROPERTIES OUTPUT_NAME mkfs.hybridfs)
