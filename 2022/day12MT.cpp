//---------------------------------------
//--- Day 12: Hill Climbing Algorithm ---
// https://adventofcode.com/2022/day/12
//---------------------------------------

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
#include <set>

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <shared_mutex>

using namespace std;

const int INF = 65536;

pair<uint64_t, uint64_t> floydWarshall(vector<string> &graph, pair<int, int> S, pair<int, int> E)
{
    int height = graph.size();
    int length = graph[0].length();

    uint64_t V = height * length;
    vector<vector<uint64_t>> matrix(height * length, vector<uint64_t>(height * length));

    vector<pair<int, int>> arr;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < length; ++j) {
            arr.push_back({i, j});
        }
    }

    for (int i = 0; i < V; i++) {
        int i1 = arr[i].first;
        int j1 = arr[i].second;

        char c1 = graph[i1][j1];
        for (int j = 0; j < V; j++) {
            if (i == j) {
                matrix[i][j] = 0;
                continue;
            }
            int i2 = arr[j].first;
            int j2 = arr[j].second;
            char c2 = graph[i2][j2];
            if (c2 <= c1 + 1) {
                if ((i1 == i2 and j1 >= j2 - 1 and j1 <= j2 + 1) or (j1 == j2 and i1 >= i2 - 1 and i1 <= i2 + 1)) {
                    matrix[i][j] = 1;
                    continue;
                }
            }
            matrix[i][j] = INF;
        }
    }

    std::shared_mutex matrixMutex;

    auto worker = [&](int a1, int a2, int k, int V) {
        for (int i = a1; i < a2; i++) {
            if (matrix[i][k] not_eq INF) {
                for (int j = 0; j < V; j++) {
                    if (matrix[k][j] not_eq INF) {
                        bool test = false;
                        {
                            std::shared_lock l(matrixMutex);
                            test = (matrix[i][j] == INF || matrix[i][k] + matrix[k][j] < matrix[i][j]);
                        }
                        if (test) {
                            std::unique_lock l(matrixMutex);
                            if (matrix[i][j] == INF || matrix[i][k] + matrix[k][j] < matrix[i][j])
                                matrix[i][j] = matrix[i][k] + matrix[k][j];
                        }
                    }
                }
            }
        }
    };

    //calculation
    for (int k = 0; k < V; k++) {
        cout << "processing row " << k + 1 << " of (" << V << ")" << endl;

        const auto maxThreads = std::thread::hardware_concurrency();

        vector<std::thread> threads;

        int temp = V / maxThreads;
        for (int i = 0; i < maxThreads; i++) {
            int a1 = i * temp;
            int a2 = (i == maxThreads - 1) ? V - 1 : (i + 1) * (temp)-1;
            //cout << a1 << " " << a2 << endl;
            threads.emplace_back(worker, a1, a2, k, V);
        }
        for (auto &t : threads) {
            t.join();
        }
    }

    //extract result
    uint64_t res1 = 0, res2 = INF;
    ofstream myfile("day12.out");
    if (myfile.is_open()) {
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                myfile << matrix[i][j] << " ";
                if (S == arr[i] and E == arr[j]) {
                    res1 = matrix[i][j];
                }
                if ('a' == graph[arr[i].first][arr[i].second] and E == arr[j]) {
                    res2 = min(res2, matrix[i][j]);
                }
            }
            myfile << endl;
        }
        myfile.close();
    } else {
        cout << "Unable to open file";
    }

    return {res1, res2};
}

int main()
{
    ifstream ifs;
    ifs.open("day12.in");
    if (not ifs) {
        ifs.open("../day12.in");
    }

    int res = 0;
    string line;
    vector<string> map;
    pair<int, int> S, E;
    int height = 0;
    while (getline(ifs, line)) {
        if (auto pos = line.find('S'); pos not_eq string::npos) {
            S = {height, pos};
            replace(line.begin(), line.end(), 'S', 'a');
        }
        if (auto pos = line.find('E'); pos not_eq string::npos) {
            E = {height, pos};
            replace(line.begin(), line.end(), 'E', 'z');
        }
        map.push_back(line);
        height++;
    }
    int length = line.length();

    cout << "S= " << S.first << " " << S.second << endl;
    cout << "E= " << E.first << " " << E.second << endl;
    auto solution = floydWarshall(map, S, E);
    cout << "solution1 = " << solution.first << endl;
    cout << "solution2 = " << solution.second << endl;
}
