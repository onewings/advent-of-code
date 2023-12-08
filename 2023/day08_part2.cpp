//----------------------------------------
// --- Day 8 part 2
// https://adventofcode.com/2023/day/8
//----------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <array>
#include <unordered_map>

#include <iostream>
#include <numeric>

using namespace std;
using MAP = unordered_map<string, std::pair<string, string>>;

int main()
{
    std::ifstream ifs;
    ifs.open("day08.in");
    if (not ifs) {
        ifs.open("../day08.in");
    }
    std::string inst;

    std::getline(ifs, inst);
    cout << inst << endl;

    MAP gmap;
    std::string line;

    std::vector<std::pair<string, string>> ncurrent;
    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        }
        char name[4];
        char left[4];
        char right[4];
        //format
        //AAA = (BBB, BBB)
        sscanf(line.c_str(), "%3s = (%3s, %3s)", &name, &left, &right);
        gmap.insert({name, {left, right}});

        if (name[2] == 'A') {
            cout << name << endl;

            ncurrent.push_back({left, right});
        }
    }

    cout << "************** size= " << ncurrent.size() << endl;
    std::vector<int> temp;
    for (int j = 0; j < ncurrent.size(); ++j) {
        long i = 0;
        bool found = false;
        while (not found) {
            for (char c : inst) {
                string token = (c == 'L') ? ncurrent[j].first : ncurrent[j].second;
                ncurrent[j] = gmap[token];
                ++i;
                if (token[2] == 'Z') {
                    found = true;
                    cout << "FOUND " << i << endl;
                    temp.push_back(i);
                    break;
                }
            }
        }
    }
    unsigned long long retval = 1;
    for (auto x : temp) {
        retval = lcm(retval, x);
    }

    cout << "res= " << retval << endl;
}