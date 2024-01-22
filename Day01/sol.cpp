// -*- C++ -*-
// g++ -std=c++17 -o sol sol.cpp
// ./sol 1 < input.txt  # part 1
// ./sol 2 < input.txt  # part 2

#include <iostream>
#include <cstdio>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>
#include <unordered_map>

using namespace std;

vector<string> read()
{
    vector<string> values;
    string line;
    while (getline(cin, line))
    {
        values.push_back(line);
    }
    return values;
}

void part1()
{
    auto values = read();
    int ans = 0;

    for (auto val : values)
    {
        string digits = "";
        for (char c : val)
        {
            if (isdigit(c))
            {
                digits += c;
            }
        }
        int ten = digits[0] - '0';
        int one = digits[digits.length() - 1] - '0';
        ans += ten * 10 + one;
    }
    cout << ans << endl;
}

void part2()
{
    auto values = read();
    int ans = 0;
    unordered_map<string, int> m{{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};
    for (auto val : values)
    {
        string l3, l4, l5;
        char d;
        for (int i = 0; i < val.length(); i++)
        {
            d = val[i];
            if (isdigit(d))
            {
                ans += (d - '0') * 10;
                break;
            }
            l3 = val.substr(i, 3);
            if (m.count(l3) != 0)
            {
                ans += m[l3] * 10;
                break;
            }
            l4 = val.substr(i, 4);
            if (m.count(l4) != 0)
            {
                ans += m[l4] * 10;
                break;
            }
            l5 = val.substr(i, 5);
            if (m.count(l5) != 0)
            {
                ans += m[l5] * 10;
                break;
            }
        }
        for (int i = val.length(); i >= 0; i--)
        {
            d = val[i];
            if (isdigit(d))
            {
                ans += (d - '0');
                break;
            }
            l3 = val.substr(max(0, i - 2), 3);
            if (m.count(l3) != 0)
            {
                ans += m[l3];
                break;
            }
            l4 = val.substr(max(0, i - 3), 4);
            if (m.count(l4) != 0)
            {
                ans += m[l4];
                break;
            }
            l5 = val.substr(max(0, i - 4), 5);
            if (m.count(l5) != 0)
            {
                ans += m[l5];
                break;
            }
        }
    }
    cout << ans << endl;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "usage: " << argv[0] << " partnum < input\n";
        exit(1);
    }
    if (*argv[1] == '1')
        part1();
    else
        part2();
    return 0;
}