//-------------------------------------
// --- Day 1: Calorie Counting ---
// https://adventofcode.com/2023/day/1
//-------------------------------------

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include <string>
#include <algorithm>

using namespace std;

int main()
{
    std::ifstream ifs;
    ifs.open("day01.in");
    if (not ifs) {
        ifs.open("../day01.in");
    }

    std::string line;

    int count = 0;
    int number = 0;
    while (std::getline(ifs, line)) {
        auto it1 = std::find_if(line.begin(), line.end(), [](char c) { return std::isdigit(c); });
        auto it2 = std::find_if(line.rbegin(), line.rend(), [](char c) { return std::isdigit(c); });
        count += (*it1 - '0') * 10;
        count += (*it2 - '0');
    }

    std::cout << "count=" << count << std::endl;
    return 0;
}