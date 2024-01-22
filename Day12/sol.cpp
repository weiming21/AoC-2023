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

ll backtrack(string s, vector<int> cnt, int i, int j, int cur, char prev, map<tuple<int, int, int, int>, ll> &memo)
{
    tuple<int, int, int, int> key(i, j, cur, prev);
    if (memo.find(key) != memo.end())
    {
        return memo[key];
    }

    if (j < cnt.size() && cur == cnt[j])
    {
        return backtrack(s, cnt, i, j + 1, 0, prev, memo);
    }
    if (i == s.length())
    {
        return j == cnt.size() && cur == 0 ? 1 : 0;
    }
    ll dot = backtrack(s, cnt, i + 1, j, cur, '.', memo);
    ll hash = backtrack(s, cnt, i + 1, j, cur + 1, '#', memo);
    ll total = 0;
    if ((s[i] == '.' || s[i] == '?') && (cur == 0))
    {
        total += dot;
    }
    if ((s[i] == '#' || s[i] == '?') && !(prev == '#' && cur == 0))
    {
        total += hash;
    }
    memo[key] = total;
    return total;
}

void part1()
{
    auto lines = read();
    int ans = 0;
    int itr = 0;
    for (auto line : lines)
    {
        vector<string> temp = split_into_str(line, ' ');
        vector<int> cnt = split_into_int(temp[1], ',');
        map<tuple<int, int, int, int>, ll> memo;
        int ways = backtrack(temp[0], cnt, 0, 0, 0, '.', memo);
        cout << ++itr << endl;
        ans += ways;
    }

    cout << ans << endl;
}

void part2()
{
    auto lines = read();
    ll ans = 0;
    int itr = 0;
    for (auto line : lines)
    {
        vector<string> temp = split_into_str(line, ' ');
        vector<int> cnt = split_into_int(temp[1], ',');
        string s = temp[0];
        int l = cnt.size();
        for (int i = 0; i < 4; i++)
        {
            s += '?';
            s += temp[0];
            for (int j = 0; j < l; j++)
            {
                cnt.push_back(cnt[j]);
            }
        }
        map<tuple<int, int, int, int>, ll> memo;
        ll ways = backtrack(s, cnt, 0, 0, 0, '.', memo);
        cout << ++itr << endl;
        ans += ways;
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