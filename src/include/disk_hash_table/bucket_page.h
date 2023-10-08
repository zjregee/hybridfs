#pragma once

#include <string>

#include "common/consts.h"
#include "utils/fill_string.h"
#include "disk_page/page.h"

namespace hybridfs {

class HashTableBucketPage: public Page {
public:
    auto GetValue(std::string &key, std::string &result) -> bool;
    auto Insert(std::string &key, std::string &value) -> bool;
    auto Remove(std::string &key) -> bool;
    auto IsFull() -> bool;
    auto IsEmpty() -> bool;
    auto NumOccupied() -> size_t;

private:
    auto KeyAt(size_t bucket_idx) -> std::string;
    auto ValueAt(size_t bucket_idx) -> std::string;
    void RemoveAt(size_t bucket_idx);
    auto IsOccupied(size_t bucket_idx) -> bool;
    void SetOccupied(size_t bucket_idx, bool occupied);
};

}