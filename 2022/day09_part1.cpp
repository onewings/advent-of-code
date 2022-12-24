//--------------------------------------
//     --- Day 9: Rope Bridge ---
// https://adventofcode.com/2022/day/9
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

void adjustTail(const pair<int, int> &H, pair<int, int> &T)
{
    if (H == T) {
        return;
    }
    if ((H.first >= T.first - 1 and H.first <= T.first + 1)
        and (H.second >= T.second - 1 and H.second <= T.second + 1)) {
        return;    //in the square
    }

    if ((abs(H.first - T.first) == 2) and (H.second == T.second))    //horizontally
    {
        if (T.first < H.first) {
            T.first++;
        } else {
            T.first--;
        }
        return;
    }

    if ((abs(H.second - T.second) == 2) and (H.first == T.first))    //vertically
    {
        if (H.second < T.second) {
            T.second--;
        } else {
            T.second++;
        }
        return;
    }

    //diagonalley
    {
        if (T.first + 2 == H.first) {
            T.first++;
            if (H.second > T.second) {
                T.second++;
            } else {
                T.second--;
            }
            return;
        }
        if (T.first - 2 == H.first) {
            T.first--;
            if (H.second > T.second) {
                T.second++;
            } else {
                T.second--;
            }
            return;
        }

        if (T.second + 2 == H.second) {
            T.second++;
            if (H.first > T.first) {
                T.first++;
            } else {
                T.first--;
            }
            return;
        }
        if (T.second - 2 == H.second) {
            T.second--;
            if (H.first > T.first) {
                T.first++;
            } else {
                T.first--;
            }
            return;
        }
    }
}

int main()
{
    std::ifstream ifs;
    ifs.open("day09.in");
    if (not ifs) {
        ifs.open("../day09.in");
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

    pair<int, int> T = {1, 1};
    pair<int, int> H = T;

    set<pair<int, int>> visited;
    visited.insert(T);

    for (const auto &m : map) {
        char pos;
        int l = 0;
        sscanf(m.c_str(), "%s %d", &pos, &l);
        //cout << pos << " " << l << "    ";

        for (int i = 0; i < l; ++i) {
            if (pos == 'R') {
                H.second++;
            }
            if (pos == 'U') {
                H.first++;
            }
            if (pos == 'L') {
                H.second--;
            }
            if (pos == 'D') {
                H.first--;
            }
            //cout << H.first << " " << H.second << endl;

            //cout << pos << " " << H.first << " " << H.second << " - " << T.first << " " << T.second << " = >";
            adjustTail(H, T);
            visited.insert(T);
            //cout << T.first << " " << T.second << endl;
        }
    }

    int res = 0;
    cout << "solution= " << visited.size() << endl;
}
