//-------------------------------------
//--- Day 17: : Pyroclastic Flow ---
//https://adventofcode.com/2022/day/17
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

using namespace std;

vector<vector<int>> GetPosns(int h, const string &name)
{
    vector<vector<int>> ret;
    if (name == "hline")
        return {{h + 3, 2}, {h + 3, 3}, {h + 3, 4}, {h + 3, 5}};
    if (name == "cross")
        return {{h + 3, 3}, {h + 4, 2}, {h + 4, 3}, {h + 4, 4}, {h + 5, 3}};
    if (name == "L")
        return {{h + 3, 2}, {h + 3, 3}, {h + 3, 4}, {h + 4, 4}, {h + 5, 4}};
    if (name == "vline")
        return {{h + 3, 2}, {h + 4, 2}, {h + 5, 2}, {h + 6, 2}};
    //if (name == "square")
    return {{h + 3, 2}, {h + 3, 3}, {h + 4, 2}, {h + 4, 3}};
}

vector<vector<int>> AttemptMove(char move, const vector<vector<int>> &rock_posns, const vector<vector<int>> &situation)
{
    vector<vector<int>> ret;
    for (auto &p : rock_posns) {
        if (move == '<') {
            if (p[1] == 0 or situation[p[0]][p[1] - 1] != 0) {
                return rock_posns;
            } else {
                ret.push_back({p[0], p[1] - 1});
            }
        } else if (move == '>') {
            if (p[1] == 6 or situation[p[0]][p[1] + 1] != 0) {
                return rock_posns;
            } else {
                ret.push_back({p[0], p[1] + 1});
            }
        }
    }
    return ret;
}

pair<vector<vector<int>>, bool> FallRock(const vector<vector<int>> &rock_posns, const vector<vector<int>> &situation)
{
    vector<vector<int>> ret;
    for (auto &el : rock_posns) {
        if (el[0] == 0 or situation[el[0] - 1][el[1]] not_eq 0) {
            return {{}, false};
        } else {
            ret.push_back({el[0] - 1, el[1]});
        }
    }
    return {ret, true};
}

int Calculate(const string &line)
{
    vector<vector<int>> situation(4, vector<int>(7, 0));
    auto curr_highest = -1;
    vector<string> rocknames = {"hline", "cross", "L", "vline", "square"};
    map<string, int> rock_width = {{"hline", 4}, {"cross", 3}, {"L", 3}, {"vline", 1}, {"square", 2}};
    map<string, int> rock_height = {{"hline", 1}, {"cross", 3}, {"L", 3}, {"vline", 4}, {"square", 2}};

    auto move_idx = 0;
    for (int num = 0; num < 2022; ++num) {
        auto curr_rock = rocknames[num % 5];
        auto curr_posns = GetPosns(curr_highest + 1, curr_rock);
        for (int i = 0; i < rock_height[curr_rock]; ++i) {
            situation.push_back(vector<int>(7, 0));
        }

        while (true) {
            if (move_idx >= line.length()) {
                move_idx -= line.length();
            }

            curr_posns = AttemptMove(line[move_idx], curr_posns, situation);
            ++move_idx;

            auto [fall_down, can_fall] = FallRock(curr_posns, situation);

            if (not can_fall) {
                for (auto &el : curr_posns) {
                    situation[el[0]][el[1]] = 1;
                    if (el[0] > curr_highest) {
                        curr_highest = el[0];
                    }
                }
                break;
            }
            curr_posns = fall_down;
        }
    }
    return curr_highest + 1;
}

int main()
{
    ifstream ifs;
    ifs.open("day17.in");
    if (not ifs) {
        ifs.open("../day17.in");
    }

    string line;
    if (getline(ifs, line)) {
        auto solution = Calculate(line);
        int counter = 0;

        cout << "solution= " << solution << endl;
    } else {
        cout << "error while opening day17.in" << endl;
        return -1;
    }
}