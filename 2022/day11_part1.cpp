//--------------------------------------
//  --- Day 11: Monkey in the Middle ---
// https://adventofcode.com/2022/day/11
//--------------------------------------

#include <iostream>
#include <sstream>
#include <string_view>
#include <stdlib.h> /* abs */
#include <cstring>
#include <array>
#include <algorithm>
#include <stack>
#include <vector>
#include <fstream>
#include <utility>
#include <set>

using namespace std;

struct Monkey {
    std::deque<int> items;
    std::string operation;
    int test_divisible{1};
    std::array<int, 2> conditions;
    int num_inspects{0};

    int Calculate(int worry_level)
    {
        int ret = 1;
        if (operation.find("old * old") not_eq string::npos) {
            ret = worry_level * worry_level;
        } else if (operation.find("old +") not_eq string::npos) {
            ret = worry_level + std::stoi(operation.substr(6));
        } else if (operation.find("old *") not_eq string::npos) {
            ret = worry_level * std::stoi(operation.substr(6));
        }
        return ret / 3;
    }

    bool TestDivisible(int number)
    {
        return number % test_divisible == 0;
    }

    friend std::ostream &operator<<(std::ostream &os, const Monkey &m)
    {
        // clang-format off
        os << "{"; 
        for (auto &item:m.items)
        {
            os <<item<<" ";
        }
        os << "} (" << m.operation << ")"
            << " [" << m.test_divisible << "] "
            << m.conditions[true] << " "
            << m.conditions[false]<< " inspects "<<m.num_inspects;
        // clang-format on
        return os;
    }
};

int main()
{
    std::ifstream ifs;
    ifs.open("day11.in");
    if (not ifs) {
        ifs.open("../day11.in");
    }

    int res = 0;
    std::string line;
    std::vector<Monkey> monkeys;

    cout << "----Read File-----" << endl;
    Monkey m;
    while (std::getline(ifs, line)) {
        if (line.rfind("  Starting", 0) == 0) {    //start_with in c++20
            char delim = ',';
            auto start = 17;
            auto end = line.find(delim);
            while (end not_eq std::string::npos) {
                int temp = std::stoi(line.substr(start, end - start));
                m.items.push_back(temp);
                start = end + 1;
                end = line.find(delim, start);
            }
            int temp = std::stoi(line.substr(start));
            m.items.push_back(temp);
        } else if (line.rfind("  Operation", 0) == 0) {
            m.operation = line.substr(19);

        } else if (line.rfind("  Test", 0) == 0) {
            m.test_divisible = stoi(line.substr(21));

        } else if (line.rfind("    If true", 0) == 0) {
            m.conditions[1] = stoi(line.substr(28));

        } else if (line.rfind("    If false", 0) == 0) {
            m.conditions[0] = stoi(line.substr(29));
            monkeys.push_back(m);
            cout << m << endl;
            m = Monkey();
        }
    }

    int m_round = monkeys.size();
    for (int i = 0; i < 20 * m_round; ++i) {
        auto &m = monkeys[i % m_round];
        while (m.items.size()) {
            //cout << "monkey " << i % m_round << " ((" << m << "))";
            m.num_inspects++;
            auto temp = m.Calculate(m.items.front());
            //cout << " calc= " << temp << "  TestDivisible= " << m.TestDivisible(temp);

            int throw_to_monkey = (m.conditions[m.TestDivisible(temp)]);
            monkeys[throw_to_monkey].items.push_back(temp);
            m.items.pop_front();
            //cout << "  throw_to_monkey [" << throw_to_monkey << "] " << monkeys[throw_to_monkey];
            //cout << endl;
        }
    }

    cout << "----Print-----" << endl;

    for (const auto &m : monkeys) {
        cout << m << endl;
    }
    cout << "--------------" << endl;

    int max1 = 0;
    int max2 = 0;

    auto comparator = [](const Monkey &a, const Monkey &b) { return a.num_inspects < b.num_inspects; };

    auto it1 = std::max_element(monkeys.begin(), monkeys.end(), comparator);
    max1 = it1->num_inspects;
    it1->num_inspects = 0;
    auto it2 = std::max_element(monkeys.begin(), monkeys.end(), comparator);
    max2 = it2->num_inspects;

    cout << "solution = " << max1 * max2 << endl;
}
