// -*- C++ -*-
// g++ -std=c++17 -o sol sol.cpp
// ./sol 1 < input.txt  # part 1
// ./sol 2 < input.txt  # part 2

#include <iostream>
#include <fstream>
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

int bfs(vector<string> mat, int steps)
{
    // get starting position
    pair<int, int> start;
    int m = mat.size(), n = mat[0].size();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == 'S')
            {
                start = {i, j};
                mat[i][j] = '.';
                break;
            }
        }
    }

    queue<pair<pair<int, int>, int>> q;
    set<pair<pair<int, int>, int>> visited;
    set<pair<int, int>> final;
    q.push({start, 0});
    visited.insert({start, 0});
    vector<pair<int, int>> moves{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    while (!q.empty())
    {
        pair<pair<int, int>, int> cur = q.front();
        q.pop();
        pair<int, int> coord = cur.first;
        int curstep = cur.second;
        if (curstep == steps)
        {
            final.insert(coord);
            continue;
        }

        int r = coord.first, c = coord.second;
        int rn, cn;
        for (auto move : moves)
        {
            rn = r + move.first;
            cn = c + move.second;
            if (0 <= rn && rn < m && 0 <= cn && cn < n && mat[rn][cn] == '.')
            {
                pair<pair<int, int>, int> next = {{rn, cn}, curstep + 1};
                if (!visited.count(next))
                {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }
    }

    return final.size();
}

void part1()
{
    auto mat = read();
    int ans = 0;

    ans = bfs(mat, 64);
    cout << ans << endl;
}

ll bfs_v2(vector<string> mat, int steps)
{
    // get starting position
    pair<int, int> start;
    int m = mat.size(), n = mat[0].size();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == 'S')
            {
                start = {i, j};
                break;
            }
        }
    }

    queue<pair<pair<int, int>, int>> q;
    set<pair<pair<int, int>, int>> visited;
    set<pair<int, int>> final;
    q.push({start, 0});
    visited.insert({start, 0});
    vector<pair<int, int>> moves{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    while (!q.empty())
    {
        pair<pair<int, int>, int> cur = q.front();
        q.pop();
        pair<int, int> coord = cur.first;
        int curstep = cur.second;
        if (curstep == steps)
        {
            final.insert(coord);
            continue;
        }

        int r = coord.first, c = coord.second;
        int rn, cn, rn_adj, cn_adj;
        for (auto move : moves)
        {
            rn = r + move.first;
            cn = c + move.second;
            rn_adj = (rn % m + m) % m;
            cn_adj = (cn % n + n) % n;
            if (mat[rn_adj][cn_adj] != '#')
            {
                pair<pair<int, int>, int> next = {{rn, cn}, curstep + 1};
                if (!visited.count(next))
                {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }
    }

    // for (auto c : final)
    // {
    //     if (c.first >= 0 && c.first < m && c.second >= 0 && c.second < n)
    //         mat[c.first][c.second] = 'O';
    // }

    return final.size();
}

ll lagrange_interpolate(int n_steps, vector<int> x, vector<ll> y)
{
    ll output = 0;
    for (int i = 0; i < x.size(); i++)
    {
        ll temp = y[i];
        for (int j = 0; j < x.size(); j++)
        {
            if (i != j)
            {
                temp *= (n_steps - x[j]);
                temp /= (x[i] - x[j]);
            }
        }
        output += temp;
    }

    return output;
}

void part2()
{
    auto mat = read();
    ll ans = 0;

    // // display diamond-shaped coverage
    // ans = bfs_v2(mat, 65);
    // for (auto itr : mat)
    // {
    //     for (auto i : itr)
    //     {
    //         cout << i;
    //     }
    //     cout << '\n';
    // }

    vector<int> x;
    vector<ll> y;
    int width = mat.size();
    for (int steps = width / 2, cnt = 0; cnt < 3; cnt++, steps += width)
    {
        x.push_back(steps);
        ll ways = bfs_v2(mat, steps);
        y.push_back(ways);
        cout << steps << ',' << ways << endl;
    }

    int n_steps = 26501365; // 26501365 = 65 + 202300 * 131
    ans = lagrange_interpolate(n_steps, x, y);
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