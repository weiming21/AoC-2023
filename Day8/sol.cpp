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

vector<string> split(string str, char delimiter)
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
    auto lines = read();
    int ans = 0;
    string commands = lines[0];
    unordered_map<string, vector<string>> m;
    for (int i = 2; i < lines.size(); i++)
    {
        vector<string> temp = split(lines[i], ' ');
        m[temp[0]] = {temp[2].substr(1, 3),
                      temp[3].substr(0, 3)};
    }

    string cur = "AAA";
    int ptr = 0;
    while (cur != "ZZZ")
    {
        int idx = commands[ptr] == 'L' ? 0 : 1;
        cur = m[cur][idx];
        ptr = (ptr + 1) % commands.length();
        ans++;
    }
    cout << ans << endl;
}

void part2()
{
    auto lines = read();
    ll ans = 0;
    string commands = lines[0];
    vector<string> start;
    unordered_map<string, vector<string>> m;
    for (int i = 2; i < lines.size(); i++)
    {
        vector<string> temp = split(lines[i], ' ');
        m[temp[0]] = {temp[2].substr(1, 3),
                      temp[3].substr(0, 3)};
        if (temp[0][2] == 'A')
        {
            start.push_back(temp[0]);
        };
    }

    for (int i = 0; i < start.size(); i++)
    {
        int ptr = 0;
        ll cnt = 0;
        while (true)
        {
            cnt++;
            int idx = commands[ptr] == 'L' ? 0 : 1;
            start[i] = m[start[i]][idx];
            if (start[i][2] == 'Z')
                break;
            ptr = (ptr + 1) % commands.length();
        }
        if (i == 0)
            ans = cnt;
        else
            ans = lcm(ans, cnt);
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