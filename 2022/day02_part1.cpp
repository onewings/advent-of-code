//----------------------------------------
// --- Day 2: Rock Paper Scissors ---
// https://adventofcode.com/2022/day/2
//----------------------------------------

#include <iostream>
#include <fstream>

using namespace std;

unsigned Calculate(char a, char b)
{
    unsigned result = 0;
    if (b == 'X') {
        result = 1;
    }
    if (b == 'Y') {
        result = 2;
    }
    if (b == 'Z') {
        result = 3;
    }

    if ((a == 'A' and b == 'X') or (a == 'B' and b == 'Y') or (a == 'C' and b == 'Z')) {
        result += 3;
    } else if ((a == 'A' and b == 'Y') or (a == 'B' and b == 'Z') or (a == 'C' and b == 'X')) {
        result += 6;
    }

    return result;
}
int main()
{
    std::ifstream ifs;
    ifs.open("day02.in");
    if (not ifs) {
        ifs.open("../day02.in");
    }

    std::string line;
    unsigned total = 0;
    while (std::getline(ifs, line)) {
        char a = line[0];
        char b = line[2];
        total += Calculate(a, b);
    }
    std::cout << total << endl;
    return 0;
}