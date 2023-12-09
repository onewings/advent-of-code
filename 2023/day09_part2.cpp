//----------------------------------------
// --- Day 9 part 1
// https://adventofcode.com/2023/day/9
//----------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <array>
#include <unordered_map>

using namespace std;
using MAP = vector<vector<long>>;

long get_prediction(vector<long> v)
{
    vector<vector<long>> rows;
    rows.push_back(v);
    while (not std::all_of((*rows.rbegin()).cbegin(), (*rows.rbegin()).cend(),
                           [](long k) { return (k == 0 or k == -0); })) {
        vector<long> new_v;
        const vector<long> &last_v = (*rows.rbegin());

        for (int i = 0, m = last_v.size() - 1; i < m; ++i) {
            new_v.push_back(last_v[i + 1] - last_v[i]);
        }
        rows.push_back(new_v);
    }
    (*rows.rbegin()).push_back(0);

    for (int i = rows.size() - 2; i >= 0; --i) {
        auto t = *rows[i].rbegin() + *rows[i + 1].rbegin();

        rows[i].push_back(t);
    }

    //print
    for (int i = 0; i < rows.size(); ++i) {
        for (int j = 0; j < rows[i].size(); ++j) {
            cout << rows[i][j] << " ";
        }
        cout << endl;
    }
    return *(*rows.begin()).rbegin();
}

int main()
{
    std::ifstream ifs;
    ifs.open("day09.in");
    if (not ifs) {
        ifs.open("../day09.in");
    }

    MAP gmap;
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        }

        string s, tmp;
        stringstream ss(line);
        vector<long> serie;

        while (getline(ss, tmp, ' ')) {
            serie.push_back(stol(tmp));
        }

        gmap.push_back(serie);
    }

    long acc = 0;
    for (auto &v : gmap) {
        reverse(v.begin(), v.end());    // added only this line for part 2 :-)
        auto k = get_prediction(v);
        cout << "temp res of v= " << k << endl;
        acc += k;
    }

    cout << "res= " << acc;
}