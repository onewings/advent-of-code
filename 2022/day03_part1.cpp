//----------------------------------------
// --- Day 3: Rucksack Reorganization ---
// https://adventofcode.com/2022/day/3
//----------------------------------------

#include <iostream>
#include <fstream>
#include <string_view>
#include <cstring>

using namespace std;

char Calculate(const std::string_view &a, const std::string_view &b)
{
    for (char x : a) {
        for (char y : b) {
            if (x == y) {
                return x;
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

    std::string line;
    unsigned total = 0;

    while (std::getline(ifs, line)) {
        auto size = line.size();
        int middle = size / 2;
        std::string_view a(line.c_str(), middle);
        std::string_view b(line.c_str() + middle, middle);

        char letter = Calculate(a, b);

        if (isupper(letter)) {
            //std::cout << a << "     " << b << " letter " << letter << " " << int(letter) << " " << int(letter) - 65 + 27 << endl;
            total += int(letter) - 65 + 27;
        } else {
            //std::cout << a << "     " << b << " letter " << letter << " " << int(letter) << " " << int(letter) - 96 << endl;
            total += int(letter) - 96;
        }
    }
    std::cout << total << endl;
    return 0;
}
