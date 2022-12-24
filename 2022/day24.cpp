//-------------------------------------
//--- Day 24: Blizzard Basin ---
//https://adventofcode.com/2022/day/24
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

int64_t RealMod(int64_t A, int64_t B)
{
    auto temp = A % B;
    if (temp < 0) {
        temp += B;
    }
    return temp;
}

int main()
{
    ifstream ifs;
    ifs.open("day24.in");
    if (not ifs) {
        ifs.open("../day24.in");
    }

    string line;
    vector<pair<int, int>> W;
    vector<tuple<int, int, int, int>> B;
    int y = 0;
    while (getline(ifs, line)) {
        for (int x = 0; x < line.size(); ++x) {
            char c = line[x];
            if (c == '#') {
                W.push_back({x - 1, y - 1});
            }
            if (c == '>') {
                B.push_back({x - 1, y - 1, +1, 0});
            }
            if (c == '<') {
                B.push_back({x - 1, y - 1, -1, 0});
            }
            if (c == '^') {
                B.push_back({x - 1, y - 1, 0, -1});
            }
            if (c == 'v') {
                B.push_back({x - 1, y - 1, 0, +1});
            }
        }
        //cout << line << endl;
        ++y;
    }

    int X = 0, Y = 0;
    for (const auto &[x1, y1] : W) {
        X = max(X, x1);
        Y = max(Y, y1);
    }

    std::cout << "maze size: " << X << "x" << Y << ", " << W.size() << " walls, " << B.size() << " blizzards"
              << std::endl;

    //add some walls on the top, otherwise the player escapes the maze
    for (int i = -1; i < 3; ++i) {
        W.push_back({i, -2});
    }
    sort(W.begin(), W.end());
    pair<int, int> start{0, -1};
    pair<int, int> exit{X - 1, Y};

    uint64_t t = 0;
    set<pair<int, int>> q = {start};
    deque<pair<int, int>> goals = {exit, start, exit};
    while (not goals.empty()) {
        ++t;
        set<pair<int, int>> b, n, diff1, diff2;
        for (const auto &[px, py, dx, dy] : B) {
            b.insert({RealMod((px + t * dx), X), RealMod((py + t * dy), Y)});
        }
        set<pair<int, int>> d{{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {0, 0}};
        for (const auto &[px, py] : q) {
            for (const auto &[dx, dy] : d) {
                n.insert({px + dx, py + dy});
            }
        }

        set_difference(n.begin(), n.end(), b.begin(), b.end(), inserter(diff1, diff1.begin()));
        set_difference(diff1.begin(), diff1.end(), W.begin(), W.end(), inserter(diff2, diff2.begin()));
        q = diff2;
        //cout << t << " q:" << q.size() << " g:(" << goals.front().first << "," << goals.front().second
        //     << ") n:" << n.size();
        //cout << " b:" << b.size() << " W:" << W.size() << " B:" << B.size() << endl;
        if (find(q.begin(), q.end(), goals.front()) not_eq q.end()) {
            cout << "goal " << goals.front().first << "," << goals.front().second << " reached after " << t << " steps "
                 << endl;
            q = {goals.front()};
            goals.pop_front();
        }
    }
}