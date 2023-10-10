#include "disk_hash_table/disk_extendible_hash_table.h"

namespace hybridfs {

auto DiskExtendibleHashTable::FetchBucketPage(uint32_t bucket_page_id) -> HashTableBucketPage * {
    return reinterpret_cast<HashTableBucketPage *>(disk_->ReadPage(bucket_page_id));
}

auto DiskExtendibleHashTable::WriteBucketPage(HashTableBucketPage* page, uint32_t bucket_page_id) -> bool {
    disk_->WritePage(bucket_page_id, page);
    return true;
}

auto DiskExtendibleHashTable::NewPage() -> uint32_t {
    int new_page_id = bitmap_->NewPage();
    if (new_page_id == - 1) {

    }
    bitmap_->SetOccupied(new_page_id, true);
    return new_page_id;
}

auto DiskExtendibleHashTable::Insert(std::string &key, std::string &value) -> bool {
    fill_string_to_length(key, HASH_TABLE_BUCKET_KEY_SIZE);
    fill_string_to_length(value, HASH_TABLE_BUCKET_VALUE_SIZE);
    uint32_t hash = Hash(key);
    uint32_t raw_bucket_idx = hash & directory_region_->GetGlobalDepthMask();
    uint32_t bucket_idx = raw_bucket_idx & directory_region_->GetLocalDepthMask(raw_bucket_idx);
    uint32_t bucket_page_id = directory_region_->GetBucketPageId(bucket_idx);
    auto bucket_page = FetchBucketPage(bucket_page_id);
    if (!bucket_page->IsFull()) {
        bucket_page->Insert(key, value);
        WriteBucketPage(bucket_page, bucket_page_id);
        return true;
    }
    uint32_t local_depth = directory_region_->GetLocalDepth(bucket_idx);
    if (local_depth == directory_region_->GetGlobalDepth()) {
        directory_region_->IncrGlobalDepth();
    }
    local_depth += 1;
    uint32_t split_bucket_index = directory_region_->GetSplitImageIndex(bucket_idx);
    uint32_t split_bucket_page_id = NewPage();
    auto split_bucket_page = FetchBucketPage(split_bucket_page_id);
    for (size_t i = 0; i < HASH_TABLE_BUCKET_ARRAY_SIZE; i++) {
        std::string new_key = bucket_page->KeyAt(i);
        uint32_t new_hash = Hash(new_key.substr(0, key.size()));
        uint32_t new_bucket_idx = new_hash & ((1 << local_depth) - 1);
        if (new_bucket_idx == split_bucket_index) {
            std::string new_value = bucket_page->ValueAt(i);
            split_bucket_page->Insert(new_key, new_value);
            bucket_page->RemoveAt(i);
        }
    }
    uint32_t diff = 1 << local_depth;
    for (uint32_t i = bucket_idx; i < directory_region_->GetSize(); i += diff) {
        directory_region_->SetBucketPageId(i, bucket_page_id);
        directory_region_->SetLocalDepth(i, local_depth);
    }
    for (uint32_t i = split_bucket_index; i < directory_region_->GetSize(); i += diff) {
        directory_region_->SetBucketPageId(i, split_bucket_page_id);
        directory_region_->SetLocalDepth(i, local_depth);
    }
    WriteBucketPage(bucket_page, bucket_page_id);
    WriteBucketPage(split_bucket_page, split_bucket_page_id);
    Insert(key, value);
    return true;
}

auto DiskExtendibleHashTable::GetValue(std::string &key, std::string &value) -> bool {
    fill_string_to_length(key, HASH_TABLE_BUCKET_KEY_SIZE);
    uint32_t hash = Hash(key);
    uint32_t raw_bucket_idx = hash & directory_region_->GetGlobalDepthMask();
    uint32_t bucket_idx = raw_bucket_idx & directory_region_->GetLocalDepthMask(raw_bucket_idx);
    uint32_t bucket_page_id = directory_region_->GetBucketPageId(bucket_idx);
    auto bucket_page = FetchBucketPage(bucket_page_id);
    return bucket_page->GetValue(key, value);
}

auto DiskExtendibleHashTable::Remove(std::string &key) -> bool {
    fill_string_to_length(key, HASH_TABLE_BUCKET_KEY_SIZE);
    uint32_t hash = Hash(key);
    uint32_t raw_bucket_idx = hash & directory_region_->GetGlobalDepthMask();
    uint32_t bucket_idx = raw_bucket_idx & directory_region_->GetLocalDepthMask(raw_bucket_idx);
    uint32_t bucket_page_id = directory_region_->GetBucketPageId(bucket_idx);
    auto bucket_page = FetchBucketPage(bucket_page_id);
    bucket_page->Remove(key);
    WriteBucketPage(bucket_page, bucket_page_id);
    return true;
}

}