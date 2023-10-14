# ./build/tools/mkfs.hybridfs sim_disk_1 256
# ./build/tools/mkfs.hybridfs sim_disk_2 256
# ./build/tests/disk_test

# ./build/tools/mkfs.hybridfs sim_disk 256
# ./build/tests/disk_bitmap_test

# ./build/tools/mkfs.hybridfs sim_disk 256
# ./build/tests/disk_bucket_page_test

# ./build/tools/mkfs.hybridfs sim_disk 256
# ./build/tests/disk_directory_region_test

./build/tools/mkfs.hybridfs sim_disk 524288
./build/tests/disk_hash_table_test