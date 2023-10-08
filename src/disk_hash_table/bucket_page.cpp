#include "disk_hash_table/bucket_page.h"

namespace hybridfs {

auto HashTableBucketPage::GetValue(std::string &key, std::string &value) -> bool {
    fill_string_to_length(key, HASH_TABLE_BUCKET_KEY_SIZE);
    for (size_t i = 0; i < HASH_TABLE_BUCKET_ARRAY_SIZE; i++) {
        if (IsOccupied(i) && key.substr(0, HASH_TABLE_BUCKET_KEY_SIZE) == KeyAt(i)) {
            value = ValueAt(i);
            return true;
        }
    }
    return false;
}

auto HashTableBucketPage::Insert(std::string &key, std::string &value) -> bool {
    fill_string_to_length(key, HASH_TABLE_BUCKET_KEY_SIZE);
    fill_string_to_length(value, HASH_TABLE_BUCKET_VALUE_SIZE);
    for (size_t i = 0; i < HASH_TABLE_BUCKET_ARRAY_SIZE; i++) {
        if (IsOccupied(i) && key.substr(0, HASH_TABLE_BUCKET_KEY_SIZE) == KeyAt(i)) {
            memcpy(GetData() + HASH_TABLE_BUCKET_ENTRY_SIZE * i + HASH_TABLE_BUCKET_KEY_SIZE + HASH_TABLE_BUCKET_ARRAY_OFFSET, value.data(), HASH_TABLE_BUCKET_VALUE_SIZE);
            return true;
        }
    }
    for (size_t i = 0; i < HASH_TABLE_BUCKET_ARRAY_SIZE; i++) {
        if (!IsOccupied(i)) {
            memcpy(GetData() + HASH_TABLE_BUCKET_ENTRY_SIZE * i + HASH_TABLE_BUCKET_ARRAY_OFFSET, key.data(), HASH_TABLE_BUCKET_KEY_SIZE);
            memcpy(GetData() + HASH_TABLE_BUCKET_ENTRY_SIZE * i + HASH_TABLE_BUCKET_KEY_SIZE + HASH_TABLE_BUCKET_ARRAY_OFFSET, value.data(), HASH_TABLE_BUCKET_VALUE_SIZE);
            SetOccupied(i, true);
            return true;
        }
    }
    return false;
}

auto HashTableBucketPage::Remove(std::string &key) -> bool {
    fill_string_to_length(key, HASH_TABLE_BUCKET_KEY_SIZE);
    for (size_t i = 0; i < HASH_TABLE_BUCKET_ARRAY_SIZE; i++) {
        if (IsOccupied(i) && key.substr(0, HASH_TABLE_BUCKET_KEY_SIZE) == KeyAt(i)) {
            SetOccupied(i, false);
            return true;
        }
    }
    return false;
}

auto HashTableBucketPage::IsFull() -> bool {
    return NumOccupied() == HASH_TABLE_BUCKET_ARRAY_SIZE;
}

auto HashTableBucketPage::IsEmpty() -> bool {
    return NumOccupied() == 0;;
}

auto HashTableBucketPage::NumOccupied() -> size_t {
    size_t num = 0;
    for (size_t i = 0; i < HASH_TABLE_BUCKET_ARRAY_SIZE; i++) {
        if (IsOccupied(i)) {
            num++;
        }
    }
    return num;
}

auto HashTableBucketPage::KeyAt(size_t bucket_idx) -> std::string {
    return std::string(GetData() + HASH_TABLE_BUCKET_ENTRY_SIZE * bucket_idx + HASH_TABLE_BUCKET_ARRAY_OFFSET, HASH_TABLE_BUCKET_KEY_SIZE);
}

auto HashTableBucketPage::ValueAt(size_t bucket_idx) -> std::string {
    return std::string(GetData() + HASH_TABLE_BUCKET_ENTRY_SIZE * bucket_idx + HASH_TABLE_BUCKET_KEY_SIZE + HASH_TABLE_BUCKET_ARRAY_OFFSET, HASH_TABLE_BUCKET_VALUE_SIZE);
}

void HashTableBucketPage::RemoveAt(size_t bucket_idx) {
    SetOccupied(bucket_idx, false);
}

auto HashTableBucketPage::IsOccupied(size_t bucket_idx) -> bool {
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