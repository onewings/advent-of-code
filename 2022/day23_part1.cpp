//-------------------------------------
// --- Day 23: Unstable Diffusion ---
//https://adventofcode.com/2022/day/23
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

int main()
{
    ifstream ifs;
    ifs.open("day23.in");
    if (not ifs) {
        ifs.open("../day23.in");
    }

    string line;

    while (getline(ifs, line)) {
        string name = line.substr(0, line.find(":"));
        cout << name << endl;
    }

    int counter = 0;

    cout << endl << "solution= " << counter << endl;
}