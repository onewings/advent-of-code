//-------------------------------------
// --- Day 1: Calorie Counting ---
// https://adventofcode.com/2022/day/1
//-------------------------------------

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

int main()
{
    std::ifstream ifs;
    ifs.open("day01.in");
    if (not ifs) {
        ifs.open("../day01.in");
    }

    std::string line;
    int i = 0;
    std::map<unsigned, unsigned> map;
    while (std::getline(ifs, line)) {
        if (line.empty()) {
            ++i;
            continue;
        }
        int temp = stoi(line);
        map[i] += temp;
    }
    int max = 0;
    for (const auto &[a, b] : map) {
        if (b > max) {
            max = b;
        }
    }
    std::cout << max << std::endl;
    return 0;
}