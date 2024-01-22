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

vector<pair<int, int>> get_neigh(vector<string> mat, pair<int, int> node, bool part2)
{
    vector<pair<int, int>> moves{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    if (!part2)
    {
        char tile = mat[node.first][node.second];
        switch (tile)
        {
        case '>':
            moves = {{0, 1}};
            break;
        case '<':
            moves = {{0, -1}};
            break;
        case 'v':
            moves = {{1, 0}};
            break;
        case '^':
            moves = {{-1, 0}};
            break;
        }
    }
    vector<pair<int, int>> next_moves;
    int rn, cn;
    for (auto move : moves)
    {
        rn = node.first + move.first;
        cn = node.second + move.second;
        if (0 <= rn && rn < mat.size() && 0 <= cn && cn < mat[0].size() && mat[rn][cn] != '#')
        {
            next_moves.push_back({rn, cn});
        }
    }
    return next_moves;
}

// path compression into smaller weighted graph
void compress(vector<string> mat, bool part2, map<pair<int, int>, vector<pair<pair<int, int>, int>>> &adj_list)
{
    int m = mat.size(), n = mat[0].size();
    set<pair<int, int>> new_nodes;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == '#')
                continue;
            vector<pair<int, int>> next = get_neigh(mat, {i, j}, part2);
            if (next.size() > 2) // otherwise (i, j) guaranteed to be compressed
            {
                new_nodes.insert({i, j});
            }
        }
    }
    new_nodes.insert({0, 1});         // start
    new_nodes.insert({m - 1, n - 2}); // end

    // run bfs to generate new graph with weighted edges
    for (auto n : new_nodes)
    {
        vector<pair<int, int>> q;
        set<pair<int, int>> visited;
        q.push_back(n);
        visited.insert(n);
        int length = 0;
        while (!q.empty())
        {
            vector<pair<int, int>> temp;
            length++;
            for (auto cur : q)
            {
                for (auto neigh : get_neigh(mat, cur, part2))
                {
                    if (!visited.count(neigh))
                    {
                        if (new_nodes.count(neigh))
                        {
                            adj_list[n].push_back({neigh, length});
                            // adj_list[neigh].push_back({n, length});
                        }
                        else
                        {
                            temp.push_back(neigh);
                        }
                        visited.insert(neigh);
                    }
                }
            }
            q = temp;
        }
    }

    // for (auto [k, v] : adj_list)
    // {
    //     cout << k.first << ',' << k.second << ':' << endl;
    //     for (auto i : v)
    //     {
    //         cout << i.second << ';' << i.first.first << ',' << i.first.second << '/';
    //     }
    //     cout << endl;
    //     cout << endl;
    // }
}

int cnt = 0;
void dfs(map<pair<int, int>, vector<pair<pair<int, int>, int>>> &adj_list, pair<int, int> node, pair<int, int> dest, set<pair<int, int>> &visited, int total, int &best)
{
    // cout << node.first << ' ' << node.second << endl;
    if (node == dest)
    {
        cnt++;
        cout << cnt << endl;
        best = max(best, total);
    }
    for (auto neigh : adj_list[node])
    {
        pair<int, int> next = neigh.first;
        int l = neigh.second;
        if (!visited.count(next))
        {
            visited.insert(next);
            dfs(adj_list, next, dest, visited, total + l, best);
            visited.erase(next);
        }
    }
}

void part1()
{
    auto mat = read();
    int ans = 0;
    int m = mat.size(), n = mat[0].size();

    map<pair<int, int>, vector<pair<pair<int, int>, int>>> adj_list;
    compress(mat, false, adj_list);

    set<pair<int, int>> visited;
    int best = 0;
    dfs(adj_list, {0, 1}, {m - 1, n - 2}, visited, 0, best);
    ans = best;

    cout << ans << endl;
}

void part2()
{
    auto mat = read();
    int ans = 0;
    int m = mat.size(), n = mat[0].size();

    map<pair<int, int>, vector<pair<pair<int, int>, int>>> adj_list;
    compress(mat, true, adj_list);

    set<pair<int, int>> visited;
    int best = 0;
    dfs(adj_list, {0, 1}, {m - 1, n - 2}, visited, 0, best);
    ans = best;

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