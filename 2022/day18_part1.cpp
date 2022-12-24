//-------------------------------------
//--- Day 18: Boiling Boulders ---
//https://adventofcode.com/2022/day/18
//-------------------------------------

#include <iostream>
#include <stdlib.h> /* abs */
#include <cstring>
#include <algorithm>
#include <vector>
#include <fstream>
#include <utility>
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

bool CheckOutside(Element inElement, const CubeMap &cubeMap, CubeMap &outMap)
{
    if (std::find(outMap.begin(), outMap.end(), inElement) not_eq outMap.end()) {
        return true;
    }

    if (std::find(cubeMap.begin(), cubeMap.end(), inElement) not_eq cubeMap.end()) {
        return false;
    }
    return true;
}

int Calculate(const CubeMap &cubeMap)
{
    int ret = 0;
    CubeMap outMap;
    for (const auto &[x, y, z] : cubeMap) {
        if (CheckOutside({x + 1, y, z}, cubeMap, outMap)) {
            ++ret;
        }
        if (CheckOutside({x - 1, y, z}, cubeMap, outMap)) {
            ++ret;
        }
        if (CheckOutside({x, y + 1, z}, cubeMap, outMap)) {
            ++ret;
        }
        if (CheckOutside({x, y - 1, z}, cubeMap, outMap)) {
            ++ret;
        }
        if (CheckOutside({x, y, z + 1}, cubeMap, outMap)) {
            ++ret;
        }
        if (CheckOutside({x, y, z - 1}, cubeMap, outMap)) {
            ++ret;
        }
        std::sort(outMap.begin(), outMap.end());
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