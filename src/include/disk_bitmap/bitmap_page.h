#pragma once

#include "common/consts.h"
#include "disk_page/page.h"

namespace hybridfs {

class BitmapPage: public Page {
public:
    auto NewPage() -> int;
    void SetOccupied(size_t page_id, bool occupied);

private:
    auto IsOccupied(size_t page_id) -> bool;
};
   
}