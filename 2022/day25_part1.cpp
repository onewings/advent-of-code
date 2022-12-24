//-------------------------------------
//--- Day 25: ************** ---
//https://adventofcode.com/2022/day/25
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
    ifs.open("day25.in");
    if (not ifs) {
        ifs.open("../day25.in");
    }

    string line;

    while (getline(ifs, line)) {

        cout << line << endl;
    }

    int counter = 0;

    cout << endl << "solution= " << counter << endl;
}