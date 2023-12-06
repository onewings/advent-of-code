//----------------------------------------
// --- Day 5: If You Give A Seed A Fertilizer ---
// https://adventofcode.com/2023/day/5
//----------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <array>

using namespace std;
using Triple = std::tuple<long, long, long>;
using TripleArr = std::vector<Triple>;
using TripleArrRef = reference_wrapper<TripleArr>;

using Locations = std::vector<std::pair<long, long>>;

void extractSeedsNumbers(char *s, std::vector<long> &res)
{
    stringstream ss;
    ss << s;
    string temp;
    long number;
    while (not ss.eof()) {
        ss >> temp;
        if (stringstream(temp) >> number) {
            res.push_back(number);
        }
        temp = "";
    }
}

Locations get_ranges(const TripleArrRef &arrRef, const Locations &src_ranges)
{
    Locations res;
    for (const auto &[a, b] : src_ranges) {
        Locations covered_ranges;
        for (const auto &[s, r, d] : arrRef.get()) {
            long x = s;
            long y = s + r - 1;
            if ((b < x) or (y < a))
                continue;
            long inter1 = std::max(a, x);
            long inter2 = std::min(b, y);
            covered_ranges.push_back({inter1, inter2});
            res.push_back({inter1 - s + d, inter2 - s + d});
        }
        if (covered_ranges.empty()) {
            res.push_back({a, b});
            continue;
        }
        sort(covered_ranges.begin(), covered_ranges.end(),
             [](const auto &a, const auto &b) { return a.first < b.first; });

        //analyze the first one
        if (covered_ranges[0].first > a)
            res.push_back({a, covered_ranges[0].first - 1});

        //analyze the end
        const auto &last = covered_ranges.rbegin();
        if ((*last).second < b) {
            res.push_back({(*last).second + 1, b});
        }

        for (int i = 0; i < covered_ranges.size() - 1; ++i) {
            const auto &[x1, y1] = covered_ranges[i];
            const auto &[x2, y2] = covered_ranges[i + 1];
            if (x2 > y1 + 1) {
                res.push_back({y1 + 1, x2 - 1});
            }
        }
    }
    return res;
}

Locations get_location_ranges(const std::array<TripleArrRef, 7> &gmap, const Locations &seed_ranges)
{
    Locations temp = seed_ranges;
    for (const auto &m : gmap) {
        temp = get_ranges(m, temp);
    }
    return temp;
}

int main()
{
    std::ifstream ifs;
    ifs.open("day05.in");
    if (not ifs) {
        ifs.open("../day05.in");
    }

    TripleArr seed_to_soil;
    TripleArr soil_to_fertilizer;
    TripleArr fertilizer_to_water;
    TripleArr water_to_light;
    TripleArr light_to_temperature;
    TripleArr temperature_to_humidity;
    TripleArr humidity_to_location;

    std::array<TripleArrRef, 7> gmap{seed_to_soil,         soil_to_fertilizer,      fertilizer_to_water, water_to_light,
                                     light_to_temperature, temperature_to_humidity, humidity_to_location};
    std::vector<long> seeds;
    std::string line;
    unsigned sum = 0;
    int current = 0;

    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        }
        if (line.rfind("seeds:", 0) == 0)    //start_with in c++20
        {
            extractSeedsNumbers(line.data() + 6, seeds);
            continue;
        } else if (line.rfind("seed-to-soil", 0) == 0)    //start_with in c++20
        {
            current = 0;
            continue;
        } else if (line.rfind("soil-to-fertilizer", 0) == 0)    //start_with in c++20
        {
            current = 1;
            continue;
        } else if (line.rfind("fertilizer-to-water", 0) == 0)    //start_with in c++20
        {
            current = 2;
            continue;
        } else if (line.rfind("water-to-light", 0) == 0)    //start_with in c++20
        {
            current = 3;
            continue;
        } else if (line.rfind("light-to-temperature", 0) == 0)    //start_with in c++20
        {
            current = 4;
            continue;
        } else if (line.rfind("temperature-to-humidity", 0) == 0)    //start_with in c++20
        {
            current = 5;
            continue;
        } else if (line.rfind("humidity-to-location", 0) == 0)    //start_with in c++20
        {
            current = 6;
            continue;
        }

        long x1 = 0, x2 = 0, x3 = 0;
        if (sscanf(line.c_str(), "%d %d %d", &x1, &x2, &x3) == 3) {
            gmap[current].get().emplace_back(x2, x3, x1);
        }
    }

    Locations seeds_ranges;
    for (int i = 0; i < seeds.size(); i = i + 2) {
        seeds_ranges.push_back({seeds[i], seeds[i] + seeds[i + 1] - 1});
    }
    /*for (const auto &[x1, x2] : seeds_ranges) {
        cout << "{" << x1 << "," << x2 << "}" << endl;
    }*/

    Locations location_ranges = get_location_ranges(gmap, seeds_ranges);

    /* for (const auto &[x1, y1] : location_ranges) {
        cout << "(" << x1 << "," << y1 << ")" << endl;
    }*/

    auto result = *std::min_element(location_ranges.cbegin(), location_ranges.cend(),
                                    [](const auto &lhs, const auto &rhs) { return lhs.first < rhs.first; });
    std::cout << "res= " << result.first << std::endl;

    return 0;
}