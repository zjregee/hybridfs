#pragma once

#include <cstring>

#include "common/consts.h"

namespace hybridfs {

class Page {
public:
    Page() {
        data_ = new char[PAGE_SIZE];
        is_ditry = false;
    }

    ~Page() { delete[] data_; }

    auto GetData() -> char* { return data_; }
    
    void ResetMemory() { memset(data_, 0, PAGE_SIZE); }

    void MarkDirty() { is_ditry = true; }

    auto CheckDirty() -> bool { return is_ditry; }

private:
    char* data_;
    bool is_ditry;
};

}