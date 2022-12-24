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

    pair<int, int> H = {1, 1};
    std::array<pair<int, int>, 9> T;
    for (auto &t : T) {
        t.first = 1;
        t.second = 1;
    }

    set<pair<int, int>> visited;
    visited.insert(H);

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
            adjustTail(H, T[0]);
            adjustTail(T[0], T[1]);
            adjustTail(T[1], T[2]);
            adjustTail(T[2], T[3]);
            adjustTail(T[3], T[4]);
            adjustTail(T[4], T[5]);
            adjustTail(T[5], T[6]);
            adjustTail(T[6], T[7]);
            adjustTail(T[7], T[8]);

            /*cout << "[" << pos << " " << i << "] ";
            cout << "H(" << H.first << " " << H.second << ") ";
            for (const auto &t : T) {
                cout << "(" << t.first << " " << t.second << ") ";
            }
            cout << endl;*/

            visited.insert(T[8]);
        }
        // << "-----" << pos << " " << l << "------ " << endl;
    }

    int res = 0;
    cout << "solution= " << visited.size() << endl;

    /*for (int i = 10; i >= -10; --i) {
        for (int j = -10; j < 15; ++j) {
            if (visited.find({i, j}) == visited.end()) {
                cout << ".";
            } else {
                cout << "#";
            }
        }
        cout << endl;
    }*/
}
