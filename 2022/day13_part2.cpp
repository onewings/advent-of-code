//------------------------------------
//  --- Day 13: Distress Signal ---
//https://adventofcode.com/2022/day/13
//------------------------------------

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

int main()
{
    std::ifstream ifs;
    ifs.open("day13.in");
    if (not ifs) {
        ifs.open("../day13.in");
    }

    int res = 0;
    std::string line;
    std::vector<std::string> map;

    while (std::getline(ifs, line)) {
        map.push_back(line);
    }

    cout << "solution= " << res << endl;
}
