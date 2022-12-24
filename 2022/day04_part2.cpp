//--------------------------------------
// --- Day 4: Camp Cleanup ---
// https://adventofcode.com/2022/day/4
//--------------------------------------

#include <iostream>
#include <fstream>
#include <string_view>
#include <cstring>

using namespace std;

int main()
{
    std::ifstream ifs;
    ifs.open("day04.in");
    if (not ifs) {
        ifs.open("../day04.in");
    }

    std::string line;

    unsigned total = 0;

    while (std::getline(ifs, line)) {
        auto middle = line.find(',');
        string a = line.substr(0, middle);
        string b = line.substr(middle + 1);

        auto middle1 = a.find('-');
        string a1 = a.substr(0, middle1);
        string a2 = a.substr(middle1 + 1);

        auto middle2 = b.find('-');
        string b1 = b.substr(0, middle2);
        string b2 = b.substr(middle2 + 1);

        int c1 = stoi(a1);
        int c2 = stoi(a2);
        int d1 = stoi(b1);
        int d2 = stoi(b2);
        //std::cout << c1 << " " << c2 << " " << d1 << " " << d2 << " " << endl;
        if ((d1 <= c2 and d1 >= c1) or (d2 >= c1 and d2 <= c2)) {
            total++;
        }

        else if ((c1 <= d2 and c1 >= d1) or (c2 >= d1 and c2 <= d2)) {
            total++;
        }
    }
    std::cout << total << endl;
    return 0;
}
