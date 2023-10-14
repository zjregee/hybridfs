#include "disk_bitmap/disk_bitmap.h"

namespace hybridfs {

auto DiskBitmap::NewPage() -> int {
    for (size_t i = 0; i < bitmap_size_; i++) {
        BitmapPage* bitmap = reinterpret_cast<BitmapPage *>(disk_->ReadPage(bitmap_offset_ + i));
        int page_id = bitmap->NewPage();
        if (page_id != -1) {
            return i * NUM_PAGES_IN_BITMAP + page_id;
        }
    }
    return -1;
}

void DiskBitmap::SetOccupied(size_t page_id, bool occupied) {
    size_t offset = page_id / NUM_PAGES_IN_BITMAP;
    size_t raw_page_id = page_id % NUM_PAGES_IN_BITMAP;
    BitmapPage* bitmap = reinterpret_cast<BitmapPage *>(disk_->ReadPage(bitmap_offset_ + offset));
    bitmap->SetOccupied(raw_page_id, occupied);
    disk_->PutBackPage(bitmap_offset_ + offset, bitmap);
}

}