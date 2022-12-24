//-------------------------------------
// --- Day 21: Monkey Math ---
//https://adventofcode.com/2022/day/21
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
#include <map>
#include <limits>
#include <cmath>

using namespace std;

static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

static inline std::string trim_copy(std::string s)
{
    rtrim(s);
    ltrim(s);
    return s;
}

using Data = map<string, vector<string> >;
double Calc(const string &name, int64_t h, Data &E)
{
    if (name == "humn" and h >= 0) {
        return h;
    }

    auto words = E[name];

    if (words.size() == 3) {
        auto e1 = Calc(words[0], h, E);
        auto e2 = Calc(words[2], h, E);
        if (words[1] == "+") {
            return e1 + e2;
        }
        if (words[1] == "*") {
            return e1 * e2;
        }
        if (words[1] == "-") {
            return e1 - e2;
        }
        if (words[1] == "/") {
            return e1 / e2;
        }
    } else {
        return stoi(words[0]);
    }
    return 0;
}

int main()
{
    ifstream ifs;
    ifs.open("day21.in");
    if (not ifs) {
        ifs.open("../day21.in");
    }

    string line;
    map<string, vector<string> > E;
    while (getline(ifs, line)) {
        string name = line.substr(0, line.find(":"));
        string expr = line.substr(line.find(":") + 2);
        vector<string> temp;
        char delim = ' ';

        auto start = 0;
        auto end = expr.find(delim);
        while (end not_eq std::string::npos) {
            E[name].push_back(trim_copy(expr.substr(start, end - start)));
            start = end + 1;
            end = expr.find(delim, start);
        }
        E[name].push_back(trim_copy(expr.substr(start)));
    }
    cout.setf(std::ios::fixed);
    cout << (int64_t)Calc("root", -1, E) << endl;

    auto p1 = E["root"][0];
    auto p2 = E["root"][2];

    if (Calc(p2, 0, E) not_eq Calc(p2, 1, E)) {
        swap<string>(p1, p2);
    }

    auto target = Calc(p2, 0, E);

    int64_t lo = 0;
    int64_t hi = 100000000000000;

    while (lo < hi) {
        int64_t mid = floor((lo + hi) / 2);
        auto score = target - Calc(p1, mid, E);
        if (score < 0) {
            lo = mid;
        } else if (score == 0) {
            cout << mid << endl;
            break;
        } else {
            hi = mid;
        }
    }
}