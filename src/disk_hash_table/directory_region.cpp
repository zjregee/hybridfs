#include "disk_hash_table/directory_region.h"

namespace hybridfs {

uint32_t HashTableDirectoryRegion::GetGlobalDepth() {
    HashTableDirectoryPage* dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_->ReadPage(directory_region_offset_));
    uint32_t global_depth = dir_page->GetGlobalDepth();
    disk_->PutBackPage(directory_region_offset_, dir_page);
    return global_depth;
}

void HashTableDirectoryRegion::SetGlobalDepth(uint32_t global_depth) {
    HashTableDirectoryPage* dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_->ReadPage(directory_region_offset_));
    dir_page->SetGlobalDepth(global_depth);
    disk_->PutBackPage(directory_region_offset_, dir_page);
}

void HashTableDirectoryRegion::IncrGlobalDepth() {
    HashTableDirectoryPage* dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_->ReadPage(directory_region_offset_));
    dir_page->IncrGlobalDepth();
    disk_->PutBackPage(directory_region_offset_, dir_page);
}

void HashTableDirectoryRegion::DecrGlobalDepth() {
    HashTableDirectoryPage* dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_->ReadPage(directory_region_offset_));
    dir_page->DecrGlobalDepth();
    disk_->PutBackPage(directory_region_offset_, dir_page);
}

uint32_t HashTableDirectoryRegion::GetLocalDepth(size_t bucket_idx) {
    size_t pos = bucket_idx / HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    size_t off = bucket_idx % HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    HashTableDirectoryPage* dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_->ReadPage(directory_region_offset_ + pos));
    uint32_t local_depth = dir_page->GetLocalDepth(off);
    disk_->PutBackPage(directory_region_offset_ + pos, dir_page);
    return local_depth;
}

void HashTableDirectoryRegion::SetLocalDepth(size_t bucket_idx, uint32_t local_depth) {
    size_t pos = bucket_idx / HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    size_t off = bucket_idx % HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    HashTableDirectoryPage* dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_->ReadPage(directory_region_offset_ + pos));
    dir_page->SetLocalDepth(off, local_depth);
    disk_->PutBackPage(directory_region_offset_ + pos, dir_page);
}

uint32_t HashTableDirectoryRegion::GetBucketPageId(size_t bucket_idx) {
    size_t pos = bucket_idx / HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    size_t off = bucket_idx % HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    HashTableDirectoryPage* dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_->ReadPage(directory_region_offset_ + pos));
    uint32_t bucke_page_id = dir_page->GetBucketPageId(off);
    disk_->PutBackPage(directory_region_offset_ + pos, dir_page);
    return bucke_page_id;
}

void HashTableDirectoryRegion::SetBucketPageId(size_t bucket_idx, uint32_t bucket_page_id) {
    size_t pos = bucket_idx / HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    size_t off = bucket_idx % HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    HashTableDirectoryPage* dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_->ReadPage(directory_region_offset_ + pos));
    dir_page->SetBucketPageId(off, bucket_page_id);
    disk_->PutBackPage(directory_region_offset_ + pos, dir_page);
}

uint32_t HashTableDirectoryRegion::GetSplitImageIndex(uint32_t bucket_idx) {
    return bucket_idx | (1 << GetLocalDepth(bucket_idx));
}

uint32_t HashTableDirectoryRegion::GetGlobalDepthMask() {
    return (1 << GetGlobalDepth()) - 1;
}

uint32_t HashTableDirectoryRegion::GetLocalDepthMask(uint32_t bucket_idx) {
    return (1 << GetLocalDepth(bucket_idx)) - 1;
}

auto HashTableDirectoryRegion::GetLocalHighBit(uint32_t bucket_idx) -> uint32_t {
    uint32_t local_depth = GetLocalDepth(bucket_idx);
    if (local_depth == 0) {
        return 0;
    }
    return 1 << (local_depth - 1);
}

}