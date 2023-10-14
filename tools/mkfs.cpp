#include <iostream>
#include <string>

#include "disk/disk_formatting.h"
#include "disk_hash_table/hash_table_formatting.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <disk_name> <disk_size>" << std::endl;
        return 1;
    }
    std::string disk_name;
    size_t disk_size;
    try {
        disk_name = argv[1];
        disk_size = std::stoi(argv[2]);
    } catch (const std::exception& e) {
        std::cout << "Error: Invalid argument" << std::endl;
        return 1;
    }
    hybridfs::DiskFormatting(disk_name, disk_size);
    hybridfs::HashTableFormatting();
    return 0;
}