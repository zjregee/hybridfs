#pragma once

#include <cstdint>

#include "common/consts.h"
#include "disk_page/page.h"

namespace hybridfs {

class HashTableDirectoryPage: public Page {
public:
    auto GetGlobalDepth() -> uint32_t;
    void SetGlobalDepth(uint32_t global_depth);
    void IncrGlobalDepth();
    void DecrGlobalDepth();
    auto GetLocalDepth(size_t bucket_idx) -> uint32_t;
    void SetLocalDepth(size_t bucket_idx, uint32_t local_depth);
    auto GetBucketPageId(size_t bucket_idx) -> uint32_t;
    void SetBucketPageId(size_t bucket_idx, uint32_t bucket_page_id);
};

}