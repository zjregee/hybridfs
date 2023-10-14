#include "disk_hash_table/disk_extendible_hash_table.h"

namespace hybridfs {

size_t DiskExtendibleHashTable::NewPage() {
    int new_page_id = bitmap_->NewPage();
    if (new_page_id == - 1) {
        spdlog::error("disk_extendible_hash_table region no more free page");
        exit(1);
    }
    bitmap_->SetOccupied(new_page_id, true);
    return new_page_id;
}

bool DiskExtendibleHashTable::Insert(std::string &key, std::string &value) {
    fill_string_to_length(key, HASH_TABLE_BUCKET_KEY_SIZE);
    uint32_t hash = Hash(key);
    uint32_t raw_bucket_idx = hash & directory_region_->GetGlobalDepthMask();
    uint32_t bucket_idx = raw_bucket_idx & directory_region_->GetLocalDepthMask(raw_bucket_idx);
    size_t bucket_page_id = directory_region_->GetBucketPageId(bucket_idx);
    HashTableBucketPage* bucket_page = reinterpret_cast<HashTableBucketPage *>(disk_->ReadPage(bucket_page_id));
    if (!bucket_page->IsFull()) {
        bucket_page->Insert(key, value);
        disk_->PutBackPage(bucket_page_id, bucket_page);
        return true;
    }
    uint32_t local_depth = directory_region_->GetLocalDepth(bucket_idx);
    if (local_depth == directory_region_->GetGlobalDepth()) {
        directory_region_->IncrGlobalDepth();
    }
    local_depth += 1;
    uint32_t split_bucket_idx = directory_region_->GetSplitImageIndex(bucket_idx);
    size_t split_bucket_page_id = NewPage();
    HashTableBucketPage* split_bucket_page = reinterpret_cast<HashTableBucketPage *>(disk_->ReadPage(split_bucket_page_id));
    for (size_t i = 0; i < HASH_TABLE_BUCKET_ARRAY_SIZE; i++) {
        std::string new_key = bucket_page->KeyAt(i);
        uint32_t new_hash = Hash(new_key);
        uint32_t new_bucket_idx = new_hash & ((1 << local_depth) - 1);
        if (new_bucket_idx == split_bucket_idx) {
            std::string new_value = bucket_page->ValueAt(i);
            bucket_page->RemoveAt(i);
            split_bucket_page->Insert(new_key, new_value);
        }
    }
    bucket_idx = hash & ((1 << local_depth) - 1);
    if (bucket_idx == bucket_page_id) {
        bucket_page->Insert(key, value);
    } else {
        split_bucket_page->Insert(key, value);
    }
    uint32_t diff = 1 << local_depth;
    for (uint32_t i = bucket_idx; i <= directory_region_->GetSize(); i += diff) {
        directory_region_->SetBucketPageId(i, bucket_page_id);
        directory_region_->SetLocalDepth(i, local_depth);
    }
    for (uint32_t i = split_bucket_idx; i <= directory_region_->GetSize(); i += diff) {
        directory_region_->SetBucketPageId(i, split_bucket_page_id);
        directory_region_->SetLocalDepth(i, local_depth);
    }
    disk_->PutBackPage(bucket_page_id, bucket_page);
    disk_->PutBackPage(split_bucket_page_id, split_bucket_page);
    return true;
}

bool DiskExtendibleHashTable::GetValue(std::string &key, std::string &value) {
    fill_string_to_length(key, HASH_TABLE_BUCKET_KEY_SIZE);
    uint32_t hash = Hash(key);
    uint32_t bucket_idx = hash & directory_region_->GetGlobalDepthMask();
    size_t bucket_page_id = directory_region_->GetBucketPageId(bucket_idx);
    HashTableBucketPage* bucket_page = reinterpret_cast<HashTableBucketPage *>(disk_->ReadPage(bucket_page_id));
    bool flag = bucket_page->GetValue(key, value);
    disk_->PutBackPage(bucket_page_id, bucket_page);
    return flag;
}

bool DiskExtendibleHashTable::Remove(std::string &key) {
    fill_string_to_length(key, HASH_TABLE_BUCKET_KEY_SIZE);
    uint32_t hash = Hash(key);
    uint32_t bucket_idx = hash & directory_region_->GetGlobalDepthMask();
    size_t bucket_page_id = directory_region_->GetBucketPageId(bucket_idx);
    HashTableBucketPage* bucket_page = reinterpret_cast<HashTableBucketPage *>(disk_->ReadPage(bucket_page_id));
    bool flag = bucket_page->Remove(key);
    disk_->PutBackPage(bucket_page_id, bucket_page);
    return flag;
}

}