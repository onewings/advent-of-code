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
#include <set>

using namespace std;

struct inode {
    int size{0};
    string name;
    struct inode *parent{nullptr};
    vector<inode> entries;
};

void Calculate(const inode &node, int freeSize, set<int> &result)
{
    for (const auto &el : node.entries) {

        if (el.size >= freeSize) {
            //cout << el.size << " " << el.name << endl;
            result.insert(el.size);
        }
        Calculate(el, freeSize, result);
    }
}

int main()
{
    ifstream ifs;
    ifs.open("day07.in");
    if (not ifs) {
        ifs.open("../day07.in");
    }

    string line;
    inode root = {0, "/"};
    inode *current_dir = &root;
    while (getline(ifs, line)) {
        if (line == "$ cd ..") {
            current_dir = current_dir->parent;
            continue;
        }
        if (line.rfind("$ cd", 0) == 0) {    //start_with in c++20

            char temp[200];

            sscanf(line.c_str(), "$ cd %s", &temp);
            string current_directory = temp;
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
            string dirName = temp;
            current_dir->entries.push_back({0, dirName, current_dir});
            continue;
        }

        int file_size = 0;
        char temp[200];
        sscanf(line.c_str(), "%d %s", &file_size, &temp);
        string name = temp;
        current_dir->size += file_size;

        inode *iter = current_dir->parent;
        while (iter not_eq nullptr) {
            iter->size += file_size;
            iter = iter->parent;
        }
    }

    current_dir = &root;
    int sizeExceeded = -(70000000 - 30000000 - root.size);

    set<int> result;
    Calculate(root, sizeExceeded, result);
    cout << "solution= " << *result.begin() << endl;
}
