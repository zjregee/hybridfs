#pragma once

#include <string>

namespace hybridfs {

void fill_string_to_length(std::string &str, size_t length) {
    if (str.length() < length) {
        str.append(std::string(length - str.length(), '0'));
    }
}

}