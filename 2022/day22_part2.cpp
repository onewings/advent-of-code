//-------------------------------------
// --- Day 22: Monkey Map ---
//https://adventofcode.com/2022/day/22
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
    ifs.open("day22.in");
    if (not ifs) {
        ifs.open("../day22.in");
    }

    string line;

    while (getline(ifs, line)) {

        cout << line << endl;
    }

    int counter = 0;

    cout << endl << "solution= " << counter << endl;
}