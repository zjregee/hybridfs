#pragma once

#include <cstddef>
#include <cmath>

namespace hybridfs {

constexpr size_t PAGE_SIZE = 4096;
constexpr size_t DISK_SIZE = 2 * 1024 * 1024 / 4;             // 2GB

constexpr size_t DISK_BUFFER_CAPACITY = 64 * 1024 / 4;        // 64MB

constexpr size_t NUM_PAGES_IN_BITMAP = 32768;

constexpr size_t HASH_TABLE_BUFFER_CAPACITY = 64 * 1024 / 4;  // 64MB

constexpr size_t HASH_TABLE_BUCKET_ARRAY_SIZE = 40;
constexpr size_t HASH_TABLE_BUCKET_ARRAY_OFFSET = 5;
constexpr size_t HASH_TABLE_BUCKET_KEY_SIZE = 32;
constexpr size_t HASH_TABLE_BUCKET_VALUE_SIZE = 64;
constexpr size_t HASH_TABLE_BUCKET_ENTRY_SIZE = 96;

constexpr size_t HASH_TABLE_DIRECTORY_ARRAY_SIZE = 500;
constexpr size_t HASH_TABLE_GLOBAL_DEPTH_OFFSET = 4000;

constexpr size_t HASH_TABLE_REGION_OFFSET = 0;
constexpr size_t HASH_TABLE_REGION_SIZE = 2 * 1024 * 1024 / 4; // 2GB
constexpr size_t HASH_TABLE_BITMAP_OFFSET = 0;
constexpr size_t HASH_TABLE_BITMAP_SIZE = (((HASH_TABLE_REGION_SIZE + 7) / 8) + PAGE_SIZE - 1) / PAGE_SIZE;
constexpr size_t HASH_TABLE_MAX_GLOBAL_DEPTH = 25;
constexpr size_t HASH_TABLE_DIRECTORY_REGION_OFFSET = HASH_TABLE_BITMAP_SIZE;
static const size_t HASH_TABLE_DIRECTORY_REGION_ARRAY_SIZE = pow(2, HASH_TABLE_MAX_GLOBAL_DEPTH);
static const size_t HASH_TABLE_DIRECTORY_REGION_SIZE = (HASH_TABLE_DIRECTORY_REGION_ARRAY_SIZE + HASH_TABLE_DIRECTORY_ARRAY_SIZE - 1) / HASH_TABLE_DIRECTORY_ARRAY_SIZE;

}