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
    auto mat = read();
    int ans = 0;
    int m = mat.size(), n = mat[0].size();

    unordered_set<int> rows;
    unordered_set<int> cols;

    for (int i = 0; i < m; i++)
    {
        bool expand = true;
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == '#')
            {
                expand = false;
                break;
            }
        }
        if (expand)
            rows.insert(i);
    }
    for (int j = 0; j < n; j++)
    {
        bool expand = true;
        for (int i = 0; i < m; i++)
        {
            if (mat[i][j] == '#')
            {
                expand = false;
                break;
            }
        }
        if (expand)
            cols.insert(j);
    }

    vector<pair<int, int>> nodes;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == '#')
            {
                nodes.push_back({i, j});
            }
        }
    }

    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = i + 1; j < nodes.size(); j++)
        {
            int r_start = min(nodes[i].first, nodes[j].first), r_end = max(nodes[i].first, nodes[j].first);
            int c_start = min(nodes[i].second, nodes[j].second), c_end = max(nodes[i].second, nodes[j].second);
            for (int r = r_start + 1; r <= r_end; r++)
            {
                ans += rows.count(r) ? 2 : 1;
            }
            for (int c = c_start + 1; c <= c_end; c++)
            {
                ans += cols.count(c) ? 2 : 1;
            }
        }
    }

    cout << ans << endl;
}

void part2()
{
    auto mat = read();
    ll ans = 0;
    int m = mat.size(), n = mat[0].size();

    unordered_set<int> rows;
    unordered_set<int> cols;

    for (int i = 0; i < m; i++)
    {
        bool expand = true;
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == '#')
            {
                expand = false;
                break;
            }
        }
        if (expand)
            rows.insert(i);
    }
    for (int j = 0; j < n; j++)
    {
        bool expand = true;
        for (int i = 0; i < m; i++)
        {
            if (mat[i][j] == '#')
            {
                expand = false;
                break;
            }
        }
        if (expand)
            cols.insert(j);
    }

    vector<pair<int, int>> nodes;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == '#')
            {
                nodes.push_back({i, j});
            }
        }
    }

    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = i + 1; j < nodes.size(); j++)
        {
            int r_start = min(nodes[i].first, nodes[j].first), r_end = max(nodes[i].first, nodes[j].first);
            int c_start = min(nodes[i].second, nodes[j].second), c_end = max(nodes[i].second, nodes[j].second);
            for (int r = r_start + 1; r <= r_end; r++)
            {
                ans += rows.count(r) ? 1000000 : 1;
            }
            for (int c = c_start + 1; c <= c_end; c++)
            {
                ans += cols.count(c) ? 1000000 : 1;
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