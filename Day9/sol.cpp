// -*- C++ -*-
// g++ -std=c++17 -o sol sol.cpp
// ./sol 1 < input.txt  # part 1
// ./sol 2 < input.txt  # part 2

#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#define ll long long

using namespace std;

vector<int> split(string str, char delimiter)
{
    vector<int> values;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter))
    {
        values.push_back(stoi(token));
    }
    return values;
}

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
    auto lines = read();
    int ans = 0;
    vector<int> last;
    int count;
    for (auto line : lines)
    {
        last.clear();
        vector<int> vals = split(line, ' ');
        vector<int> temp; // to fill next row of difference
        bool allEqual = false;
        while (!allEqual)
        {
            allEqual = true;
            temp.clear();
            for (int i = 1; i < vals.size(); i++)
            {
                int diff = vals[i] - vals[i - 1];
                if (diff != 0)
                    allEqual = false;
                temp.push_back(diff);
                if (i == vals.size() - 1)
                    last.push_back(vals[i]);
            }
            vals = temp;
        }
        for (auto l : last)
        {
            ans += l;
        }
    }
    cout << ans << endl;
}

void part2()
{
    auto lines = read();
    int ans = 0;
    vector<int> first;
    int count;
    for (auto line : lines)
    {
        first.clear();
        vector<int> vals = split(line, ' ');
        vector<int> temp; // to fill next row of difference
        bool allEqual = false;
        while (!allEqual)
        {
            allEqual = true;
            temp.clear();
            for (int i = 0; i < vals.size(); i++)
            {
                if (i == 0)
                {
                    first.push_back(vals[i]);
                    continue;
                }
                int diff = vals[i] - vals[i - 1];
                if (diff != 0)
                    allEqual = false;
                temp.push_back(diff);
            }
            vals = temp;
        }
        int v = 0;
        for (int i = first.size() - 1; i >= 0; i--)
        {
            v = first[i] - v;
        }
        ans += v;
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