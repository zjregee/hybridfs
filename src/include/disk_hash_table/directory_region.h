#pragma once

#include "disk/disk.h"
#include "disk_hash_table/directory_page.h"

namespace hybridfs {

class HashTableDirectoryRegion {
public:
    HashTableDirectoryRegion(Disk* disk, size_t directory_region_offset, size_t directory_region_size, size_t directory_region_array_size) {
        disk_ = disk;
        directory_region_offset_ = directory_region_offset;
        directory_region_size_ = directory_region_size;
        directory_region_array_size_ = directory_region_array_size;
    }

    auto GetGlobalDepth() -> uint32_t;
    void SetGlobalDepth(uint32_t global_depth);
    void IncrGlobalDepth();
    void DecrGlobalDepth();
    uint32_t GetLocalDepth(size_t bucket_idx);
    void SetLocalDepth(size_t bucket_idx, uint32_t local_depth);
    uint32_t GetBucketPageId(size_t bucket_idx);
    void SetBucketPageId(size_t bucket_idx, uint32_t bucket_page_id);
    uint32_t GetSplitImageIndex(uint32_t bucket_idx);
    uint32_t GetGlobalDepthMask();
    uint32_t GetLocalDepthMask(uint32_t bucket_idx);
    uint32_t GetLocalHighBit(uint32_t bucket_idx);
    
    size_t GetSize() { return directory_region_array_size_; }

private:
    Disk* disk_;
    size_t directory_region_offset_;
    size_t directory_region_size_;
    size_t directory_region_array_size_;
};

}