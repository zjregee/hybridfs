#include "disk_hash_table/directory_page.h"

namespace hybridfs {

uint32_t HashTableDirectoryPage::GetGlobalDepth() {
    return *reinterpret_cast<uint32_t *>(GetData() + HASH_TABLE_GLOBAL_DEPTH_OFFSET);
}

void HashTableDirectoryPage::SetGlobalDepth(uint32_t global_depth) {
    memcpy(GetData() + HASH_TABLE_GLOBAL_DEPTH_OFFSET, &global_depth, 4);
    MarkDirty();
}

void HashTableDirectoryPage::IncrGlobalDepth() {
    SetGlobalDepth(GetGlobalDepth() + 1);
    MarkDirty();
}

void HashTableDirectoryPage::DecrGlobalDepth() {
    SetGlobalDepth(GetGlobalDepth() - 1);
    MarkDirty();
}

uint32_t HashTableDirectoryPage::GetLocalDepth(size_t bucket_idx) {
    return *reinterpret_cast<uint32_t *>(GetData() + 4 * bucket_idx);
}

void HashTableDirectoryPage::SetLocalDepth(size_t bucket_idx, uint32_t local_depth) {
    memcpy(GetData() + 4 * bucket_idx, &local_depth, 4);
    MarkDirty();
}

uint32_t HashTableDirectoryPage::GetBucketPageId(size_t bucket_idx) {
    return *reinterpret_cast<uint32_t *>(GetData() + 4 * HASH_TABLE_DIRECTORY_ARRAY_SIZE + 4 * bucket_idx);
}

void HashTableDirectoryPage::SetBucketPageId(size_t bucket_idx, uint32_t bucket_page_id) {
    memcpy(GetData() + 4 * HASH_TABLE_DIRECTORY_ARRAY_SIZE + 4 * bucket_idx, &bucket_page_id, 4);
    MarkDirty();
}

}