//--------------------------------------
//  --- Day 10: Cathode-Ray Tube ---
// https://adventofcode.com/2022/day/10
//--------------------------------------

#include <iostream>
#include <sstream>
#include <string_view>
#include <stdlib.h> /* abs */
#include <cstring>
#include <array>
#include <algorithm>
#include <stack>
#include <vector>
#include <fstream>
#include <utility>
#include <set>

using namespace std;

int main()
{
    std::ifstream ifs;
    ifs.open("day10.in");
    if (not ifs) {
        ifs.open("../day10.in");
    }

    int res = 0;
    std::string line;

    std::set<int> cycles{20, 60, 100, 140, 180, 220};
    int total_cycles = 0;
    int X{1};

    auto CheckCycles = [&]() {
        if (cycles.find(total_cycles) not_eq cycles.end()) {
            res += (X * total_cycles);
        }
    };

    while (std::getline(ifs, line)) {
        if (line.rfind("noop", 0) == 0) {    //start_with in c++20
            ++total_cycles;
            CheckCycles();
            continue;
        } else {
            int temp = stoi(line.substr(5));
            for (int i = 0; i < 2; ++i) {
                ++total_cycles;
                CheckCycles();
            }
            X += temp;
        }
    }

    cout << "solution= " << res << endl;
}
