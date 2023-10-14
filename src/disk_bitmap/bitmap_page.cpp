#include "disk_bitmap/bitmap_page.h"

namespace hybridfs {

auto BitmapPage::NewPage() -> int {
    for (size_t i = 0; i < PAGE_SIZE; i++) {
        for (size_t j = 0; j < 8; j++) {
            if (!(*(GetData() + i) & (1 << j))) {
                return i * 8 + j;
            }
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
    MarkDirty();
}

}