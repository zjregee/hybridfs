#pragma once

#include <cstdint>

#include "common/consts.h"
#include "disk_page/page.h"

namespace hybridfs {

class HashTableDirectoryPage: public Page {
public:
    uint32_t GetGlobalDepth();
    void SetGlobalDepth(uint32_t global_depth);
    void IncrGlobalDepth();
    void DecrGlobalDepth();
    uint32_t GetLocalDepth(size_t bucket_idx);
    void SetLocalDepth(size_t bucket_idx, uint32_t local_depth);
    uint32_t GetBucketPageId(size_t bucket_idx);
    void SetBucketPageId(size_t bucket_idx, uint32_t bucket_page_id);
};

}