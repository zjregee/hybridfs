#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <algorithm>

#include "disk_hash_table/hash_table.h"

int main(int argc, char* argv[]) {
    size_t data_num;
    size_t key_size;
    size_t value_size;

    if (argc < 4) {
        data_num = 1'0000;
        key_size = 32;
        value_size = 64;
    } else {
        data_num = std::atoi(argv[1]);
        key_size = std::atoi(argv[2]);
        value_size = std::atoi(argv[3]);
    }

    std::vector<std::string> random_keys;
    std::vector<std::string> random_values;
    std::vector<std::string> random_query_keys;

    random_keys.reserve(data_num);
    random_values.reserve(data_num);
    random_query_keys.reserve(2 * data_num);

    const std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, charset.size() - 1);

    for (size_t i = 0; i < data_num; i++) {
        std::string random_key;
        std::string random_value;
        std::string null_query_key;
        random_key.reserve(key_size);
        random_value.reserve(value_size);
        null_query_key.reserve(key_size);
        for (size_t j = 0; j < key_size; j++) {
            random_key.push_back(charset[distribution(generator)]);
        }
        for (size_t j = 0; j < value_size; j++) {
            random_value.push_back(charset[distribution(generator)]);
        }
        for (size_t j = 0; j < key_size; j++) {
            null_query_key.push_back(charset[distribution(generator)]);
        }
        random_keys.push_back(random_key);
        random_values.push_back(random_value);
        random_query_keys.push_back(random_key);
        random_query_keys.push_back(null_query_key);
    }

    std::shuffle(random_query_keys.begin(), random_query_keys.end(), generator);

    hybridfs::HashTable* index = new hybridfs::HashTable();

    {
        auto start_time = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < data_num; i++) {
            index->Insert(random_keys[i], random_values[i]);
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "HashTable 数据插入时间：" << duration.count() << "ms" << std::endl; 
    }

    {
        auto start_time = std::chrono::high_resolution_clock::now();

        std::string value;
        for (size_t i = 0; i < 2 * data_num; i++) {
            index->GetValue(random_query_keys[i], value);
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "HashTable 数据查询时间：" << duration.count() << "ms" << std::endl;
    }

    {
        auto start_time = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < 2 * data_num; i++) {
            index->Delete(random_query_keys[i]);
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "HashTable 数据删除时间：" << duration.count() << "ms" << std::endl;
    }

    return 0;
}