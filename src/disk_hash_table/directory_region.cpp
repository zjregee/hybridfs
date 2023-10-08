#include "disk_hash_table/directory_region.h"

namespace hybridfs {

auto HashTableDirectoryRegion::GetGlobalDepth() -> uint32_t {
    auto dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_adaptor_->ReadPage(directory_page_id_));
    return dir_page->GetGlobalDepth();
}

void HashTableDirectoryRegion::SetGlobalDepth(uint32_t global_depth) {
    auto dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_adaptor_->ReadPage(directory_page_id_));
    dir_page->SetGlobalDepth(global_depth);
    disk_adaptor_->WritePage(directory_page_id_, dir_page);
}

void HashTableDirectoryRegion::IncrGlobalDepth() {
    auto dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_adaptor_->ReadPage(directory_page_id_));
    dir_page->IncrGlobalDepth();
    disk_adaptor_->WritePage(directory_page_id_, dir_page);
}

void HashTableDirectoryRegion::DecrGlobalDepth() {
    auto dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_adaptor_->ReadPage(directory_page_id_));
    dir_page->DecrGlobalDepth();
    disk_adaptor_->WritePage(directory_page_id_, dir_page);
}

auto HashTableDirectoryRegion::GetLocalDepth(uint32_t bucket_idx) -> uint32_t {
    uint32_t pos = bucket_idx / HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    uint32_t off = bucket_idx % HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    auto dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_adaptor_->ReadPage(directory_page_id_ + pos));
    return dir_page->GetLocalDepth(off);
}

void HashTableDirectoryRegion::SetLocalDepth(uint32_t bucket_idx, uint32_t local_depth) {
    uint32_t pos = bucket_idx / HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    uint32_t off = bucket_idx % HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    auto dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_adaptor_->ReadPage(directory_page_id_ + pos));
    dir_page->SetLocalDepth(off, local_depth);
    disk_adaptor_->WritePage(directory_page_id_ + pos, dir_page);
}

auto HashTableDirectoryRegion::GetBucketPageId(uint32_t bucket_idx) -> uint32_t {
    uint32_t pos = bucket_idx / HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    uint32_t off = bucket_idx % HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    auto dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_adaptor_->ReadPage(directory_page_id_ + pos));
    return dir_page->GetBucketPageId(off);
}

void HashTableDirectoryRegion::SetBucketPageId(uint32_t bucket_idx, uint32_t bucket_page_id) {
    uint32_t pos = bucket_idx / HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    uint32_t off = bucket_idx % HASH_TABLE_DIRECTORY_ARRAY_SIZE;
    auto dir_page = reinterpret_cast<HashTableDirectoryPage *>(disk_adaptor_->ReadPage(directory_page_id_ + pos));
    dir_page->SetBucketPageId(off, bucket_page_id);
    disk_adaptor_->WritePage(directory_page_id_ + pos, dir_page);
}

auto HashTableDirectoryRegion::GetSplitImageIndex(uint32_t bucket_idx) -> uint32_t {
    return bucket_idx | (1 << GetLocalDepth(bucket_idx));
}

auto HashTableDirectoryRegion::GetGlobalDepthMask() -> uint32_t {
    return (1 << GetGlobalDepth()) - 1;
}

auto HashTableDirectoryRegion::GetLocalDepthMask(uint32_t bucket_idx) -> uint32_t {
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