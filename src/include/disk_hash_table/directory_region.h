#pragma once

#include "disk/disk.h"
#include "disk_hash_table/directory_page.h"

namespace hybridfs {

class HashTableDirectoryRegion {
public:
    HashTableDirectoryRegion(Disk* disk_adaptor, size_t directory_page_id, size_t directory_region_size) {
        disk_adaptor_ = disk_adaptor;
        directory_page_id_ = directory_page_id;
        directory_region_size_ = directory_region_size;
        directory_region_array_size_ = directory_region_size * HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    }

    auto GetGlobalDepth() -> uint32_t;
    void SetGlobalDepth(uint32_t global_depth);
    void IncrGlobalDepth();
    void DecrGlobalDepth();

    auto GetLocalDepth(uint32_t bucket_idx) -> uint32_t;
    void SetLocalDepth(uint32_t bucket_idx, uint32_t local_depth);

    auto GetBucketPageId(uint32_t bucket_idx) -> uint32_t;
    void SetBucketPageId(uint32_t bucket_idx, uint32_t bucket_page_id);

    auto GetSplitImageIndex(uint32_t bucket_idx) -> uint32_t;

    auto GetGlobalDepthMask() -> uint32_t;
    auto GetLocalDepthMask(uint32_t bucket_idx) -> uint32_t;

    auto GetLocalHighBit(uint32_t bucket_idx) -> uint32_t;

    auto GetSize() -> size_t { return directory_region_array_size_; }

private:
    Disk* disk_adaptor_;
    size_t directory_page_id_;
    size_t directory_region_size_;
    size_t directory_region_array_size_;
};

}