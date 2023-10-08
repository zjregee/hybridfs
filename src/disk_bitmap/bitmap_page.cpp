#include "disk_bitmap/bitmap_page.h"

namespace hybridfs {

auto BitmapPage::NewPage() -> int {
    for (int i = 0; i < NUM_PAGES_IN_BITMAP; i++) {
        if (!IsOccupied(i)) {
            return i;
        }
    }
    return -1;
}

void BitmapPage::SetOccupied(size_t page_id, bool occupied) {
    size_t pos = page_id / 8;
    size_t off = page_id % 8;
    char mask = 1 << off;
    if (occupied) {
        *(GetData() + pos) |= mask;
    } else {
        *(GetData() + pos) &= ~mask;
    }
}

auto BitmapPage::IsOccupied(size_t page_id) -> bool {
    size_t pos = page_id / 8;
    size_t off = page_id % 8;
    char mask = 1 << off;
    return *(GetData() + pos) & mask;
}

}