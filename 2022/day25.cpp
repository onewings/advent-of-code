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
#include <map>

using namespace std;

map<char, int> PLACES = {{'2', 2}, {'1', 1}, {'0', 0}, {'-', -1}, {'=', -2}};
int64_t SnafuToDecimal(string_view line)
{
    if (line.empty()) {
        return 0;
    }
    return 5 * SnafuToDecimal(string_view(line.data(), line.size() - 1)) + PLACES[*line.rbegin()];
}

string DecimalToSnafu(int64_t decimal)
{
    if (decimal <= 0) {
        return "";
    }
    string token{"=-012"};
    int64_t a = (decimal + 2) / 5;
    int b = (decimal + 2) % 5;
    return DecimalToSnafu(a) + token[b];
}
int main()
{
    ifstream ifs;
    ifs.open("day25.in");
    if (not ifs) {
        ifs.open("../day25.in");
    }

    string line;
    int64_t count;
    while (getline(ifs, line)) {
        count += SnafuToDecimal(line);
    }

    cout << "solution in decimal = " << count << endl;
    cout << "solution in snafu = " << DecimalToSnafu(count) << endl;
}