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

// calculate 2 * the area of triangle enclosed
// by coord1, coord2, (0, 0) using determinant
int calc_area(pair<int, int> coord1, pair<int, int> coord2)
{
    int det = coord1.first * coord2.second - coord1.second * coord2.first;
    return det;
}

void part1()
{
    auto lines = read();
    int ans = 0;

    map<string, pair<int, int>> m; // dir -> {dx, dy}
    m["R"] = {1, 0};
    m["L"] = {-1, 0};
    m["U"] = {0, 1};
    m["D"] = {0, -1};

    pair<int, int> prev{0, 0};
    pair<int, int> cur{0, 0};
    int area = 0;
    int boundary = 0;
    for (auto line : lines)
    {
        // shoelace formula
        area += calc_area(prev, cur);

        vector<string> in = split_into_str(line, ' ');
        string dir = in[0];
        pair<int, int> move = m[dir];
        int steps = stoi(in[1]);

        boundary += steps;
        prev = cur;
        cur = {cur.first + steps * move.first, cur.second + steps * move.second};
    }
    area = abs(area) / 2;

    // pick's theorem
    // A = interior + boundary / 2 - 1
    int interior = area + 1 - boundary / 2;
    ans = interior + boundary;

    cout << ans << endl;
}

ll calc_area_ll(pair<ll, ll> coord1, pair<ll, ll> coord2)
{
    ll det = coord1.first * coord2.second - coord1.second * coord2.first;
    return det;
}

int hexadecode(string s)
{
    int decimal = 0;
    int power = 0;
    int rep;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        char c = s[i];
        if (isdigit(c))
            rep = c - '0';
        else
            rep = c - 'a' + 10;
        decimal += rep * pow(16, power++);
    }
    return decimal;
}

void part2()
{
    auto lines = read();
    ll ans = 0;

    map<int, pair<int, int>> m; // dir -> {dx, dy}
    // 0 means R, 1 means D, 2 means L, and 3 means U
    m[0] = {1, 0};
    m[1] = {0, -1};
    m[2] = {-1, 0};
    m[3] = {0, 1};

    pair<ll, ll> prev{0, 0};
    pair<ll, ll> cur{0, 0};
    ll area = 0;
    ll boundary = 0;
    for (auto line : lines)
    {
        // shoelace formula
        area += calc_area_ll(prev, cur);

        vector<string> in = split_into_str(line, ' ');
        string code = in[2].substr(2, 6);
        int dir = code[5] - '0';
        pair<int, int> move = m[dir];
        int steps = hexadecode(code.substr(0, 5));

        boundary += steps;
        prev = cur;
        cur = {cur.first + steps * move.first, cur.second + steps * move.second};
    }
    area = abs(area) / 2;

    // pick's theorem
    // A = interior + boundary / 2 - 1
    ll interior = area + 1 - boundary / 2;
    ans = interior + boundary;

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