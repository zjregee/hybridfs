#include <iostream>
#include <string>

#include "disk/disk.h"
#include "disk_hash_table/bucket_page.h"

void fill_string_to_length(std::string &str, size_t length) {
    if (str.length() < length) {
        str.insert(0, std::string(length - str.length(), '0'));
    }
}

int main() {
    hybridfs::Disk* disk = new hybridfs::Disk("sim_disk", 0, 256, false);
    hybridfs::HashTableBucketPage* page = reinterpret_cast<hybridfs::HashTableBucketPage *>(disk->ReadPage(0));

    for (size_t i = 0; i < 40; i++) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        fill_string_to_length(key, 32);
        fill_string_to_length(value, 64);
        if (!page->Insert(key, value)) {
            std::cout << "error exists" << std::endl;
        }
    }

    for (size_t i = 0; i < 40; i++) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        fill_string_to_length(key, 32);
        fill_string_to_length(value, 64);
        std::string raw_value;
        if (!page->GetValue(key, raw_value) || raw_value != value) {
            std::cout << "error exists" << std::endl;
        }
    }

    for (size_t i = 0; i < 40; i++) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        fill_string_to_length(key, 32);
        fill_string_to_length(value, 64);
        if (page->KeyAt(i) != key) {
            std::cout << "error exists" << std::endl;
        }
        if (page->ValueAt(i) != value) {
            std::cout << "error exists" << std::endl;
        }
    }

    for (size_t i = 10; i < 20; i++) {
        std::string key = "key" + std::to_string(i);
        fill_string_to_length(key, 32);
        if (!page->Remove(key)) {
            std::cout << "error exists" << std::endl;
        }
    }

    for (size_t i = 20; i < 30; i++) {
        page->RemoveAt(i);
    }

    for (size_t i = 0; i < 10; i++) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        fill_string_to_length(key, 32);
        fill_string_to_length(value, 64);
        std::string raw_value;
        if (!page->GetValue(key, raw_value) || raw_value != value) {
            std::cout << "error exists" << std::endl;
        }
    }

    for (size_t i = 10; i < 30; i++) {
        std::string key = "key" + std::to_string(i);
        std::string value;
        if (page->GetValue(key, value)) {
            std::cout << "error exists" << std::endl;
        }
    }

    for (size_t i = 30; i < 40; i++) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        fill_string_to_length(key, 32);
        fill_string_to_length(value, 64);
        std::string raw_value;
        if (!page->GetValue(key, raw_value) || raw_value != value) {
            std::cout << "error exists" << std::endl;
        }
    }

    for (size_t i = 10; i < 30; i++) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        fill_string_to_length(key, 32);
        fill_string_to_length(value, 64);
        if (!page->Insert(key, value)) {
            std::cout << "error exists" << std::endl;
        }
    }

    for (size_t i = 0; i < 40; i++) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        fill_string_to_length(key, 32);
        fill_string_to_length(value, 64);
        std::string raw_value;
        if (!page->GetValue(key, raw_value) || raw_value != value) {
            std::cout << "error exists" << std::endl;
        }
    }

    for (size_t i = 10; i < 30; i++) {
        std::string key = "key" + std::to_string(i);
        fill_string_to_length(key, 32);
        if (!page->Remove(key)) {
            std::cout << "error exists" << std::endl;
        }
    }

    for (size_t i = 0; i < 40; i++) {
        std::string key = "key" + std::to_string(i);
        std::string value = "new_value" + std::to_string(i);
        fill_string_to_length(key, 32);
        fill_string_to_length(value, 64);
        if (!page->Insert(key, value)) {
            std::cout << "error exists" << std::endl;
        }
    }

    for (size_t i = 0; i < 40; i++) {
        std::string key = "key" + std::to_string(i);
        std::string value = "new_value" + std::to_string(i);
        fill_string_to_length(key, 32);
        fill_string_to_length(value, 64);
        std::string raw_value;
        if (!page->GetValue(key, raw_value) || raw_value != value) {
            std::cout << "error exists" << std::endl;
        }
    }

    for (size_t i = 0; i < 40; i++) {
        std::string key = "new_key" + std::to_string(i);
        std::string value = "new_value" + std::to_string(i);
        fill_string_to_length(key, 32);
        fill_string_to_length(value, 64);
        if (page->Insert(key, value)) {
            std::cout << "error exists" << std::endl;
        }
    }

    disk->PutBackPage(0, page);
    delete disk;

    return 0;
}