#include <random>
#include <iostream>
#include <murmur3/MurmurHash3.h>

int main() {
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789:";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, characters.size() - 1);

    for (int i = 0; i < 100; i++) {
        std::string str;
        for (int j = 0; j < 32; j++) {
            str += characters[distribution(generator)];
        }
        uint32_t hash = murmur3::MurmurHash3_x64_128(reinterpret_cast<const void *>(str.data()), 32, 0);
        std::cout << str + " :";
        for (int i = 31; i >= 0; i--) {
            uint32_t mask = 1 << i;
            uint32_t bit = (hash & mask) >> i;
            std::cout << bit;
        }
        std::cout << " " << hash << std::endl;
    }

    return 0;
}