#pragma once

#include <string>

#include "common/consts.h"
#include "disk_page/page.h"

namespace hybridfs {

class HashTableBucketPage: public Page {
public:
    bool GetValue(const std::string &key, std::string &result);
    bool Insert(const std::string &key, const std::string &value);
    bool Remove(const std::string &key);
    std::string KeyAt(size_t bucket_idx);
    std::string ValueAt(size_t bucket_idx);
    void RemoveAt(size_t bucket_idx);
    bool IsFull();
    size_t NumOccupied();

private:
    bool IsOccupied(size_t bucket_idx);
    void SetOccupied(size_t bucket_idx, bool occupied);
};

}