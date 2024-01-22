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

bool hasHorizLine(int line, vector<string> mat)
{
    int rows = mat.size(), cols = mat[0].size();
    int i = line, j = line + 1;
    while (i >= 0 && j < rows)
    {
        for (int c = 0; c < cols; c++)
        {
            if (mat[i][c] != mat[j][c])
                return false;
        }
        i--;
        j++;
    }
    return true;
}

bool hasVertLine(int line, vector<string> mat)
{
    int rows = mat.size(), cols = mat[0].size();
    int i = line, j = line + 1;
    while (i >= 0 && j < cols)
    {
        for (int r = 0; r < rows; r++)
        {
            if (mat[r][i] != mat[r][j])
                return false;
        }
        i--;
        j++;
    }

    return true;
}

int eval(vector<string> mat, int prev)
{
    int rows = mat.size(), cols = mat[0].size();
    for (int r = 0; r < rows - 1; r++)
    {
        if (hasHorizLine(r, mat) && (r + 1) * 100 != prev)
        {
            return (r + 1) * 100;
        }
    }
    for (int c = 0; c < cols - 1; c++)
    {
        if (hasVertLine(c, mat) && c + 1 != prev)
        {
            return (c + 1);
        }
    }
    return 0;
}

void part1()
{
    auto lines = read();
    int ans = 0;
    vector<string> mat;
    for (auto line : lines)
    {
        if (line.length() != 0)
        {
            mat.push_back(line);
        }
        else
        {
            ans += eval(mat, 0);
            mat.clear();
        }
    }
    cout << ans << endl;
}

void part2()
{
    auto lines = read();
    ll ans = 0;
    vector<string> mat;
    for (auto line : lines)
    {
        if (line.length() != 0)
        {
            mat.push_back(line);
        }
        else
        {
            int rows = mat.size(), cols = mat[0].size();
            int oldLine = eval(mat, 0);
            int newLine;
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    mat[i][j] = mat[i][j] == '#' ? '.' : '#';
                    newLine = eval(mat, oldLine);
                    if (newLine != 0)
                    {
                        ans += newLine;
                        break;
                    }
                    mat[i][j] = mat[i][j] == '#' ? '.' : '#';
                }
                if (newLine != 0)
                    break;
            }
            mat.clear();
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