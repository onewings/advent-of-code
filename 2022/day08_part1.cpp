//-------------------------------------
// ---  Day 8: Treetop Tree House ---
// https://adventofcode.com/2022/day/8
//-------------------------------------

#include <iostream>
#include <sstream>
#include <string_view>
#include <cstring>
#include <array>
#include <algorithm>
#include <stack>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    std::ifstream ifs;
    ifs.open("day08.in");
    if (not ifs) {
        ifs.open("../day08.in");
    }

    std::string line;

    size_t length = 0;
    size_t height = 0;

    std::vector<std::string> map;

    while (std::getline(ifs, line)) {
        map.push_back(line);
    }
    length = line.length();
    height = map.size();

    int res = height + height + length + length - 4;

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < length - 1; ++j) {
            char current = map[i][j];
            bool found = false;

            //calculate left to right
            for (int z = j + 1; z <= length and not found; ++z) {
                if (map[i][z] >= current) {
                    break;
                }
                if (z == length) {
                    res++;
                    found = true;
                }
            }

            //calculate right to left
            for (int z = j - 1; z >= 0 and not found; --z) {
                if (map[i][z] >= current) {
                    break;
                }
                if (z == 0) {
                    res++;
                    found = true;
                }
            }

            //calculate top to bottom
            for (int z = i + 1; z <= height and not found; ++z) {
                if (map[z][j] >= current) {
                    break;
                }
                if (z == length) {
                    res++;
                    found = true;
                }
            }

            //calculate bottom to top
            for (int z = i - 1; z >= 0 and not found; --z) {
                if (map[z][j] >= current) {
                    break;
                }
                if (z == 0) {
                    res++;
                    found = true;
                }
            }
        }
    }
    cout << "solution= " << res << endl;
}
