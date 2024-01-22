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

void part1()
{
    auto mat = read();
    int ans = 0;

    int rows = mat.size(), cols = mat[0].size();
    for (int c = 0; c < cols; c++)
    {
        int pos = 0;
        int load = 0;
        for (int r = 0; r < rows; r++)
        {
            if (mat[r][c] == 'O')
            {
                load += (rows - pos);
                pos++;
            }
            else if (mat[r][c] == '#')
            {
                pos = r + 1;
            }
        }
        ans += load;
    }
    cout << ans << endl;
}

// rotate 90 degree clockwise = transpose + reverse
void rotate(vector<string> &mat)
{
    int rows = mat.size(), cols = mat[0].size();
    for (int i = 0; i < rows; i++)
    {
        for (int j = i + 1; j < cols; j++)
        {
            char temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols / 2; j++)
        {
            char temp = mat[i][j];
            mat[i][j] = mat[i][cols - j - 1];
            mat[i][cols - j - 1] = temp;
        }
    }
}

void tilt(vector<string> &mat)
{
    int rows = mat.size(), cols = mat[0].size();
    for (int c = 0; c < cols; c++)
    {
        int pos = 0;
        for (int r = 0; r < rows; r++)
        {
            if (mat[r][c] == 'O')
            {
                mat[r][c] = '.';
                mat[pos][c] = 'O';
                pos++;
            }
            else if (mat[r][c] == '#')
            {
                pos = r + 1;
            }
        }
    }
}

void part2()
{
    auto mat = read();
    int ans = 0;
    vector<vector<string>> v;
    int idx;

    while (true)
    {
        for (int i = 0; i < 4; i++)
        {
            tilt(mat);
            rotate(mat);
        }

        auto it = find(v.begin(), v.end(), mat);
        if (it != v.end())
        {
            int prev = it - v.begin();
            int cycles = v.size();
            idx = (1000000000 - prev) % (cycles - prev);
            idx = idx == 0 ? cycles - 1 : prev + idx - 1;
            break;
        }
        v.push_back(mat);
    }

    // for (auto itr : mat)
    // {
    //     for (auto i : itr)
    //     {
    //         cout << i;
    //     }
    //     cout << endl;
    // }

    vector<string> final = v[idx];
    int rows = final.size(), cols = final[0].size();
    for (int r = 0; r < rows; r++)
    {
        int multiplier = rows - r;
        for (int c = 0; c < cols; c++)
        {
            if (final[r][c] == 'O')
            {
                ans += multiplier;
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