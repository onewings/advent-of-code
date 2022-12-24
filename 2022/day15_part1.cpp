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

struct item {
    int x1;
    int x2;
};

int main()
{
    ifstream ifs;
    ifs.open("day15.in");
    if (not ifs) {
        ifs.open("../day15.in");
    }

    string line;
    vector<item> ranges;

    const int inputY = 2000000;
    while (getline(ifs, line)) {
        int x1, y1, x2, y2;
        sscanf(line.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &x1, &y1, &x2, &y2);
        int manhatten = abs(x1 - x2) + abs(y1 - y2);
        auto temp = manhatten - abs(y1 - inputY);

        if (temp > 0) {
            ranges.push_back({x1 - temp, x1 + temp});
        }
    }

    int counter = 0;

    sort(ranges.begin(), ranges.end(), [](const auto &left, const auto &right) { return left.x1 < right.x1; });

    vector<item> mergedRanges;
    mergedRanges.push_back(ranges[0]);
    auto it = ranges.begin();

    while (++it not_eq ranges.end()) {
        if (it->x1 <= mergedRanges.back().x2) {
            mergedRanges.back().x2 = max(it->x2, mergedRanges.back().x2);
        } else {
            mergedRanges.push_back(*it);
        }
    }
    //print all ranges
    for (const auto &range : mergedRanges) {
        cout << "(" << range.x1 << "," << range.x2 << ")";
        counter += abs(range.x2 - range.x1);
    }

    cout << endl << "solution= " << counter << endl;
}