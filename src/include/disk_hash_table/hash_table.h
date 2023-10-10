#pragma once

#include <list>
#include <unordered_map>
#include <mutex>
#include <spdlog/spdlog.h>

#include "common/consts.h"
#include "disk_hash_table/disk_extendible_hash_table.h"

namespace hybridfs {

class HashTable {
public:
    HashTable() {
        capacity_ = HASH_TABLE_BUFFER_CAPACITY;
        disk_hash_table_ = new DiskExtendibleHashTable();
    }

    void Insert(std::string &key, std::string &value) {
        std::lock_guard<std::mutex> lock(mtx_);
        Put(key, value);
        disk_hash_table_->Insert(key, value);
    }

    bool GetValue(std::string &key, std::string &value) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!Get(key, value)) {
            return disk_hash_table_->GetValue(key, value);
        }
        return true;
    }

    void Delete(std::string &key) {
        std::lock_guard<std::mutex> lock(mtx_);
        Remove(key);
        disk_hash_table_->Remove(key);
    }

private:
    size_t capacity_;
    std::mutex mtx_;
    DiskExtendibleHashTable* disk_hash_table_;
    std::list<std::pair<std::string, std::string>> cache_list_;
    std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>::iterator> cache_map_;

    bool Get(std::string key, std::string &value) {
        auto iter = cache_map_.find(key);
        if (iter == cache_map_.end()) {
            return false;
        }
        cache_list_.splice(cache_list_.begin(), cache_list_, iter->second);
        value = iter->second->second;
        return true;
    }

    void Put(std::string &key, std::string &value) {
        auto iter = cache_map_.find(key);
        if (iter != cache_map_.end()) {
            iter->second->second = value;
            cache_list_.splice(cache_list_.begin(), cache_list_, iter->second);
            return;
        }
        if (cache_map_.size() == capacity_) {
            std::string last_key = cache_list_.back().first;
            cache_list_.pop_back();
            cache_map_.erase(last_key);
        }
        cache_list_.emplace_front(key, value);
        cache_map_[key] = cache_list_.begin();
    }

    void Remove(std::string &key) {
        auto iter = cache_map_.find(key);
        if (iter != cache_map_.end()) {
            cache_list_.erase(cache_map_[key]);
            cache_map_.erase(key);
        }
    }
};


}