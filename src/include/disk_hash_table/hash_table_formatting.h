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
    directory_region->SetGlobalDepth(0);
    for (size_t i = 0; i < HASH_TABLE_BITMAP_SIZE + HASH_TABLE_DIRECTORY_REGION_SIZE + 1; i++) {
        bitmap->SetOccupied(i, true);
    }
    size_t bucket_page_id = HASH_TABLE_BITMAP_SIZE + HASH_TABLE_DIRECTORY_REGION_SIZE;
    for (size_t i = 0; i < directory_region->GetSize(); i++) {
        directory_region->SetLocalDepth(i, 0);
        directory_region->SetBucketPageId(i, bucket_page_id);
    }
    disk->Flush();
    delete disk;
}

}