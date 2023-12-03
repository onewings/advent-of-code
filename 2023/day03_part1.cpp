//----------------------------------------
// --- Day 3: Gear Ratios ---
// https://adventofcode.com/2023/day/3
//----------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <map>

using namespace std;

/*
    check symbol
    x-1 | y-1, y ,y+1
    x   | y-1,  , y+1
    x+1 | y-1, y ,y+1
*/
bool checkSymbolAround(const std::vector<std::string> &matrix, int x, int y)
{
    unsigned max_row = matrix.size();
    unsigned max_col = matrix[0].length();

    for (int x1 = x - 1; x1 <= x + 1; ++x1) {
        if (x1 < 0 or x1 > max_row - 1) {
            continue;
        }
        for (int y1 = y - 1; y1 <= y + 1; ++y1) {
            if (y1 < 0 or y1 > max_col - 1) {
                continue;
            }
            if (char c = matrix[x1][y1]; not std::isdigit(c) and not(c == '.')) {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    std::ifstream ifs;
    ifs.open("day03.in");
    if (not ifs) {
        ifs.open("../day03.in");
    }

    std::string line;
    unsigned sum = 0;
    std::vector<std::string> matrix;

    while (std::getline(ifs, line)) {
        matrix.push_back(line);
    }

    unsigned max_row = matrix.size();

    for (unsigned i = 0; i < max_row; ++i) {
        bool check = false;
        unsigned temp = 0;
        for (unsigned j = 0; j < matrix[i].length(); ++j) {
            char c = matrix[i][j];

            if (std::isdigit(c)) {
                check = check or checkSymbolAround(matrix, i, j);
                temp = temp * 10 + (c - 48);
            } else {
                //is number ended
                if (temp > 0 and check) {
                    sum += temp;
                }
                temp = 0;
                check = false;
            }
        }

        //check if number ended at the end of line
        if (check and (temp > 0)) {
            sum += temp;
        }
        temp = 0;
        check = false;
    }

    std::cout << "result = " << sum << endl;
    return 0;
}