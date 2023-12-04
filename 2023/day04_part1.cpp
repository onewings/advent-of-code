//----------------------------------------
// --- Day 4: Scratchcards ---
// https://adventofcode.com/2023/day/4
//----------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int checkCard(const std::unordered_set<int> &winning_numbers, const std::vector<int> &card_number)
{
    int point = 0;
    for (int number : card_number) {
        if (auto iter = winning_numbers.find(number); iter != winning_numbers.end()) {
            if (point == 0) {
                point = 1;
            } else {
                point *= 2;
            }
        }
    }
    return point;
}

int main()
{
    std::ifstream ifs;
    ifs.open("day04.in");
    if (not ifs) {
        ifs.open("../day04.in");
    }

    std::string line;
    unsigned sum = 0;
    std::vector<std::string> matrix;

    while (std::getline(ifs, line)) {
        std::unordered_set<int> winning_numbers;
        std::vector<int> card_numbers;

        std::size_t found_colon = line.find(':');
        std::size_t found_pipe = line.find('|');

        string winning_str = line.substr(found_colon + 1, found_pipe - found_colon - 1);
        string card_Str = line.substr(found_pipe + 1, line.length() - found_pipe - 1);

        // read winning numbers
        {
            stringstream ss;
            ss << winning_str;
            string temp;
            int found;
            while (!ss.eof()) {
                ss >> temp;
                if (stringstream(temp) >> found) {
                    //cout << found << " ";
                    winning_numbers.insert(found);
                }
                temp = "";
            }
        }
        //cout << " | ";

        // read card numbers
        {
            stringstream ss;

            ss << card_Str;
            string temp;
            int found;
            while (!ss.eof()) {
                ss >> temp;
                if (stringstream(temp) >> found) {
                    // cout << found << " ";
                    card_numbers.push_back(found);
                }
                temp = "";
            }
        }

        int res = checkCard(winning_numbers, card_numbers);
        //cout << " = " << res << endl;
        sum += res;
    }

    std::cout << "result = " << sum << endl;
    return 0;
}