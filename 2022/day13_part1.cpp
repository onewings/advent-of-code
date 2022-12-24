//------------------------------------
//  --- Day 13: Distress Signal ---
//https://adventofcode.com/2022/day/13
//------------------------------------

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

using namespace std;

struct Value {
    bool isList = false;
    int number{0};
    int level{0};
    Value *parent{nullptr};
    std::vector<Value> values;
};

struct Object {
    string left;
    string right;

    std::vector<Value> vectLeft;
    std::vector<Value> vectRight;

    void Print()
    {
        PrintVect(vectLeft);
        cout << "  --  ";
        PrintVect(vectRight);
    }

    static void PrintVect(const std::vector<Value> &values)
    {
        for (const auto &el : values) {
            if (not el.isList) {
                cout << el.number << " ";
            } else {
                cout << "[";

                PrintVect(el.values);
                cout << "]";
            }
        }
    }

    static void Parse(const string &inString, std::vector<Value> &outVect)
    {
        int pos = 1;
        int level = 0;

        Value rootValue;
        rootValue.isList = true;
        outVect.push_back(rootValue);

        Value *currentList = &outVect.back();
        while (pos < inString.length() - 1) {
            if (inString[pos] == ',') {
                //skip
            } else if (inString[pos] == '[') {
                Value myValue;
                level++;
                myValue.isList = true;
                myValue.level = level;
                myValue.parent = currentList;
                currentList->values.push_back(myValue);
                currentList = &currentList->values.back();
            } else if (inString[pos] == ']') {
                level--;
                currentList = currentList->parent;
            } else {
                int number = stoi(inString.substr(pos));
                Value myValue;
                myValue.number = number;
                myValue.level = level;
                //cout <<number<<"*** back is "<< outVect.back().isList<<" " <<outVect.back().level<<endl;
                //outVect.back().values.push_back(myValue);
                currentList->values.push_back(myValue);
                while ((pos + 1 < inString.length())
                       and (inString[pos + 1] not_eq ',' and inString[pos + 1] not_eq ']')) {
                    pos++;
                }
            }
            pos++;
        }
    }

    void Parse()
    {
        Parse(left, vectLeft);
        Parse(right, vectRight);
    }

    bool CheckOrdering(Value &left, Value &right, bool &forceExit)
    {
        if (not left.isList and not right.isList) {
            //cout << "checks " << left.number << "<" << right.number << " = " << (left.number <= right.number) << endl;
            /*if (!(left.number <= right.number)) */ {
                cout << "checks " << left.number << "<" << right.number << " = " << (left.number <= right.number)
                     << endl;
            }

            if (left.number not_eq right.number) {
                forceExit = true;
            }

            return left.number <= right.number;
        } else if (left.isList and right.isList) {
            auto it1 = left.values.begin();
            auto it2 = right.values.begin();

            while (it1 not_eq left.values.end() and it2 not_eq right.values.end()) {
                bool res = CheckOrdering(*it1, *it2, forceExit);

                if (res == false or forceExit) {
                    cout << "return falseA or forceExit " << res << endl;
                    return res;
                }
                it1++;
                it2++;
            }
            if (forceExit) {
                return true;
            }

            // left or right  is now empty

            //If the left list runs out of items first, the inputs are in the right order
            if (it1 == left.values.end()) {
                cout << "return trueB" << endl;
                forceExit = true;
                return true;
            }

            //If the right list runs out of items first, the inputs are not in the right order
            if (it2 == right.values.end()) {
                cout << "right is empty" << endl;
                forceExit = true;
                return false;
            }
            cout << "it will never happen1" << endl;
            return true;
        } else {
            // exactly one value is an integer, convert the integer to a list which contains that integer as its only value

            if (not left.isList) {
                Value myValue = left;
                left.isList = true;
                left.values.push_back(myValue);
                cout << "Left " << endl;
                PrintVect(left.values);
                cout << endl;
                forceExit = true;
                return CheckOrdering(myValue, right, forceExit);
            }
            if (not right.isList) {
                Value myValue = right;
                right.isList = true;
                right.values.push_back(myValue);
                cout << "Right convert the integer to a list n_" << myValue.number << " isList:" << myValue.isList
                     << endl;
                PrintVect(right.values);
                cout << endl;
                forceExit = true;
                bool temp = CheckOrdering(myValue, right, forceExit);

                cout << " res=" << temp << endl;
                return temp;
            }
            cout << "it will never happen2" << endl;
            return true;
        }
        return true;
    }

    bool CheckOrdering()
    {
        bool forceExit = false;
        return CheckOrdering(vectLeft[0], vectRight[0], forceExit);
    }
};

int main()
{
    std::ifstream ifs;
    ifs.open("day13.in");
    if (not ifs) {
        ifs.open("../day13.in");
    }

    int res = 0;
    std::string line;
    std::vector<Object> map;

    int counter = 0;
    int pair = 0;

    Object current;
    while (std::getline(ifs, line)) {
        pair++;
        if (pair % 3 == 1) {
            current.left = line;
        } else {
            if (pair % 3 == 2) {
                current.right = line;

                counter++;
                current.Parse();
                if (current.CheckOrdering()) {
                    //cout << "GOOD SOLUTION " << counter << endl;
                    res += counter;
                }

                cout << endl << "print ==> ";
                current.Print();
                cout << endl;
                cout << current.left << " " << current.right << endl;

                //map.push_back(current);
                current = Object();
            }
        }
    }

    /*for (auto &element : map) {
        counter++;
        element.Parse();
        if (element.CheckOrdering()) {
            res += counter;
        }
        cout << endl << "print ==> ";
        element.Print();
        cout << endl;
        cout << element.left << " " << element.right << endl;
    }*/
    cout << "solution= " << res << endl;
    return 0;
}
