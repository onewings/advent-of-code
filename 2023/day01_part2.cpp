//-------------------------------------
// --- Day 1: Calorie Counting ---
// https://adventofcode.com/2023/day/1
//-------------------------------------

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include <array>
#include <string>
#include <algorithm>

using namespace std;

int analize_string_from_left(const std::string &line)
{
    auto it1 = std::find_if(line.begin(), line.end(), [](char c) { return std::isdigit(c); });
    int digit = 0;
    int dist = 1215752191;
    if (it1 not_eq line.end()) {
        digit = (*it1 - '0');
        dist = std::distance(line.begin(), it1);
    }
    std::array<std::string, 9> dict{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int count = 1;
    for (const auto &k : dict) {
        std::size_t found = line.find(k);
        if (found not_eq std::string::npos and found < dist) {
            digit = count;
            dist = found;
        }
        ++count;
    }
    return digit;
}

int analize_string_from_right(const std::string &line)
{
    auto it1 = std::find_if(line.rbegin(), line.rend(), [](char c) { return std::isdigit(c); });
    int digit = 0;
    int dist = 0;
    if (it1 not_eq line.rend()) {
        digit = (*it1 - '0');
        dist = line.length() - std::distance(line.rbegin(), it1) - 1;
    }
    std::array<std::string, 9> dict{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int count = 1;
    for (const auto &k : dict) {
        std::size_t found = line.rfind(k);
        if (found not_eq std::string::npos and (found) > dist) {
            digit = count;
            dist = found;
        }
        ++count;
    }
    return digit;
}

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
        count += analize_string_from_left(line) * 10;
        count += analize_string_from_right(line);
    }

    std::cout << "count=" << count << std::endl;
    return 0;
}