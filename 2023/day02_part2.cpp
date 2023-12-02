//----------------------------------------
// --- Day 2: Cube Conundrum ---
// https://adventofcode.com/2023/day/2
//----------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

using namespace std;

void checkString(const std::string &s, int &red, int &green, int &blue)
{
    std::smatch m;

    if (std::regex_search(s, m, std::regex("[0-9]* red"))) {
        if (int temp = stoi(m[0]); temp > red) {
            red = temp;
        }
    }

    if (std::regex_search(s, m, std::regex("[0-9]* green"))) {
        if (int temp = stoi(m[0]); temp > green) {
            green = temp;
        }
    }

    if (std::regex_search(s, m, std::regex("[0-9]* blue"))) {
        if (int temp = stoi(m[0]); temp > blue) {
            blue = temp;
        }
    }
}

int main()
{
    std::ifstream ifs;
    ifs.open("day02.in");
    if (not ifs) {
        ifs.open("../day02.in");
    }

    std::string s;
    unsigned sum = 0;
    while (std::getline(ifs, s)) {
        std::string delimiter = "; ";

        size_t pos = 0;
        std::string token;

        int red = 0;
        int green = 0;
        int blue = 0;
        while (((pos = s.find(delimiter)) != std::string::npos)) {
            token = s.substr(0, pos);
            checkString(token, red, green, blue);
            s.erase(0, pos + delimiter.length());
        }
        checkString(s, red, green, blue);
        sum += red * green * blue;
    }
    std::cout << sum << endl;
    return 0;
}