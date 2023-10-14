#pragma once

#include "common/consts.h"
#include "disk/disk.h"
#include "disk_bitmap/disk_bitmap.h"
#include "disk_hash_table/directory_region.h"

namespace hybridfs {

void HashTableFormatting() {
    Disk* disk = new Disk(METADATA_DISK, HASH_TABLE_REGION_OFFSET, HASH_TABLE_REGION_SIZE, true, 10);
    DiskBitmap* bitmap = new DiskBitmap(disk, HASH_TABLE_BITMAP_OFFSET, HASH_TABLE_BITMAP_SIZE);
    HashTableDirectoryRegion* directory_region = new HashTableDirectoryRegion(disk, HASH_TABLE_DIRECTORY_REGION_OFFSET, HASH_TABLE_DIRECTORY_REGION_SIZE, HASH_TABLE_DIRECTORY_REGION_ARRAY_SIZE);
    directory_region->SetGlobalDepth(1);
    for (size_t i = 0; i < HASH_TABLE_BITMAP_SIZE + HASH_TABLE_DIRECTORY_REGION_SIZE + 2; i++) {
        bitmap->SetOccupied(i, true);
    }
    size_t a_bucket_page_id = HASH_TABLE_BITMAP_SIZE + HASH_TABLE_DIRECTORY_REGION_SIZE;
    size_t b_bucket_page_id = a_bucket_page_id + 1;
    uint32_t diff = 2;
    for (uint32_t i = 0; i <= directory_region->GetSize(); i += diff) {
        directory_region->SetBucketPageId(i, a_bucket_page_id);
        directory_region->SetLocalDepth(i, 1);
    }
    for (uint32_t i = 1; i <= directory_region->GetSize(); i += diff) {
        directory_region->SetBucketPageId(i, b_bucket_page_id);
        directory_region->SetLocalDepth(i, 1);
    }
    disk->Flush();
    delete disk;
}

}