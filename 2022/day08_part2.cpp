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

    size_t length = 0;
    size_t height = 0;

    std::vector<std::string> map;
    std::string line;
    while (std::getline(ifs, line)) {
        map.push_back(line);
    }
    length = line.length();
    height = map.size();

    int scenic_score = 1;

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < length - 1; ++j) {
            char current = map[i][j];

            int scenic_score1 = 0;
            //calculate left to right
            for (int z = j + 1; z < length; ++z) {
                scenic_score1++;
                if (map[i][z] >= current) {
                    break;
                }
            }

            //calculate right to left
            int scenic_score2 = 0;
            for (int z = j - 1; z >= 0; --z) {
                scenic_score2++;
                if (map[i][z] >= current) {
                    break;
                }
            }

            //calculate top to bottom
            int scenic_score3 = 0;
            for (int z = i + 1; z < height; ++z) {
                scenic_score3++;
                if (map[z][j] >= current) {
                    break;
                }
            }

            //calculate bottom to top
            int scenic_score4 = 0;
            for (int z = i - 1; z >= 0; --z) {
                ++scenic_score4;
                if (map[z][j] >= current) {
                    break;
                }
            }
            scenic_score = std::max(scenic_score, scenic_score1 * scenic_score2 * scenic_score3 * scenic_score4);
        }
    }
    cout << "solution= " << scenic_score << endl;
}
