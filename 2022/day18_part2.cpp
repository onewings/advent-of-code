//-------------------------------------
//--- Day 18: Boiling Boulders ---
//https://adventofcode.com/2022/day/18
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
#include <deque>
#include <functional>

using namespace std;
using Element = tuple<int, int, int>;
using CubeMap = vector<Element>;

void ReadInput(CubeMap &cubeMap)
{
    ifstream ifs;
    ifs.open("day18.in");
    if (not ifs) {
        ifs.open("../day18.in");
    }

    int x = 0;
    int y = 0;
    int z = 0;
    string line;
    while (getline(ifs, line)) {
        sscanf(line.c_str(), "%d,%d,%d", &x, &y, &z);
        cubeMap.push_back({x, y, z});
    }
}

bool CheckOutside(Element inElement, const CubeMap &cubeMap, CubeMap &inMap, CubeMap &outMap)
{
    const auto &[x, y, z] = inElement;

    if (std::find(outMap.begin(), outMap.end(), inElement) not_eq outMap.end()) {
        return true;
    }

    if (std::find(inMap.begin(), inMap.end(), inElement) not_eq inMap.end()) {
        return false;
    }

    CubeMap seen;

    deque<Element> Q;
    Q.push_back(inElement);

    while (not Q.empty()) {
        const auto &element = Q.front();
        Q.pop_front();

        if (std::find(cubeMap.begin(), cubeMap.end(), element) not_eq cubeMap.end()) {
            continue;
        }

        if (std::find(seen.begin(), seen.end(), element) not_eq seen.end()) {
            continue;
        }
        seen.push_back(element);

        if (seen.size() > 5000) {
            outMap.insert(outMap.end(), seen.begin(), seen.end());
            return true;
        }

        const auto &[x, y, z] = element;
        Q.emplace_back(x + 1, y, z);
        Q.emplace_back(x - 1, y, z);
        Q.emplace_back(x, y + 1, z);
        Q.emplace_back(x, y - 1, z);
        Q.emplace_back(x, y, z + 1);
        Q.emplace_back(x, y, z - 1);
    }

    inMap.insert(inMap.end(), seen.begin(), seen.end());
    return false;
}

int Calculate(const CubeMap &cubeMap)
{
    int ret = 0;
    CubeMap inMap, outMap;
    int counter = 0;
    for (auto &[x, y, z] : cubeMap) {
        if (CheckOutside({x + 1, y, z}, cubeMap, inMap, outMap)) {
            ++ret;
        }
        if (CheckOutside({x - 1, y, z}, cubeMap, inMap, outMap)) {
            ++ret;
        }
        if (CheckOutside({x, y + 1, z}, cubeMap, inMap, outMap)) {
            ++ret;
        }
        if (CheckOutside({x, y - 1, z}, cubeMap, inMap, outMap)) {
            ++ret;
        }
        if (CheckOutside({x, y, z + 1}, cubeMap, inMap, outMap)) {
            ++ret;
        }
        if (CheckOutside({x, y, z - 1}, cubeMap, inMap, outMap)) {
            ++ret;
        }
    }
    return ret;
}

int main()
{
    ifstream ifs;
    ifs.open("day18.in");
    if (not ifs) {
        ifs.open("../day18.in");
    }

    CubeMap cube_map;
    ReadInput(cube_map);
    int solution = Calculate(cube_map);

    cout << endl << "solution= " << solution << endl;
    return 0;
}