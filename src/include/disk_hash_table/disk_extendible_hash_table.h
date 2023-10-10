#pragma once

#include <murmur3/MurmurHash3.h>

#include "common/consts.h"
#include "disk/disk.h"
#include "disk_bitmap/disk_bitmap.h"
#include "disk_hash_table/bucket_page.h"
#include "disk_hash_table/directory_page.h"
#include "disk_hash_table/directory_region.h"

namespace hybridfs {

class DiskExtendibleHashTable {
public:
    DiskExtendibleHashTable() {
        disk_ = new Disk(HASH_TABLE_REGION_OFFSET, HASH_TABLE_REGION_SIZE, ENABLED_DISK_BUFFER);
        bitmap_ = new DiskBitmap(disk_, HASH_TABLE_BITMAP_OFFSET, HASH_TABLE_BITMAP_SIZE);
        directory_region_ = new HashTableDirectoryRegion(disk_, HASH_TABLE_DIRECTORY_OFFSET, HASH_TABLE_DIRECTORY_SIZE);
    }

    ~DiskExtendibleHashTable() {
        delete disk_;
        delete bitmap_;
        delete directory_region_;
    }

    auto Insert(std::string &key, std::string &value) -> bool;
    auto GetValue(std::string &key, std::string &value) -> bool;
    auto Remove(std::string &key) -> bool;

private:
    Disk* disk_;
    DiskBitmap* bitmap_;
    HashTableDirectoryRegion* directory_region_;

    auto FetchBucketPage(uint32_t bucket_page_id) -> HashTableBucketPage *;
    auto WriteBucketPage(HashTableBucketPage * page, uint32_t bucket_page_id) -> bool;
    auto NewPage() -> uint32_t;

    uint32_t Hash(const std::string &key) {
        return murmur3::MurmurHash3_x64_128(reinterpret_cast<const void *>(key.data()), HASH_TABLE_BUCKET_KEY_SIZE, 0);
    }

    void fill_string_to_length(std::string &str, size_t length) {
        if (str.length() < length) {
            str.insert(0, std::string(length - str.length(), '0'));
        }
    }
};

}