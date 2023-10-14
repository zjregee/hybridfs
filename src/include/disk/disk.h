#pragma once

#include <list>
#include <unordered_map>
#include <fcntl.h>
#include <unistd.h>
#include <spdlog/spdlog.h>

#include "common/defines.h"
#include "common/consts.h"
#include "disk_page/page.h"

namespace hybridfs {

class Disk {
public:
    Disk(std::string disk_name, size_t offset, size_t page_num, bool enabled_buffer, size_t buffer_capacity = DISK_BUFFER_CAPACITY) {
        offset_ = offset;
        page_num_ = page_num;
        enabled_buffer_ = enabled_buffer;
        fd_ = open(disk_name.c_str(), O_RDWR);
        if (fd_ == -1) {
            spdlog::error("open error");
            exit(1);
        }
        if (enabled_buffer) {
            capacity_ = buffer_capacity;
        }
    }

    ~Disk() {
        Flush();
    }

    Page* ReadPage(size_t page_id) {
        if (enabled_buffer_) {
            Page* page = Get(page_id);
            if (page != nullptr) {
                page->SetUsed(true);
                return page;
            }
            page = new Page();
            off_t off = (page_id + offset_) * PAGE_SIZE;
            if (lseek(fd_, off, SEEK_SET) == -1) {
                spdlog::error("lseek error");
                exit(1);
            }
            if (read(fd_, page->GetData(), PAGE_SIZE) == -1) {
                spdlog::error("read error");
                exit(1);
            }
            Put(page_id, page);
            page->SetUsed(true);
            return page;
        } else {
            Page* page = new Page();
            off_t off = (page_id + offset_) * PAGE_SIZE;
            if (lseek(fd_, off, SEEK_SET) == -1) {
                spdlog::error("lseek error");
                exit(1);
            }
            if (read(fd_, page->GetData(), PAGE_SIZE) == -1) {
                spdlog::error("read error");
                exit(1);
            }
            return page;
        }
    }

    void PutBackPage(size_t page_id, Page* p) {
        if (enabled_buffer_) {
            p->SetUsed(false);
        } else {
            if (p->CheckDirty()) {
                off_t off = (page_id + offset_) * PAGE_SIZE;
                if (lseek(fd_, off, SEEK_SET) == -1) {
                    spdlog::error("lseek error");
                    exit(1);
                }
                if (write(fd_, p->GetData(), PAGE_SIZE) == -1) {
                    spdlog::error("write error");
                    exit(1);
                }
            }
            delete p;
        }
    }

    void Flush() {
        if (enabled_buffer_) {
            for (auto &entry: cache_list_) {
                if (entry.second->CheckUsed()) {
                    spdlog::error("some page is not put back");
                    exit(1);
                }
            }
            for (auto &entry: cache_list_) {
                if (entry.second->CheckDirty()) {
                    off_t off = (entry.first + offset_) * PAGE_SIZE;
                    if (lseek(fd_, off, SEEK_SET) == -1) {
                        spdlog::error("lseek error");
                        exit(1);
                    }
                    if (write(fd_, entry.second->GetData(), PAGE_SIZE) == -1) {
                        spdlog::error("write error");
                        exit(1);
                    }
                }
                delete entry.second;
            }
            cache_list_.clear();
            cache_map_.clear();
        }
    }

private:
    int fd_;
    bool enabled_buffer_;
    size_t offset_;
    size_t page_num_;
    size_t capacity_;
    std::list<std::pair<size_t, Page*>> cache_list_;
    std::unordered_map<size_t, std::list<std::pair<size_t, Page*>>::iterator> cache_map_;

    Page* Get(size_t page_id) {
        auto iter = cache_map_.find(page_id);
        if (iter == cache_map_.end()) {
            return nullptr;
        }
        cache_list_.splice(cache_list_.begin(), cache_list_, iter->second);
        return iter->second->second;
    }

    void Put(size_t page_id, Page* p) {
        auto iter = cache_map_.find(page_id);
        if (iter != cache_map_.end()) {
            cache_list_.splice(cache_list_.begin(), cache_list_, iter->second);
            return;
        }
        if (cache_map_.size() == capacity_) {
            size_t last_page_id = cache_list_.back().first;
            Page* last_page = cache_list_.back().second;
            if (last_page->CheckDirty()) {
                off_t off = (last_page_id + offset_) * PAGE_SIZE;
                if (lseek(fd_, off, SEEK_SET) == -1) {
                    spdlog::error("lseek error");
                    exit(1);
                }
                if (write(fd_, last_page->GetData(), PAGE_SIZE) == -1) {
                    spdlog::error("read error");
                    exit(1);
                }
            }
            cache_list_.pop_back();
            cache_map_.erase(last_page_id);
            delete last_page;
        }
        cache_list_.emplace_front(page_id, p);
        cache_map_[page_id] = cache_list_.begin();
    }
};

}