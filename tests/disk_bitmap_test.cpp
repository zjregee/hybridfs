#include <iostream>
#include <cstring>

#include "disk/disk.h"
#include "disk_page/page.h"
#include "disk_bitmap/disk_bitmap.h"

int main() {
    hybridfs::Disk* disk = new hybridfs::Disk("sim_disk", 0, 256, true, 10);
    hybridfs::DiskBitmap* disk_bitmap = new hybridfs::DiskBitmap(disk, 0, 10);

    for (int i = 0; i < 327680; i++) {
        if (disk_bitmap->NewPage() != i) {
            std::cout << "error exists" << std::endl;
            return 1;
        }
        disk_bitmap->SetOccupied(i, true);
    }

    if (disk_bitmap->NewPage() != -1) {
        std::cout << "error exists" << std::endl;
        return 1;
    }

    for (int i = 100; i < 300000; i++) {
        disk_bitmap->SetOccupied(i, false);
    }

    for (int i = 100; i < 300000; i++) {
        if (disk_bitmap->NewPage() != i) {
            std::cout << "error exists" << std::endl;
            return 1;
        }
        disk_bitmap->SetOccupied(i, true);
    }

    std::cout << "passed" << std::endl;

    return 0;
}