//-------------------------------------
//--- Day 20: Grove Positioning System ---
//https://adventofcode.com/2022/day/20
//-------------------------------------

#include <iostream>
#include <sstream>
#include <stdlib.h> /* abs */
#include <cstring>
#include <array>
#include <algorithm>
#include <stack>
#include <vector>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

using Data = vector<int64_t>;

bool ReadInput(Data &data, string &error)
{
    error.clear();
    ifstream ifs;
    ifs.open("day20.in");
    if (not ifs) {
        ifs.open("../day20.in");
    }

    string line;
    while (getline(ifs, line)) {
        try {
            int64_t d = stoll(line);
            data.push_back(d);
        } catch (...) {
            error = "Conversion failure ";
            return false;
        }
    }
    return true;
}

int64_t RealMod(int64_t A, int64_t B)
{
    auto temp = A % B;
    if (temp < 0) {
        temp += B;
    }
    return temp;
}

int64_t Calculate(Data &data)
{
    deque<vector<int64_t>> X;
    for (int i = 0; i < data.size(); ++i) {
        X.push_back({i, data[i] * 811589153});
    }

    for (int t = 0; t < 10; ++t) {
        for (int i = 0; i < X.size(); ++i) {
            int j = 0;
            for (; j < X.size() and X[j][0] not_eq i; ++j) {
            }
            while (X[0][0] not_eq i) {
                X.push_back(X.front());
                X.pop_front();
            }

            auto val = X.front();
            X.pop_front();
            auto to_pop = val[1];
            to_pop = RealMod(to_pop, int64_t(X.size()));

            for (int z = 0; z < to_pop; ++z) {
                X.push_back(X.front());
                X.pop_front();
            }
            X.push_back(val);
        }
    }

    int j = 0;
    for (; j < X.size() and X[j][1] not_eq 0; ++j) {
    }

    return (X[(j + 1000) % X.size()][1] + X[(j + 2000) % X.size()][1] + X[(j + 3000) % X.size()][1]);
}

int main()
{
    string error;
    Data data;
    if (not ReadInput(data, error)) {
        cout << error << endl;
        return -1;
    }

    auto res = Calculate(data);
    cout << endl << "solution= " << res << endl;
}
