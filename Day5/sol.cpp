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

vector<ll> split(string str, char delimiter)
{
    vector<ll> values;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter))
    {
        if (isdigit(token[0]))
            values.push_back(stoll(token));
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
    ll ans = 0;

    vector<ll> seeds = split(lines[0], ' ');
    vector<vector<ll>> mappings;

    for (int i = 2; i < lines.size(); i++)
    {
        string line = lines[i];
        if (line.empty())
        {
            for (int s = 0; s < seeds.size(); s++)
            {
                for (auto m : mappings)
                {
                    if (m[1] <= seeds[s] && seeds[s] < m[1] + m[2])
                    {
                        seeds[s] = seeds[s] - m[1] + m[0];
                        break;
                    }
                }
            }
        }
        else if (!isdigit(line[0]))
        {
            mappings.clear();
        }
        else
        {
            vector<ll> range = split(line, ' ');
            mappings.push_back(range);
        }
    }
    ans = *min_element(seeds.begin(), seeds.end());
    cout << ans << endl;
}

void part2()
{
    auto lines = read();
    ll ans = 0;

    vector<ll> temp = split(lines[0], ' ');
    vector<pair<ll, ll>> seeds;
    for (int i = 0; i < temp.size(); i += 2)
    {
        seeds.push_back({temp[i], temp[i] + temp[i + 1]});
    }

    vector<vector<ll>> mappings;
    for (int i = 2; i < lines.size(); i++)
    {
        cout << i << endl;
        string line = lines[i];
        if (line.empty())
        {
            queue<pair<ll, ll>> q;
            for (auto s : seeds)
                q.push(s);
            seeds.clear();

            while (!q.empty())
            {
                pair<ll, ll> s = q.front();
                bool transformed = false;
                for (auto m : mappings)
                {
                    if (s.first < m[1] + m[2] && s.second > m[1])
                    {
                        if (m[1] <= s.first)
                        {
                            if (s.second <= m[1] + m[2])
                            {
                                seeds.push_back({s.first - m[1] + m[0], s.second - m[1] + m[0]});
                            }
                            else
                            {
                                seeds.push_back({s.first - m[1] + m[0], m[0] + m[2]});
                                q.push({m[1] + m[2], s.second});
                            }
                        }
                        else
                        {
                            if (s.second <= m[1] + m[2])
                            {
                                seeds.push_back({m[0], s.second - m[1] + m[0]});
                                q.push({s.first, m[1]});
                            }
                            else
                            {
                                seeds.push_back({m[0], m[0] + m[2]});
                                q.push({s.first, m[1]});
                                q.push({m[1] + m[2], s.second});
                            }
                        }
                        transformed = true;
                        break;
                    }
                }
                if (!transformed)
                    seeds.push_back(s);
                q.pop();
            }
        }
        else if (!isdigit(line[0]))
        {
            mappings.clear();
        }
        else
        {
            vector<ll> range = split(line, ' ');
            mappings.push_back(range);
        }
    }
    sort(seeds.begin(), seeds.end());
    ans = seeds[0].first;
    for (auto itr : seeds)
    {
        cout << itr.first << ',' << itr.second << ';';
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