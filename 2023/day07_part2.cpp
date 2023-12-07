//----------------------------------------
// --- Day 6: Wait For It ---
// https://adventofcode.com/2023/day/6
//----------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <array>

using namespace std;
using hand = std::array<char, 5>;

int getScore(const hand &a)
{
    //cout << a[0] << a[1] << a[2] << a[3] << a[4] << endl;

    std::array<int, 13> v{0};
    for (auto card : a)
        v[card - '1'] += 1;

    for (auto x : v) {
        cout << " " << x;
    }

    const int num_items5 = std::count(v.cbegin(), v.cend(), 5);
    const int num_items4 = std::count(v.cbegin(), v.cend(), 4);
    const int num_items3 = std::count(v.cbegin(), v.cend(), 3);
    const int num_items2 = std::count(v.cbegin(), v.cend(), 2);

    int J = v[0];
    cout << " [J=" << J << "] ";

    if (num_items5 == 1) {
        //cout << "Five of a kind" << endl;
        return 6;
    } else if (num_items4 == 1) {
        if ((J == 1) or (J == 4))
            return 6;
        //cout << "Four of a kind" << endl;
        return 5;
    } else if (num_items3 == 1 and num_items2 == 1) {
        //cout << "Full house" << endl;
        if (J > 0)    //3->J or 2->J = 5
            return 6;
        return 4;
    } else if (num_items3 == 1 and num_items2 not_eq 1) {
        //cout << "Three of a kind" << endl;
        if ((J == 1) or (J == 3))
            return 5;    //->4
        return 3;
    } else if (num_items2 == 2) {
        //cout << "Two pair" << endl;
        if (J == 1)
            return 4;
        if (J == 2)
            return 5;
        return 2;
    } else if (num_items2 == 1) {
        //cout << "One pair" << endl;

        if ((J == 1) or (J == 2))
            return 3;
        return 1;
    } else {
        //cout << "High cards" << endl;
        if (J == 1)
            return 1;
        return 0;
    }
    return 0;
}

bool cmpHands(const hand &a, const hand &b)
{

    //cout << a[0] << a[1] << a[2] << a[3] << a[4] << " score=" << getScore(a) << endl;
    int scorea = getScore(a);
    int scoreb = getScore(b);

    if (scorea == scoreb) {
        //second ordering rule
        for (int i = 0; i < 5; ++i) {
            if (a[i] == b[i])
                continue;
            return a[i] < b[i];
        }
    }

    return scorea < scoreb;

    //second ordering rule

    return false;
}

char sanitize(char a)
{
    if (a == 'T')
        return '9' + 1;
    if (a == 'J')
        return '1';
    if (a == 'Q')
        return '9' + 2;
    if (a == 'K')
        return '9' + 3;
    if (a == 'A')
        return '9' + 4;
    return a;
}

int main()
{
    std::ifstream ifs;
    ifs.open("day07.in");
    if (not ifs) {
        ifs.open("../day07.in");
    }
    std::string line;

    std::vector<std::pair<hand, long>> vect;

    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        }
        long num = std::stol(line.data() + 5);
        for (int i = 0; i < 5; ++i) {
            line[i] = sanitize(line[i]);
        }
        hand cards{line[0], line[1], line[2], line[3], line[4]};
        vect.emplace_back(cards, num);
    }

    auto customLess = [](const auto &a, const auto &b) { return cmpHands(a.first, b.first); };
    std::sort(vect.begin(), vect.end(), customLess);

    long i = 0;

    long sum = 0;
    for (const auto &[a, b] : vect) {
        sum += ++i * b;

        cout << "* " << a[0] << a[1] << a[2] << a[3] << a[4] << " (" << getScore(a) << ")" << endl;
    }
    cout << "res=" << sum << endl;
}