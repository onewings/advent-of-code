//----------------------------------------
// --- Day 8 part 1
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
    }

    std::pair<string, string> current = gmap["AAA"];
    cout << "AAA " << current.first << " " << current.second << endl;
    bool found = false;
    int i = 0;
    while (not found) {
        for (char c : inst) {
            cout << c;

            string token = (c == 'L') ? current.first : current.second;
            cout << " (" << token << ") " << current.first << " " << current.second << " *** ";

            current = gmap[token];
            cout << " (" << token << ") " << current.first << " " << current.second << endl;
            ++i;
            if (token == "ZZZ") {
                found = true;
                cout << "FOUND" << endl;
                break;
            }
        }
    }

    cout << endl;
    cout << "res=" << i << endl;
}