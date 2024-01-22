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

using namespace std;

vector<vector<char>> read()
{
    vector<vector<char>> values;
    string line;
    while (getline(cin, line))
    {
        vector<char> l;
        for (char c : line)
        {
            l.push_back(c);
        }
        values.push_back(l);
    }
    return values;
}

bool isSpecial(char c)
{
    return (!isdigit(c) && c != '.');
}

bool isPart(int r, int c, vector<vector<char>> mat)
{
    vector<int> dx{1, -1, 0, 0, 1, 1, -1, -1};
    vector<int> dy{0, 0, 1, -1, 1, -1, 1, -1};
    int x, y;
    int m = mat.size(), n = mat[0].size();
    for (int i = 0; i < 8; i++)
    {
        x = r + dx[i];
        y = c + dy[i];
        if (0 <= x && x < m && 0 <= y && y < n)
        {
            if (isSpecial(mat[x][y]))
                return true;
        }
    }
    return false;
}

void part1()
{
    auto mat = read();
    int ans = 0;
    int m = mat.size(), n = mat[0].size();
    for (int i = 0; i < m; i++)
    {
        int j = 0;
        while (j < n)
        {
            bool cond = false;
            string s = "";
            while (j < n && isdigit(mat[i][j]))
            {
                if (isPart(i, j, mat))
                {
                    cond = true;
                }
                s += mat[i][j++];
            }
            if (cond)
            {
                ans += stoi(s);
            }
            j++;
        }
    }
    cout << ans << endl;
}

string checkLeft(int r, int c, vector<vector<char>> mat)
{
    string s = "";
    while (c >= 0 && isdigit(mat[r][c]))
    {
        s = mat[r][c--] + s;
    }
    return s;
}

string checkRight(int r, int c, vector<vector<char>> mat)
{
    string s = "";
    while (c < mat[0].size() && isdigit(mat[r][c]))
    {
        s += mat[r][c++];
    }
    return s;
}

void part2()
{
    auto mat = read();
    int ans = 0;
    int m = mat.size(), n = mat[0].size();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == '*')
            {
                vector<int> nums;
                string s;
                // left
                s = checkLeft(i, j - 1, mat);
                if (s.length() > 0)
                    nums.push_back(stoi(s));
                // right
                s = checkRight(i, j + 1, mat);
                if (s.length() > 0)
                    nums.push_back(stoi(s));
                // top
                string sl, sr;
                if (i > 0)
                {
                    sl = checkLeft(i - 1, j - 1, mat);
                    sr = checkRight(i - 1, j + 1, mat);
                    if (isdigit(mat[i - 1][j]))
                    {
                        s = sl + mat[i - 1][j] + sr;
                        if (s.length() > 0)
                            nums.push_back(stoi(s));
                    }
                    else
                    {
                        if (sl.length() > 0)
                            nums.push_back(stoi(sl));
                        if (sr.length() > 0)
                            nums.push_back(stoi(sr));
                    }
                }
                // bottom
                if (i + 1 < m)
                {
                    sl = checkLeft(i + 1, j - 1, mat);
                    sr = checkRight(i + 1, j + 1, mat);
                    if (isdigit(mat[i + 1][j]))
                    {
                        s = sl + mat[i + 1][j] + sr;
                        if (s.length() > 0)
                            nums.push_back(stoi(s));
                    }
                    else
                    {
                        if (sl.length() > 0)
                            nums.push_back(stoi(sl));
                        if (sr.length() > 0)
                            nums.push_back(stoi(sr));
                    }
                }
                if (nums.size() == 2)
                {
                    ans += nums[0] * nums[1];
                }
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