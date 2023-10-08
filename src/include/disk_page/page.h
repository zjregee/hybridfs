#pragma once

#include <cstring>

#include "common/consts.h"

namespace hybridfs {

class Page {
public:
    Page() {
        data_ = new char[PAGE_SIZE];
        is_ditry = false;
        is_used = false;
    }

    ~Page() { delete[] data_; }

    auto GetData() -> char* { return data_; }
    
    void ResetMemory() { memset(data_, 0, PAGE_SIZE); }

    void SetUsed(bool used) { is_used = used; }

    auto CheckUsed() -> bool { return is_used; }

    void MarkDirty() { is_ditry = true; }

    auto CheckDirty() -> bool { return is_ditry; }

private:
    char* data_;
    bool is_used;
    bool is_ditry;
};

}