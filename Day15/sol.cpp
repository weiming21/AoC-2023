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
#include <map>
#include <set>
#include <queue>
#define ll long long

using namespace std;

vector<string> split_into_str(string str, char delimiter)
{
    vector<string> values;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter))
    {
        values.push_back(token);
    }
    return values;
}

vector<int> split_into_int(string str, char delimiter)
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

int getHash(string s)
{
    int cur = 0;
    for (auto c : s)
    {
        cur += int(c);
        cur *= 17;
        cur %= 256;
    }
    return cur;
}

void part1()
{
    auto lines = read();
    int ans = 0;
    vector<string> steps = split_into_str(lines[0], ',');

    for (auto s : steps)
    {
        ans += getHash(s);
    }
    cout << ans << endl;
}

void part2()
{
    auto lines = read();
    int ans = 0;

    map<int, vector<string>> m1;
    map<string, pair<int, int>> m2; // pair<position, focal_length>

    vector<string> steps = split_into_str(lines[0], ',');

    for (auto s : steps)
    {
        int pos = s.find('=');
        if (pos != -1)
        {
            string label = s.substr(0, pos);
            int code = getHash(label);
            int focal = s[s.length() - 1] - '0';
            if (!m2.count(label))
            {
                m1[code].push_back(label);
                m2[label] = {m1[code].size() - 1, focal};
            }
            else
            {
                m2[label].second = focal;
            }
        }
        else
        {
            string label = s.substr(0, s.length() - 1);
            m2.erase(label);
        }
    }

    for (auto &[k, v] : m1)
    {
        int itr = 1;
        int power;
        for (int i = 0; i < v.size(); i++)
        {
            string label = v[i];
            if (m2.count(label) && m2[label].first == i)
            {
                power = (k + 1) * itr * m2[label].second;
                itr++;
                ans += power;
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