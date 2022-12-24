//---------------------------------------
// --- Day 7: No Space Left On Device ---
//  https://adventofcode.com/2022/day/7
//---------------------------------------

#include <iostream>
#include <sstream>
#include <string_view>
#include <cstring>
#include <array>
#include <stack>
#include <vector>
#include <fstream>

using namespace std;

struct inode {
    int size{0};
    std::string name;
    struct inode *parent{nullptr};
    vector<inode> entries;
};

int Calculate(const inode &node)
{
    int res = 0;
    for (const auto &el : node.entries) {
        if (el.size <= 100000) {
            //cout << el.size << " " << el.name << endl;
            res += el.size;
        }
        res += Calculate(el);
    }
    return res;
}

int main()
{
    std::ifstream ifs;
    ifs.open("day07.in");
    if (not ifs) {
        ifs.open("../day07.in");
    }

    std::string line;
    inode root = {0, "/"};
    inode *current_dir = &root;
    while (std::getline(ifs, line)) {
        if (line == "$ cd ..") {
            current_dir = current_dir->parent;
            continue;
        }
        if (line.rfind("$ cd", 0) == 0) {    //start_with in c++20
            char temp[200];

            sscanf(line.c_str(), "$ cd %s", &temp);
            std::string current_directory = temp;
            for (auto &entry : current_dir->entries) {
                if (entry.name == current_directory) {
                    current_dir = &entry;
                }
            }
            continue;
        }

        if (line.rfind("$ ls", 0) == 0) {    //start_with in c++20
            continue;
        }

        if (line.rfind("dir", 0) == 0) {    //start_with in c++20
            char temp[200];
            sscanf(line.c_str(), "dir %s", &temp);
            std::string dirName = temp;
            current_dir->entries.push_back({0, dirName, current_dir});
            continue;
        }

        int file_size = 0;
        char temp[200];
        sscanf(line.c_str(), "%d %s", &file_size, &temp);
        std::string name = temp;
        current_dir->size += file_size;
        inode *iter = current_dir->parent;
        while (iter not_eq nullptr) {
            iter->size += file_size;
            iter = iter->parent;
        }
    }

    current_dir = &root;

    auto res = Calculate(root);
    cout << "solution= " << res << endl;
}
