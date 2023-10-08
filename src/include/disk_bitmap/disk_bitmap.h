#pragma once

#include "disk/disk.h"
#include "disk_bitmap/bitmap_page.h"

namespace hybridfs {

class DiskBitmap {
public:
    DiskBitmap(Disk* disk_adaptor, size_t bitmap_offset, size_t bitmap_size) {
        disk_ = disk_adaptor;
        bitmap_offset_ = bitmap_offset;
        bitmap_size_ = bitmap_size;
    }

    auto NewPage() -> int;
    void SetOccupied(uint32_t page_id, bool occupied);

private:
    Disk* disk_;
    size_t bitmap_offset_;
    size_t bitmap_size_;
};

}