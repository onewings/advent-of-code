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
#include <numeric>

using namespace std;

struct Monkey {
    std::deque<uint64_t> items;
    std::string operation;
    uint64_t test_divisible{1};
    std::array<int, 2> conditions;    //so I can do conditions[true] and conditions[false]
    uint64_t num_inspects{0};
    static uint64_t common_divisor;

    uint64_t Calculate(uint64_t worry_level)
    {
        uint64_t ret = 1;
        if (operation.find("old * old") not_eq string::npos) {
            ret = worry_level * worry_level;
        } else if (operation.find("old +") not_eq string::npos) {
            ret = worry_level + std::stoll(operation.substr(6));
        } else if (operation.find("old *") not_eq string::npos) {
            ret = worry_level * std::stoll(operation.substr(6));
        }
        return ret % common_divisor;
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

uint64_t Monkey::common_divisor = 1;
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
        if (line.rfind("  Starting", 0) == 0) {
            char delim = ',';
            auto start = 17;
            auto end = line.find(delim);
            while (end not_eq std::string::npos) {
                uint64_t temp = std::stoll(line.substr(start, end - start));
                m.items.push_back(temp);
                start = end + 1;
                end = line.find(delim, start);
            }
            uint64_t temp = std::stoll(line.substr(start));
            m.items.push_back(temp);
        } else if (line.rfind("  Operation", 0) == 0) {
            m.operation = line.substr(19);

        } else if (line.rfind("  Test", 0) == 0) {
            m.test_divisible = stoll(line.substr(21));
            Monkey::common_divisor = std::lcm(Monkey::common_divisor, m.test_divisible);

        } else if (line.rfind("    If true", 0) == 0) {
            m.conditions[1] = stoll(line.substr(28));

        } else if (line.rfind("    If false", 0) == 0) {
            m.conditions[0] = stoll(line.substr(29));
            monkeys.push_back(m);
            cout << m << endl;
            m = Monkey();
        }
    }

    int m_round = monkeys.size();
    for (int i = 0; i < 10000 * m_round; ++i) {
        auto &m = monkeys[i % m_round];
        while (m.items.size()) {
            m.num_inspects++;
            auto temp = m.Calculate(m.items.front());

            int throw_to_monkey = (m.conditions[m.TestDivisible(temp)]);
            monkeys[throw_to_monkey].items.push_back(temp);
            m.items.pop_front();
        }
    }

    cout << "----Print-----" << endl;

    for (const auto &m : monkeys) {
        cout << m << endl;
    }
    cout << "--------------" << endl;

    uint64_t max1 = 0;
    uint64_t max2 = 0;

    auto comparator = [](const Monkey &a, const Monkey &b) { return a.num_inspects < b.num_inspects; };

    auto it1 = std::max_element(monkeys.begin(), monkeys.end(), comparator);
    max1 = it1->num_inspects;
    it1->num_inspects = 0;

    auto it2 = std::max_element(monkeys.begin(), monkeys.end(), comparator);
    max2 = it2->num_inspects;

    cout << "solution " << max1 << " * " << max2 << " = " << max1 * max2 << endl;
}
