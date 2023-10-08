#pragma once

#include <cstddef>

namespace hybridfs {

constexpr size_t PAGE_SIZE = 4096;
constexpr size_t DISK_BUFFER_CAPACITY = 16384;  // 64MB
constexpr size_t DISK_FLUSH_TIME_INTERVAL = 60; // units: s
constexpr size_t NUM_PAGES_IN_BITMAP = 32768;

}