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
    int r, c;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == 'S')
            {
                r = i;
                c = j;
                break;
            }
        }
    }

    vector<int> dr{0, 0, 1, -1};
    vector<int> dc{1, -1, 0, 0};
    vector<vector<char>> sym{
        {'-', 'J', '7'}, {'-', 'L', 'F'}, {'|', 'L', 'J'}, {'|', '7', 'F'}};

    vector<int> prev{r, c};
    int rn, cn;
    for (int i = 0; i < 4; i++) // explore possible start
    {
        rn = r + dr[i];
        cn = c + dc[i];
        vector<char> s = sym[i];

        if (0 <= rn && rn < m && 0 <= cn && cn < n && find(s.begin(), s.end(), mat[rn][cn]) != s.end())
        {

            r = rn;
            c = cn;
            break;
        }
    };

    unordered_map<char, vector<vector<int>>> map;
    map['-'] = {{0, 1}, {0, -1}};
    map['|'] = {{1, 0}, {-1, 0}};
    map['L'] = {{-1, 0}, {0, 1}};
    map['J'] = {{-1, 0}, {0, -1}};
    map['7'] = {{0, -1}, {1, 0}};
    map['F'] = {{1, 0}, {0, 1}};

    int steps = 1;
    char cur = mat[r][c];
    while (cur != 'S')
    {
        for (auto v : map[cur])
        {
            if (!(r + v[0] == prev[0] && c + v[1] == prev[1]))
            {
                prev = {r, c};
                r += v[0];
                c += v[1];
                break;
            }
        }
        cur = mat[r][c];
        steps++;
    }

    ans = (steps + 1) / 2;
    cout << ans << endl;
}

vector<vector<char>> preprocess(vector<string> &lines)
{
    int m = lines.size(), n = lines[0].size();
    vector<vector<char>> mat(m, vector<char>(n, '0'));
    int r, c;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mat[i][j] = lines[i][j];
            if (mat[i][j] == 'S')
            {
                r = i;
                c = j;
            }
        }
    }

    vector<int> dr{0, 0, 1, -1};
    vector<int> dc{1, -1, 0, 0};
    vector<vector<char>> sym{
        {'-', 'J', '7'}, {'-', 'L', 'F'}, {'|', 'L', 'J'}, {'|', '7', 'F'}};

    vector<int> prev{r, c};
    int rn, cn;
    bool found = false;
    vector<vector<int>> start;
    for (int i = 0; i < 4; i++) // explore possible starts
    {
        rn = r + dr[i];
        cn = c + dc[i];
        vector<char> s = sym[i];
        if (0 <= rn && rn < m && 0 <= cn && cn < n && find(s.begin(), s.end(), mat[rn][cn]) != s.end())
        {
            if (found) // find both starts and only assign for the second one
            {
                r = rn;
                c = cn;
            }
            found = true;
            start.push_back({dr[i], dc[i]});
        }
    };

    unordered_map<char, vector<vector<int>>> map;
    map['-'] = {{0, 1}, {0, -1}};
    map['|'] = {{1, 0}, {-1, 0}};
    map['L'] = {{0, 1}, {-1, 0}};
    map['J'] = {{0, -1}, {-1, 0}};
    map['7'] = {{0, -1}, {1, 0}};
    map['F'] = {{0, 1}, {1, 0}};

    for (const auto &[k, v] : map) // reassign S to the correct pipe
    {
        if (v == start)
            lines[prev[0]][prev[1]] = k;
    }

    int steps = 1;
    char cur = mat[r][c];
    mat[r][c] = 'X';
    while (cur != 'S')
    {
        for (auto v : map[cur])
        {
            if (!(r + v[0] == prev[0] && c + v[1] == prev[1]))
            {
                prev = {r, c};
                r += v[0];
                c += v[1];
                break;
            }
        }
        cur = mat[r][c];
        mat[r][c] = 'X';
    }

    return mat;
}

void part2()
{
    auto original = read();
    int ans = 0;
    vector<vector<char>> marked = preprocess(original);
    int m = marked.size(), n = marked[0].size();

    // only consider |F7 as vertical pipes
    unordered_set<char> verts{'|', 'F', '7'};
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (marked[i][j] != 'X')
            {
                bool out = true;
                for (int k = j + 1; k < n; k++)
                {

                    if (marked[i][k] == 'X' && verts.count(original[i][k]))
                    {
                        out = !out;
                    }
                }
                if (!out)
                {
                    marked[i][j] = 'I';
                    ans++;
                }
            }
        }
    }

    // for (auto itr : original)
    // {
    //     for (auto i : itr)
    //     {
    //         cout << i;
    //     }
    //     cout << endl;
    // }

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