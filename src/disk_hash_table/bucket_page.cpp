#include "disk_hash_table/bucket_page.h"

namespace hybridfs {

bool HashTableBucketPage::GetValue(const std::string &key, std::string &value) {
    for (size_t i = 0; i < HASH_TABLE_BUCKET_ARRAY_SIZE; i++) {
        if (IsOccupied(i) && key.substr(0, HASH_TABLE_BUCKET_KEY_SIZE) == KeyAt(i)) {
            value = ValueAt(i);
            return true;
        }
    }
    return false;
}

bool HashTableBucketPage::Insert(const std::string &key, const std::string &value) {
    int insert_pos = -1;
    for (size_t i = 0; i < HASH_TABLE_BUCKET_ARRAY_SIZE; i++) {
        if (IsOccupied(i)) {
            if (key.substr(0, HASH_TABLE_BUCKET_KEY_SIZE) == KeyAt(i)) {
                memcpy(GetData() + HASH_TABLE_BUCKET_ENTRY_SIZE * i + HASH_TABLE_BUCKET_KEY_SIZE + HASH_TABLE_BUCKET_ARRAY_OFFSET, value.data(), HASH_TABLE_BUCKET_VALUE_SIZE);
                MarkDirty();
                return true;
            }
        } else {
            if (insert_pos == -1) {
                insert_pos = i;
            }
        }
    }
    if (insert_pos != -1) {
        memcpy(GetData() + HASH_TABLE_BUCKET_ENTRY_SIZE * insert_pos + HASH_TABLE_BUCKET_ARRAY_OFFSET, key.data(), HASH_TABLE_BUCKET_KEY_SIZE);
        memcpy(GetData() + HASH_TABLE_BUCKET_ENTRY_SIZE * insert_pos + HASH_TABLE_BUCKET_KEY_SIZE + HASH_TABLE_BUCKET_ARRAY_OFFSET, value.data(), HASH_TABLE_BUCKET_VALUE_SIZE);
        SetOccupied(insert_pos, true);
        MarkDirty();
        return true;
    }
    return false;
}

bool HashTableBucketPage::Remove(const std::string &key) {
    for (size_t i = 0; i < HASH_TABLE_BUCKET_ARRAY_SIZE; i++) {
        if (IsOccupied(i) && key.substr(0, HASH_TABLE_BUCKET_KEY_SIZE) == KeyAt(i)) {
            SetOccupied(i, false);
            MarkDirty();
            return true;
        }
    }
    return false;
}

std::string HashTableBucketPage::KeyAt(size_t bucket_idx) {
    return std::string(GetData() + HASH_TABLE_BUCKET_ENTRY_SIZE * bucket_idx + HASH_TABLE_BUCKET_ARRAY_OFFSET, HASH_TABLE_BUCKET_KEY_SIZE);
}

std::string HashTableBucketPage::ValueAt(size_t bucket_idx) {
    return std::string(GetData() + HASH_TABLE_BUCKET_ENTRY_SIZE * bucket_idx + HASH_TABLE_BUCKET_KEY_SIZE + HASH_TABLE_BUCKET_ARRAY_OFFSET, HASH_TABLE_BUCKET_VALUE_SIZE);
}

void HashTableBucketPage::RemoveAt(size_t bucket_idx) {
    SetOccupied(bucket_idx, false);
    MarkDirty();
}

bool HashTableBucketPage::IsFull() {
    return NumOccupied() == HASH_TABLE_BUCKET_ARRAY_SIZE;
}

size_t HashTableBucketPage::NumOccupied() {
    size_t num = 0;
    for (size_t i = 0; i < HASH_TABLE_BUCKET_ARRAY_SIZE; i++) {
        if (IsOccupied(i)) {
            num++;
        }
    }
    return num;
}

bool HashTableBucketPage::IsOccupied(size_t bucket_idx) {
    size_t pos = bucket_idx / 8;
    size_t off = bucket_idx % 8;
    char mask = 1 << off;
    return *(GetData() + pos) & mask;
}

void HashTableBucketPage::SetOccupied(size_t bucket_idx, bool occupied) {
    size_t pos = bucket_idx / 8;
    size_t off = bucket_idx % 8;
    char mask = 1 << off;
    if (occupied) {
        *(GetData() + pos) |= mask;
    } else {
        *(GetData() + pos) &= ~mask;
    }
}

}