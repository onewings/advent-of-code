//-------------------------------------
//--- Day 15: Beacon Exclusion Zone ---
//https://adventofcode.com/2022/day/15
//-------------------------------------

#include <iostream>
#include <sstream>
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

struct Range {
    int x1;
    int x2;
};

struct Item {
    int x1;
    int y1;
    int x2;
    int y2;
};
const int inputY = 4000000;

int find_non_excluded(vector<Range> &items)
{
    int res = 0;
    sort(items.begin(), items.end(), [](const auto &left, const auto &right) { return left.x1 < right.x1; });

    for (const auto &el : items) {
        if (el.x1 > res) {
            return res;
        }
        res = max(res, el.x2 + 1);
    }

    return res < inputY ? res : -1;
}

int main()
{
    ifstream ifs;
    ifs.open("day15.in");
    if (not ifs) {
        ifs.open("../day15.in");
    }

    string line;
    vector<Item> Items;

    while (getline(ifs, line)) {
        int x1, y1, x2, y2;
        sscanf(line.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &x1, &y1, &x2, &y2);
        Items.push_back({x1, y1, x2, y2});
    }

    int x = -1;
    int y = -1;

    for (int i = 0; i <= inputY + 1; ++i) {
        vector<Range> excludeY, excludeX;
        for (const auto &r : Items) {

            int manhatten = abs(r.x1 - r.x2) + abs(r.y1 - r.y2);
            if (manhatten >= abs(i - r.y1)) {
                auto diffy = manhatten - abs(i - r.y1);
                excludeY.push_back({max(r.x1 - diffy, 0), min(r.x1 + diffy, inputY)});
            }

            if (manhatten >= abs(i - r.x1)) {
                auto diffx = manhatten - abs(i - r.x1);
                excludeX.push_back({max(r.y1 - diffx, 0), min(r.y1 + diffx, inputY)});
            }
        }
        y = max(y, find_non_excluded(excludeX));
        x = max(x, find_non_excluded(excludeY));
    }
    uint64_t counter = x * 4000000 + y;
    cout << endl << "solution= " << counter << endl;
}