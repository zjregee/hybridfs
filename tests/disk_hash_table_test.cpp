#include <iomanip>
#include <sstream>
#include <iostream>
#include "disk_hash_table/hash_table.h"

int main() {
    hybridfs::HashTable* index = new hybridfs::HashTable();

    for (int i = 0; i < 1000000; i++) {
        std::string inode = std::to_string(i);
        std::stringstream ss;
        ss << std::right << std::setw(10) << std::setfill('0') << inode;
        std::string key = "DIR:" + ss.str();
        std::string value = "i:" + std::to_string(i);
        index->Insert(key, value);
    }

    for (int i = 0; i < 1000000; i++) {
        std::string inode = std::to_string(i);
        std::stringstream ss;
        ss << std::right << std::setw(10) << std::setfill('0') << inode;
        std::string key = "DIR:" + ss.str();
        std::string value = "i:" + std::to_string(i);
        std::string raw_value;
        index->GetValue(key, raw_value);
        if (value != raw_value.substr(0, value.size())) {
            std::cout << "Get Error: " << key << "\n";
        }
    }

    for (int i = 20000; i < 30000; i++) {
        std::string inode = std::to_string(i);
        std::stringstream ss;
        ss << std::right << std::setw(5) << std::setfill('0') << inode;
        std::string key = "DIR:" + ss.str() + ":test";
        index->Delete(key);
    }

    for (int i = 0; i < 20000; i++) {
        std::string inode = std::to_string(i);
        std::stringstream ss;
        ss << std::right << std::setw(5) << std::setfill('0') << inode;
        std::string key = "DIR:" + ss.str() + ":test";
        std::string value = "i:" + std::to_string(i);
        std::string raw_value;
        index->GetValue(key, raw_value);
        if (value != raw_value.substr(0, value.size())) {
            std::cout << "Get Error: " << key << "\n";
        }
    }

    for (int i = 20000; i < 30000; i++) {
        std::string inode = std::to_string(i);
        std::stringstream ss;
        ss << std::right << std::setw(5) << std::setfill('0') << inode;
        std::string key = "DIR:" + ss.str() + ":test";
        std::string raw_value;
        if (index->GetValue(key, raw_value)) {
            std::cout << "Not Delete: " << key << " " << raw_value << "\n";
        }
    }

    for (int i = 30000; i < 100000; i++) {
        std::string inode = std::to_string(i);
        std::stringstream ss;
        ss << std::right << std::setw(5) << std::setfill('0') << inode;
        std::string key = "DIR:" + ss.str() + ":test";
        std::string value = "i:" + std::to_string(i);
        std::string raw_value;
        index->GetValue(key, raw_value);
        if (value != raw_value.substr(0, value.size())) {
            std::cout << "Get Error: " << key << "\n";
        }
    }

    return 0;
}