//------------------------------------
//--- Day 14: Regolith Reservoir ---
//https://adventofcode.com/2022/day/14
//------------------------------------

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

void InitializePos(int &posx, int &posy)
{
    posx = 500;
    posy = 0;
}

const int max_x = 1000;
const int max_y = 174;

using Map = array<array<char, max_x>, max_y>;

int Draw(const string &src, const string &dest, Map &map)
{
    int x1 = stoi(src);
    int y1 = stoi(src.substr(src.find(',') + 1));
    int x2 = stoi(dest);
    int y2 = stoi(dest.substr(dest.find(',') + 1));

    if (y1 == y2) {
        int distance = (x1 >= x2) ? (x1 - x2) : (x2 - x1);
        for (int i = 0; i <= distance; ++i) {
            if (x1 >= x2) {
                map[y1][x1 - i] = '#';
            } else {
                map[y1][x1 + i] = '#';
            }
        }
    }

    if (x1 == x2) {
        int distance = (y1 >= y2) ? (y1 - y2) : (y2 - y1);
        for (int i = 0; i <= distance; ++i) {
            if (y1 >= y2) {
                map[y1 - i][x1] = '#';
            } else {
                map[y1 + i][x1] = '#';
            }
        }
    }
    return max(y1, y2);
}

int main()
{
    ifstream ifs;
    ifs.open("day14.in");
    if (not ifs) {
        ifs.open("../day14.in");
    }

    array<array<char, max_x>, max_y> map;
    for (auto &arr : map) {
        arr.fill('.');
    }

    int lowest = 0;

    auto ReadFromInput = [&]() {
        string line;
        while (getline(ifs, line)) {
            char *p = strtok(line.data(), "->");
            string previous = p;
            while (p) {
                p = strtok(NULL, "->");
                if (p) {
                    lowest = max(lowest, Draw(previous, p, map));
                    previous = p;
                }
            }
        }
    };
    ReadFromInput();

    lowest = lowest + 2;
    //insert a horizontal line
    for (int i = 0; i < max_x; ++i) {
        map[lowest][i] = '#';
    }

    int counter = 0;
    bool shoulRun = true;
    int posx = 500, posy = 0;

    while (shoulRun) {
        if (map[0][500] == 'O') {
            shoulRun = false;
            break;
        }

        //check bottom boundary
        if (posy + 1 >= max_y) {
            shoulRun = false;
            break;
        }

        if (map[posy + 1][posx] == '.') {
            posy++;
            continue;
        }

        //try_left
        //check border
        if (posx - 1 < 0) {
            shoulRun = false;
            break;
        }

        if (map[posy + 1][posx - 1] == '.') {
            posx--;
            posy++;
            continue;
        }

        //try_right
        //check border
        if (posx + 1 >= max_x) {
            shoulRun = false;
            break;
        }

        if (map[posy + 1][posx + 1] == '.') {
            posx++;
            posy++;
            continue;
        }

        //no move
        map[posy][posx] = 'O';
        counter++;
        InitializePos(posx, posy);
    }

    cout << "-----------" << endl;
    map[0][500] = 'A';    //the top
    for (int i = 0; i < max_y; ++i) {
        for (int j = 445; j <= 560; ++j) {
            cout << map[i][j];
        }
        cout << endl;
    }

    cout << "lowest= " << lowest << endl;
    cout << "solution= " << counter << endl;
}