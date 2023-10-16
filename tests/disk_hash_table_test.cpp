#include <iomanip>
#include <sstream>
#include <iostream>
#include "disk_hash_table/disk_extendible_hash_table.h"

int main() {
    hybridfs::DiskExtendibleHashTable* index = new hybridfs::DiskExtendibleHashTable();

    for (int i = 0; i < 1000; i++) {
        // std::cout << i << std::endl;
        std::string key = "test_key_" + std::to_string(i);
        std::string value = "test_value_" + std::to_string(i);
        index->Insert(key, value);
    }

    for (int i = 0; i < 1000; i++) {
        // std::cout << i << std::endl;
        std::string key = "test_key_" + std::to_string(i);
        std::string value = "test_value_" + std::to_string(i);
        std::string raw_value;
        index->GetValue(key, raw_value);
        std::cout << raw_value.substr(0, value.size()) << std::endl;
        // if (raw_value.substr(0, value.size()) != value) {
        //     std::cout << "Get Error: " << key << "\n";
        //     std::cout << raw_value << std::endl;
        // }
    }

    // for (int i = 20000; i < 30000; i++) {
    //     std::string inode = std::to_string(i);
    //     std::stringstream ss;
    //     ss << std::right << std::setw(5) << std::setfill('0') << inode;
    //     std::string key = "DIR:" + ss.str() + ":test";
    //     index->Delete(key);
    // }

    // for (int i = 0; i < 20000; i++) {
    //     std::string inode = std::to_string(i);
    //     std::stringstream ss;
    //     ss << std::right << std::setw(5) << std::setfill('0') << inode;
    //     std::string key = "DIR:" + ss.str() + ":test";
    //     std::string value = "i:" + std::to_string(i);
    //     std::string raw_value;
    //     index->GetValue(key, raw_value);
    //     if (value != raw_value.substr(0, value.size())) {
    //         std::cout << "Get Error: " << key << "\n";
    //     }
    // }

    // for (int i = 20000; i < 30000; i++) {
    //     std::string inode = std::to_string(i);
    //     std::stringstream ss;
    //     ss << std::right << std::setw(5) << std::setfill('0') << inode;
    //     std::string key = "DIR:" + ss.str() + ":test";
    //     std::string raw_value;
    //     if (index->GetValue(key, raw_value)) {
    //         std::cout << "Not Delete: " << key << " " << raw_value << "\n";
    //     }
    // }

    // for (int i = 30000; i < 100000; i++) {
    //     std::string inode = std::to_string(i);
    //     std::stringstream ss;
    //     ss << std::right << std::setw(5) << std::setfill('0') << inode;
    //     std::string key = "DIR:" + ss.str() + ":test";
    //     std::string value = "i:" + std::to_string(i);
    //     std::string raw_value;
    //     index->GetValue(key, raw_value);
    //     if (value != raw_value.substr(0, value.size())) {
    //         std::cout << "Get Error: " << key << "\n";
    //     }
    // }

    return 0;
}