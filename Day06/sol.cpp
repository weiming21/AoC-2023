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
        if (isdigit(token[0]))
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
    auto lines = read();
    int ans = 1;
    vector<int> time = split(lines[0], ' ');
    vector<int> dist = split(lines[1], ' ');

    int count;
    for (int i = 0; i < time.size(); i++)
    {
        count = 0;
        for (int t = i; t <= time[i]; t++)
        {
            int d = (time[i] - t) * t;
            if (d > dist[i])
                count++;
        }
        ans *= count;
    }

    cout << ans << endl;
}

ll convert(string str)
{
    string s = "";
    for (char c : str)
    {
        if (isdigit(c))
            s += c;
    }
    return stoll(s);
}

void part2()
{
    auto lines = read();
    ll ans = 0;
    ll time = convert(lines[0]);
    ll dist = convert(lines[1]);

    ll win;
    for (int i = 0; i <= time; i++)
    {
        ll d = (time - i) * i;
        if (d > dist)
        {
            win = i;
            break;
        }
    }

    ans = (time - win) - win + 1;
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