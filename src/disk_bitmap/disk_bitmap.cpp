#include "disk_bitmap/disk_bitmap.h"

namespace hybridfs {

auto DiskBitmap::NewPage() -> int {
    for (int i = 0; i < bitmap_size_; i++) {
        BitmapPage* bitmap = reinterpret_cast<BitmapPage *>(disk_->ReadPage(bitmap_offset_ + i));
        int page_id = bitmap->NewPage();
        if (page_id != -1) {
            return i * NUM_PAGES_IN_BITMAP + page_id;
        }
    }
    return -1;
}

void DiskBitmap::SetOccupied(uint32_t page_id, bool occupied) {
    int offset = page_id / NUM_PAGES_IN_BITMAP;
    int raw_page_id = page_id % NUM_PAGES_IN_BITMAP;
    BitmapPage* bitmap = reinterpret_cast<BitmapPage *>(disk_->ReadPage(bitmap_offset_ + offset));
    bitmap->SetOccupied(raw_page_id, occupied);
    disk_->WritePage(bitmap_offset_ + offset, bitmap);
}

}