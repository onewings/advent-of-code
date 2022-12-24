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
#include <unordered_map>

using namespace std;

vector<vector<int64_t>> GetPosns(int64_t h, const string &name)
{
    vector<vector<int64_t>> ret;
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

vector<vector<int64_t>> AttemptMove(char move, const vector<vector<int64_t>> &rock_posns,
                                    const vector<vector<int64_t>> &situation)
{
    vector<vector<int64_t>> ret;
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

pair<vector<vector<int64_t>>, bool> FallRock(const vector<vector<int64_t>> &rock_posns,
                                             const vector<vector<int64_t>> &situation)
{
    vector<vector<int64_t>> ret;
    for (auto &el : rock_posns) {
        if (el[0] == 0 or situation[el[0] - 1][el[1]] not_eq 0) {
            return {{}, false};
        } else {
            ret.push_back({el[0] - 1, el[1]});
        }
    }
    return {ret, true};
}

class Element
{
public:
    Element() : m_vect(vector<int64_t>(7, 0)) {}
    Element(const vector<int64_t> &vect, int64_t idx, int64_t num) : m_vect(vect), m_idx(idx), m_num(num) {}

    bool operator==(const Element &p) const
    {
        for (int i = 0; i < p.m_vect.size(); ++i) {
            if (m_vect[i] not_eq p.m_vect[i]) {
                return false;
            }
        }
        return m_idx == p.m_idx && m_num == p.m_num;
    }

    vector<int64_t> m_vect;
    int64_t m_idx{0};
    int64_t m_num{0};
};

class MyHashFunction
{
public:
    size_t operator()(const Element &p) const
    {
        return p.m_idx + 13 + p.m_num * 17 + p.m_vect[0] * 19 + p.m_vect[1] * 23 + p.m_vect[2] * 29 + p.m_vect[3] * 31
               + p.m_vect[4] * 37 + p.m_vect[5] * 41 + p.m_vect[6] * 53;
    }
};

int64_t Calculate(const string &line)
{
    vector<vector<int64_t>> situation(4, vector<int64_t>(7, 0));
    auto curr_highest = -1;
    vector<string> rocknames = {"hline", "cross", "L", "vline", "square"};
    map<string, int64_t> rock_width = {{"hline", 4}, {"cross", 3}, {"L", 3}, {"vline", 1}, {"square", 2}};
    map<string, int64_t> rock_height = {{"hline", 1}, {"cross", 3}, {"L", 3}, {"vline", 4}, {"square", 2}};

    int64_t move_idx = 0;
    vector<int64_t> seven_peaks(7, 0);
    unordered_map<Element, int64_t, MyHashFunction> prev_seen;
    map<int64_t, int64_t> h_dict;
    for (int64_t num = 0; num < 1000000000000; ++num) {
        auto curr_rock = rocknames[num % 5];
        auto curr_posns = GetPosns(curr_highest + 1, curr_rock);
        for (int64_t i = 0; i < rock_height[curr_rock]; ++i) {
            situation.push_back(vector<int64_t>(7, 0));
        }

        while (true) {
            if (move_idx >= line.length()) {
                move_idx -= line.length();
            }
            curr_posns = AttemptMove(line[move_idx], curr_posns, situation);
            ++move_idx;

            auto [fall_down, can_fall] = FallRock(curr_posns, situation);

            if (not can_fall) {
                auto old_max = curr_highest;

                for (auto &el : curr_posns) {
                    situation[el[0]][el[1]] = 1;
                    if (el[0] > curr_highest) {
                        curr_highest = el[0];
                    }
                }
                auto max_change = curr_highest - old_max;

                for (int64_t i = 0; i < 7; ++i) {
                    seven_peaks[i] -= max_change;
                }
                for (auto &el : curr_posns) {
                    auto this_peak = el[0] - curr_highest;
                    seven_peaks[el[1]] = max(seven_peaks[el[1]], this_peak);
                }

                break;
            }
            curr_posns = fall_down;
        }
        h_dict[num] = curr_highest;
        Element k(seven_peaks, move_idx, num % 5);
        if (prev_seen.find(k) not_eq prev_seen.end()) {
            if (prev_seen[k] not_eq 0) {
                auto then_count = prev_seen[k];
                auto highest_then = h_dict[prev_seen[k]];
                auto highest_now = curr_highest;
                auto height_change = highest_now - highest_then;
                auto cycle_size = num - prev_seen[k];
                auto goal = 1000000000000;
                goal -= prev_seen[k];
                auto num_cycles = goal / cycle_size;
                auto left_over = goal % cycle_size;
                auto leftover_height = h_dict[then_count + left_over] - highest_then;
                return highest_then + leftover_height + (num_cycles * height_change);
            }
        }
        prev_seen[k] = num;
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
        cout << "solution= " << solution << endl;
    } else {
        cout << "error while opening day17.in" << endl;
        return -1;
    }
}