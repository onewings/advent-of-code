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

long get_dest(const TripleArrRef &arrRef, long number)
{
    for (const auto &[x1, x2, x3] : arrRef.get()) {
        if (x1 <= number and number < x1 + x2) {
            return number - x1 + x3;
        }
    }
    return number;
}

long get_location(const std::array<TripleArrRef, 7> &gmap, long number)
{
    long temp = number;
    for (const auto &m : gmap) {
        temp = get_dest(m, temp);
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

    std::vector<long> calc;
    for (auto x : seeds) {
        calc.push_back(get_location(gmap, x));
    }
    cout << "min: " << *std::min_element(calc.begin(), calc.end()) << endl;

    return 0;
}