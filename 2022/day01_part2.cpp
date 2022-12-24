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
    int max1 = 0;
    int max2 = 0;
    int max3 = 0;
    for (const auto &[a, b] : map) {
        if (b > max1) {
            max3 = max2;
            max2 = max1;
            max1 = b;
        } else if (b > max2) {
            max3 = max2;
            max2 = b;
        } else if (b > max3) {
            max3 = b;
        }
    }
    std::cout << max1 + max2 + max3 << std::endl;
    return 0;
}