//----------------------------------------
// --- Day 6: Wait For It ---
// https://adventofcode.com/2023/day/6
//----------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <array>

using namespace std;
using VectNumbers = std::vector<long>;

void readNumbers(const string &s, VectNumbers &res)
{
    std::stringstream ss(s);
    for (int i = 0; ss >> i;) {
        res.push_back(i);
    }
}

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
    cout << times_str << endl;
    cout << distance_str << endl;

    VectNumbers times, distance;
    readNumbers(times_str, times);
    readNumbers(distance_str, distance);

    long num_ways = 1;

    auto get_distance = [](auto charge, auto race_time) { return (race_time - charge) * charge; };

    for (long i = 0; i < times.size(); ++i) {
        long num = 0;
        for (long j = 0; j < times[i] + 1; ++j) {
            if (get_distance(j, times[i]) > distance[i]) {
                ++num;
            }
        }
        num_ways *= num;
    }
    cout << "res = " << num_ways << endl;
    return 0;
}