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

int readNumber(const std::vector<std::string> &matrix, int x, int y)
{
    unsigned max_col = matrix[0].length();

    int index{y};
    int number{0};

    while ((index - 1) >= 0 and std::isdigit(matrix[x][index - 1])) {
        --index;
    }

    while (std::isdigit(matrix[x][index])) {
        char c = matrix[x][index];
        number = number * 10 + (c - 48);
        ++index;
    }
    return number;
}

std::optional<int> checkNumberAround(const std::vector<std::string> &matrix, int x, int y)
{
    unsigned max_row = matrix.size();
    unsigned max_col = matrix[0].length();

    int first_number = 0;

    for (int x1 = x - 1; x1 <= x + 1; ++x1) {
        if (x1 < 0 or x1 > max_row - 1) {
            continue;
        }
        for (int y1 = y - 1; y1 <= y + 1; ++y1) {
            if (y1 < 0 or y1 > max_col - 1) {
                continue;
            }

            if (char c = matrix[x1][y1]; std::isdigit(c)) {
                int number = readNumber(matrix, x1, y1);

                //it will not work in case we have the same number two times
                if ((first_number not_eq 0) and (first_number not_eq number)) {
                    return first_number * number;
                }
                first_number = number;
            }
        }
    }
    return std::nullopt;
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
        for (unsigned j = 0; j < matrix[i].length(); ++j) {
            char c = matrix[i][j];
            if (c == '*') {
                if (auto res = checkNumberAround(matrix, i, j); res) {
                    sum += *res;
                }
            }
        }
    }

    std::cout << "result = " << sum << endl;
    return 0;
}