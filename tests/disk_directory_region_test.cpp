#include <iostream>
#include <string>

#include "disk/disk.h"
#include "disk_hash_table/directory_region.h"

int main() {
    hybridfs::Disk* disk = new hybridfs::Disk("sim_disk", 0, 256, false);
    hybridfs::HashTableDirectoryRegion* directory_region = new hybridfs::HashTableDirectoryRegion(disk, 0, 10, 0);

    if (directory_region->GetSize() != 0) {
        std::cout << "error exists" << std::endl;
        return 1;
    }

    if (directory_region->GetGlobalDepth() != 0) {
        std::cout << "error exists" << std::endl;
        return 1;
    }

    for (size_t i = 0; i < 10; i++) {
        directory_region->IncrGlobalDepth();
    }

    if (directory_region->GetGlobalDepth() != 10) {
        std::cout << "error exists" << std::endl;
        return 1;
    }

    for (size_t i = 0; i < 5; i++) {
        directory_region->DecrGlobalDepth();
    }

    if (directory_region->GetGlobalDepth() != 5) {
        std::cout << "error exists" << std::endl;
        return 1;
    }

    for (size_t i = 0; i < 5000; i++) {
        directory_region->SetLocalDepth(i, 2 * i);
        directory_region->SetBucketPageId(i, 2 * i + 1);
    }

    for (size_t i = 0; i < 5000; i++) {
        if (directory_region->GetLocalDepth(i) != 2 * i) {
            std::cout << "error exists" << std::endl;
        }
        if (directory_region->GetBucketPageId(i) != 2 * i + 1) {
            std::cout << "error exists" << std::endl;
        }
    }

    return 0;
}