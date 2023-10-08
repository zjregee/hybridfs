#pragma once

#include <cstddef>

namespace hybridfs {

constexpr size_t PAGE_SIZE = 4096;
constexpr size_t DISK_BUFFER_CAPACITY = 16384;  // 64MB
constexpr size_t DISK_FLUSH_TIME_INTERVAL = 60; // units: s
constexpr size_t NUM_PAGES_IN_BITMAP = 32768;
constexpr size_t HASH_TABLE_BUCKET_ARRAY_SIZE = 40;
constexpr size_t HASH_TABLE_BUCKET_ARRAY_OFFSET = 5;
constexpr size_t HASH_TABLE_BUCKET_KEY_SIZE = 32;
constexpr size_t HASH_TABLE_BUCKET_VALUE_SIZE = 64;
constexpr size_t HASH_TABLE_BUCKET_ENTRY_SIZE = 96;
constexpr size_t HASH_TABLE_DIRECTORY_ARRAY_SIZE = 500;
constexpr size_t HASH_TABLE_GLOBAL_DEPTH_OFFSET = 4000;

}