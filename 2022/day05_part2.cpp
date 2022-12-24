//--------------------------------------
// --- Day 5: Supply Stacks ---
// https://adventofcode.com/2022/day/5
//--------------------------------------

#include <iostream>
#include <fstream>
#include <string_view>
#include <cstring>
#include <array>
#include <stack>

using namespace std;

int main()
{
    std::ifstream ifs;
    ifs.open("day05.in");
    if (not ifs) {
        ifs.open("../day05.in");
    }

    std::string line;

    std::array<std::stack<char>, 9> map;

    for (auto x : "PFMQWGRT") {
        map[0].push(x);
    }

    for (auto x : "HFR") {
        map[1].push(x);
    }

    for (auto x : "PZRVGHSD") {
        map[2].push(x);
    }

    for (auto x : "QHPBFWG") {
        map[3].push(x);
    }
    for (auto x : "PSMJH") {
        map[4].push(x);
    }

    for (auto x : "MZTHSRPL") {
        map[5].push(x);
    }

    for (auto x : "PTHNML") {
        map[6].push(x);
    }

    for (auto x : "FDQR") {
        map[7].push(x);
    }

    for (auto x : "DSCNLPH") {
        map[8].push(x);
    }

    for (auto &el : map) {
        el.pop();    //remove \0
    }

    while (std::getline(ifs, line)) {
        int quantity = 0;
        int from = 0;
        int to = 0;
        sscanf(line.c_str(), "move %d from %d to %d", &quantity, &from, &to);

        std::stack<char> temp;
        for (int i = 0; i < quantity; i++) {
            temp.push(map[from - 1].top());
            map[from - 1].pop();
        }
        while (not temp.empty()) {
            map[to - 1].push(temp.top());
            temp.pop();
        }

        //cout << quantity << " " << from << " " << to << endl;
    }

    for (auto &el : map) {
        std::cout << el.top();
    }
    std::cout << std::endl;

    return 0;
}
