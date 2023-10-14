#pragma once

#include <murmur3/MurmurHash3.h>
#include <spdlog/spdlog.h>

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
        disk_ = new Disk(METADATA_DISK, HASH_TABLE_REGION_OFFSET, HASH_TABLE_REGION_SIZE, ENABLED_DISK_BUFFER);
        bitmap_ = new DiskBitmap(disk_, HASH_TABLE_BITMAP_OFFSET, HASH_TABLE_BITMAP_SIZE);
        directory_region_ = new HashTableDirectoryRegion(disk_, HASH_TABLE_DIRECTORY_REGION_OFFSET, HASH_TABLE_DIRECTORY_REGION_SIZE, HASH_TABLE_DIRECTORY_REGION_ARRAY_SIZE);
    }

    ~DiskExtendibleHashTable() {
        delete disk_;
        delete bitmap_;
        delete directory_region_;
    }

    bool Insert(std::string &key, std::string &value);
    bool GetValue(std::string &key, std::string &value);
    bool Remove(std::string &key);

private:
    Disk* disk_;
    DiskBitmap* bitmap_;
    HashTableDirectoryRegion* directory_region_;
    
    size_t NewPage();

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