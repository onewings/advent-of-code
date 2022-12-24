//----------------------------------------
// --- Day 3: Rucksack Reorganization ---
// https://adventofcode.com/2022/day/3
//----------------------------------------

#include <iostream>
#include <fstream>
#include <string_view>
#include <cstring>
using namespace std;

char Calculate(const std::string &a, const std::string &b, const std::string &c)
{
    for (char x : a) {
        for (char y : b) {
            if (x == y) {
                for (char z : c) {
                    if (x == z) {
                        return x;
                    }
                }
            }
        }
    }

    std::cout << "error" << std::endl;
    return 'x';
}
int main()
{
    std::ifstream ifs;
    ifs.open("day03.in");
    if (not ifs) {
        ifs.open("../day03.in");
    }

    std::string line1;
    std::string line2;
    std::string line3;
    unsigned total = 0;

    while (true) {
        if (not std::getline(ifs, line1)) {
            break;
        }
        if (not std::getline(ifs, line2)) {
            break;
        }
        if (not std::getline(ifs, line3)) {
            break;
        }

        char letter = Calculate(line1, line2, line3);
        if (isupper(letter)) {
            //std::cout << " letter " << letter << " " << int(letter) << " " << int(letter) - 65 + 27 << endl;
            total += int(letter) - 65 + 27;
        } else {
            //std::cout << " letter " << letter << " " << int(letter) << " " << int(letter) - 96 << endl;
            total += int(letter) - 96;
        }
    }
    std::cout << total << endl;
    return 0;
}
