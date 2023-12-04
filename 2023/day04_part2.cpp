//----------------------------------------
// --- Day 4: Scratchcards ---
// https://adventofcode.com/2023/day/4
//----------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int checkCard(const std::unordered_set<int> &winning_numbers, const std::vector<int> &card_number)
{
    int point = 0;
    for (int number : card_number) {
        if (auto iter = winning_numbers.find(number); iter != winning_numbers.end()) {
            ++point;
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
    std::unordered_map<int, int> matrix;

    while (std::getline(ifs, line)) {
        std::unordered_set<int> winning_numbers;
        std::vector<int> card_numbers;
        int id = 0;
        char buf[1024];
        sscanf(line.c_str(), "Card %d: %[^\t\n]", &id, &buf);
        //cout << "game " << id << " ";
        matrix[id]++;    //put the original here

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
                    winning_numbers.insert(found);
                }
                temp = "";
            }
        }

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
        //cout << "my count=" << matrix[id] << " res= " << res << endl;
        for (int i = 0; i < matrix[id] and res > 0; ++i) {
            for (int j = 1; j <= res; ++j) {
                matrix[id + j]++;
            }
        }
    }

    for (const auto &[key, value] : matrix) {
        //cout << key << "=" << value << endl;
        sum += value;
    }

    std::cout << "result = " << sum << endl;
    return 0;
}