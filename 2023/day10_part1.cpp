//----------------------------------------
// --- Day 10 part 1
// https://adventofcode.com/2023/day/10
//----------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <array>

using namespace std;
using MAP = vector<string>;

int main()
{
    std::ifstream ifs;
    ifs.open("day10.in");
    if (not ifs) {
        ifs.open("../day10.in");
    }

    MAP gmap;
    std::string line;
    pair<int, int> pos_s;
    int i = 0;
    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        }
        for (int j = 0; j < line.length(); ++j) {
            if (line[j] == 'S') {
                pos_s = {i, j};
            }
        }

        gmap.push_back(line);
        i++;
    }
    for (auto x : gmap) {
        cout << x << endl;
    }

    int X = pos_s.first;
    int Y = pos_s.second;
    gmap[X][Y] = '|';

    int start = 0;
    int count = 0;
    char dir = 'N';    //S,W,E,N
    while (start not_eq 2) {
        ++count;
        if (X == pos_s.first and Y == pos_s.second) {
            ++start;
        }
        char C = gmap[X][Y];
        cout << count << " [" << X << "," << Y << "] " << C << " dir=" << dir << endl;
        if (dir == 'S') {
            if (C == '|') {
                --X;
                continue;
            } else if (C == '7') {
                dir = 'E';
                --Y;
                continue;
            } else if (C == 'F') {
                dir = 'W';
                ++Y;
                continue;
            }
        }

        if (dir == 'N') {
            if (C == '|') {
                ++X;
                continue;
            } else if (C == 'L') {
                dir = 'W';
                ++Y;
                continue;
            } else if (C == 'J') {
                dir = 'E';
                --Y;
                continue;
            }
        }

        if (dir == 'W') {
            if (C == '-') {
                ++Y;
                continue;
            } else if (C == '7') {
                dir = 'N';
                ++X;
                continue;
            } else if (C == 'J') {
                dir = 'S';
                --X;
                continue;
            }
        }

        if (dir == 'E') {
            if (C == '-') {
                --Y;
                continue;
            } else if (C == 'F') {
                dir = 'N';
                ++X;
                continue;
            } else if (C == 'L') {
                dir = 'S';
                --X;
                continue;
            }
        }
        cout << "error [" << X << "," << Y << "] " << C << " count=" << count << endl;
        break;
    }
    cout << "res= " << (count - 1) / 2;
}