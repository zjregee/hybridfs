#include <list>
#include <iostream>
#include <unordered_map>

int main() {
    {
        std::list<std::pair<std::string, std::string>> list;
        std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>::iterator> map;

        for (int i = 0; i < 5; i++) {
            list.emplace_front(std::to_string(i), std::to_string(i));
            map[std::to_string(i)] = list.begin();
        }

        auto iter = map.find(std::to_string(2));
        list.splice(list.begin(), list, iter->second);

        for (auto &entry : list) {
            std::cout << entry.first << " ";
        }
        std::cout << std::endl;
        std::cout << iter->second->second << std::endl;
        std::cout << map[std::to_string(2)]->second << std::endl;
    }

    {
        std::unordered_map<std::string, std::string> map;

        std::string key = "key";
        std::string value = "value";

        map[key] = value;

        value = "new_value";

        std::cout << value << std::endl;
        std::cout << map[key] << std::endl;
    }

    return 0;
}