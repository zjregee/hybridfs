#pragma once

#include "disk_page/page.h"

namespace hybridfs {

static const int NUM_PAGES_IN_BITMAP = 32768;

class BitmapPage: public Page {
public:
    auto NewPage() -> int;
    void SetOccupied(size_t page_id, bool occupied);

private:
    auto IsOccupied(size_t page_id) -> bool;
};
   
}