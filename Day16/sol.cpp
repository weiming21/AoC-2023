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

int helper(vector<string> mat, pair<pair<int, int>, int> start)
{
    int m = mat.size(), n = mat[0].size();
    set<pair<pair<int, int>, int>> visited;
    queue<pair<pair<int, int>, int>> q;
    set<pair<int, int>> energized;
    q.push(start);
    visited.insert(start);

    // 0: left, 1: right, 2: up, 3: down
    while (!q.empty())
    {
        pair<pair<int, int>, int> cur = q.front();
        q.pop();
        pair<int, int> coord = cur.first;
        energized.insert(coord);
        int r = coord.first, c = coord.second;
        int dir = cur.second;
        char sym = mat[coord.first][coord.second];

        if (sym == '\\')
        {
            if (dir == 0)
                r--;
            else if (dir == 1)
                r++;
            else if (dir == 2)
                c--;
            else
                c++;
            dir = (dir + 2) % 4;
        }
        else if (sym == '/')
        {
            if (dir == 0)
                r++;
            else if (dir == 1)
                r--;
            else if (dir == 2)
                c++;
            else
                c--;
            dir = 3 - dir;
        }
        else if (sym == '|')
        {
            if (dir == 0 || dir == 1)
            {
                if (0 <= r - 1 && r - 1 < m && !visited.count({{r - 1, c}, 2}))
                {
                    q.push({{r - 1, c}, 2});
                    visited.insert({{r - 1, c}, 2});
                }
                if (0 <= r + 1 && r + 1 < m && !visited.count({{r + 1, c}, 3}))
                {
                    q.push({{r + 1, c}, 3});
                    visited.insert({{r + 1, c}, 3});
                }
                continue;
            }
            else
            {
                r = dir == 2 ? r - 1 : r + 1;
            }
        }
        else if (sym == '-')
        {
            if (dir == 2 || dir == 3)
            {
                if (0 <= c - 1 && c - 1 < n && !visited.count({{r, c - 1}, 0}))
                {
                    q.push({{r, c - 1}, 0});
                    visited.insert({{r, c - 1}, 0});
                }
                if (0 <= c + 1 && c + 1 < n && !visited.count({{r, c + 1}, 1}))
                {
                    q.push({{r, c + 1}, 1});
                    visited.insert({{r, c + 1}, 1});
                }
                continue;
            }
            else
            {
                c = dir == 0 ? c - 1 : c + 1;
            }
        }
        else
        {
            if (dir == 0)
                c--;
            else if (dir == 1)
                c++;
            else if (dir == 2)
                r--;
            else
                r++;
        }

        if (0 <= r && r < m && 0 <= c && c < n && !visited.count({{r, c}, dir}))
        {
            q.push({{r, c}, dir});
            visited.insert({{r, c}, dir});
        }
    }

    for (auto coord : energized)
    {
        mat[coord.first][coord.second] = '#';
    }

    return energized.size();
}

void part1()
{
    auto mat = read();
    int ans = 0;

    ans = helper(mat, {{0, 0}, 1});

    cout << ans << endl;
}

void part2()
{
    auto mat = read();
    int ans = 0;

    int rows = mat.size(), cols = mat[0].size();
    for (int i = 0; i < rows; i++)
    {
        ans = max(ans, helper(mat, {{i, 0}, 1}));
        ans = max(ans, helper(mat, {{i, cols - 1}, 0}));
    }
    for (int j = 0; j < cols; j++)
    {
        ans = max(ans, helper(mat, {{0, j}, 3}));
        ans = max(ans, helper(mat, {{rows - 1, j}, 2}));
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