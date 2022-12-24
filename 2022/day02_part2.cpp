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
    if (b == 'X')    //lose
    {
        if (a == 'A') {
            result += 3;
        }
        if (a == 'B') {
            result += 1;
        }
        if (a == 'C') {
            result += 2;
        }
    }
    if (b == 'Y')    //pair
    {
        result = 3;
        if (a == 'A') {
            result += 1;
        }
        if (a == 'B') {
            result += 2;
        }
        if (a == 'C') {
            result += 3;
        }
    }
    if (b == 'Z')    //win
    {
        result = 6;
        if (a == 'A') {
            result += 2;
        }
        if (a == 'B') {
            result += 3;
        }
        if (a == 'C') {
            result += 1;
        }
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