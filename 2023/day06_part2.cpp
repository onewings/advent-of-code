//----------------------------------------
// --- Day 6: Wait For It ---
// https://adventofcode.com/2023/day/6
//----------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <functional>
#include <array>

using namespace std;
using VectNumbers = std::vector<int>;

int main()
{
    std::ifstream ifs;
    ifs.open("day06.in");
    if (not ifs) {
        ifs.open("../day06.in");
    }

    std::string times_str, distance_str;
    unsigned sum = 0;

    std::getline(ifs, times_str);
    std::getline(ifs, distance_str);

    times_str = times_str.substr(10);
    distance_str = distance_str.substr(10);

    auto noSpaceEnd1 = remove(times_str.begin(), times_str.end(), ' ');
    times_str = string(times_str.begin(), noSpaceEnd1);
    cout << "1-st number = " << times_str << endl;

    auto noSpaceEnd2 = remove(distance_str.begin(), distance_str.end(), ' ');
    distance_str = string(distance_str.begin(), noSpaceEnd2);
    cout << "2-nd number = " << distance_str << endl;

    long t = stol(times_str);
    long d = stol(distance_str);

    auto get_distance = [](auto charge, auto race_time) { return (race_time - charge) * charge; };

    long num = 0;
    for (long j = 0; j < t + 1; ++j) {
        if (get_distance(j, t) > d) {
            ++num;
        }
    }

    cout << "res = " << num << endl;
    return 0;
}