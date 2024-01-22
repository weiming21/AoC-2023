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
#include <unordered_set>

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
        unordered_set<int> s;
        for (int i = val.find(":") + 2; i < val.find("|") - 1; i += 3)
        {
            s.insert(stoi(val.substr(i, 2)));
        }
        int pts = -1;
        for (int i = val.find("|") + 2; i < val.length(); i += 3)
        {
            int x = stoi(val.substr(i, 2));
            if (s.count(x))
            {
                pts += 1;
            }
        }
        if (pts != -1)
            ans += pow(2, pts);
    }
    cout << ans << endl;
}

void part2()
{
    auto values = read();
    int ans = 0;
    unordered_map<int, int> m;
    int id = 1;
    for (auto val : values)
    {
        unordered_set<int> s;
        for (int i = val.find(":") + 2; i < val.find("|") - 1; i += 3)
        {
            s.insert(stoi(val.substr(i, 2)));
        }
        int cnt = 0;
        for (int i = val.find("|") + 2; i < val.length(); i += 3)
        {
            int x = stoi(val.substr(i, 2));
            if (s.count(x))
            {
                cnt += 1;
            }
        }
        // if (m.find(id) == m.end())
        //     m[id] = 0;
        // m[id]++;

        auto cur = m.emplace(id, 0);
        cur.first->second += 1;

        for (int i = 0; i < m[id]; i++)
        {
            for (int j = id + 1; j <= id + cnt; j++)
            {
                auto child = m.emplace(j, 0);
                child.first->second += 1;
            }
        }
        id++;
    }
    ans = accumulate(m.begin(), m.end(), 0, [](auto prev, auto &entry)
                     { return prev + entry.second; });
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