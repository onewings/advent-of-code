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

void PrintOneWingsTV(const array<string, 240> &data)
{
    cout << endl << "|------------- OneWings TV --------------|" << endl << "|";
    for (int i = 0; i < data.size(); ++i) {
        cout << data[i];
        if ((i + 1) % 40 == 0) {
            cout << "|" << endl;
            if (i < 200) {
                cout << "|";
            }
        }
    }
    cout << "|----------------------------------------|" << endl << endl;
}
int main()
{
    ifstream ifs;
    ifs.open("day10.in");
    if (not ifs) {
        ifs.open("../day10.in");
    }

    int total_cycles = 0;
    int X{1};

    array<string, 240> screen;
    for (auto &s : screen) {
        s = ' ';
    }

    auto CheckCycles = [&]() {
        if ((total_cycles % 40 >= X - 1) and (total_cycles % 40 <= X + 1)) {
            screen[total_cycles] = "█";
        }
    };

    string line;
    while (getline(ifs, line)) {
        if (line.rfind("noop", 0) == 0) {    //start_with in c++20
            CheckCycles();
            ++total_cycles;
            continue;
        } else {
            int temp = stoi(line.substr(5));
            for (int i = 0; i < 2; ++i) {
                CheckCycles();
                ++total_cycles;
            }
            X += temp;
        }
    }

    PrintOneWingsTV(screen);
}
