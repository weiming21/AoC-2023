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

struct Brick
{
    pair<int, int> x;
    pair<int, int> y;
    pair<int, int> z;
    Brick(pair<int, int> x, pair<int, int> y, pair<int, int> z) : x(x), y(y), z(z) {}
};

bool compareBrick(Brick b1, Brick b2)
{
    return b1.z.first < b2.z.first;
}

void part1()
{
    auto lines = read();
    int ans = 0;

    vector<Brick> bricks;

    for (int i = 0; i < lines.size(); i++)
    {
        string line = lines[i];
        int cut = line.find('~');
        vector<int> s = split_into_int(line.substr(0, cut), ',');
        vector<int> e = split_into_int(line.substr(cut + 1), ',');

        Brick b = Brick({s[0], e[0]}, {s[1], e[1]}, {s[2], e[2]});
        bricks.push_back(b);
    }

    sort(bricks.begin(), bricks.end(), compareBrick);
    map<pair<int, int>, pair<int, int>> m; // stores the highest z and brick at (x,y)
    set<int> bad;                          // bricks that cannot be removed

    for (int i = 0; i < bricks.size(); i++)
    {
        Brick b = bricks[i];

        int highest = 0;
        set<int> support;
        for (int x = b.x.first; x <= b.x.second; x++)
        {
            for (int y = b.y.first; y <= b.y.second; y++)
            {
                if (!m.count({x, y})) // ground floor
                {
                    continue;
                }
                int curh = m[{x, y}].first;
                int bb = m[{x, y}].second; // brick below
                if (curh > highest)
                {
                    highest = curh;
                    support.clear();
                    support.insert(bb);
                }
                else if (curh == highest)
                {
                    support.insert(bb);
                }
            }
        }

        if (support.size() == 1)
        {
            int s = *support.begin();
            bad.insert(s);
        }

        int newh = highest + b.z.second - b.z.first + 1;
        for (int x = b.x.first; x <= b.x.second; x++)
        {
            for (int y = b.y.first; y <= b.y.second; y++)
            {
                m[{x, y}] = {newh, i};
            }
        }
    }

    ans = bricks.size() - bad.size();
    cout << ans << endl;
}

void part2()
{
    auto lines = read();
    int ans = 0;

    vector<Brick> bricks;

    for (int i = 0; i < lines.size(); i++)
    {
        string line = lines[i];
        int cut = line.find('~');
        vector<int> s = split_into_int(line.substr(0, cut), ',');
        vector<int> e = split_into_int(line.substr(cut + 1), ',');

        Brick b = Brick({s[0], e[0]}, {s[1], e[1]}, {s[2], e[2]});
        bricks.push_back(b);
    }

    sort(bricks.begin(), bricks.end(), compareBrick);
    map<pair<int, int>, pair<int, int>> m; // stores the highest z and brick at (x,y)
    set<int> bad;                          // bricks that cannot be removed
    map<int, set<int>> supporting;         // list of bricks being supported by each brick

    for (int i = 0; i < bricks.size(); i++)
    {
        Brick b = bricks[i];

        int highest = 0;
        set<int> support;
        for (int x = b.x.first; x <= b.x.second; x++)
        {
            for (int y = b.y.first; y <= b.y.second; y++)
            {
                if (!m.count({x, y})) // ground floor
                {
                    continue;
                }
                int curh = m[{x, y}].first;
                int bb = m[{x, y}].second; // brick below
                if (curh > highest)
                {
                    highest = curh;
                    support.clear();
                    support.insert(bb);
                }
                else if (curh == highest)
                {
                    support.insert(bb);
                }
            }
        }

        if (support.size() == 1)
        {
            int s = *support.begin();
            bad.insert(s);
        }

        for (auto s : support)
        {
            supporting[s].insert(i);
        }

        int newh = highest + b.z.second - b.z.first + 1;
        for (int x = b.x.first; x <= b.x.second; x++)
        {
            for (int y = b.y.first; y <= b.y.second; y++)
            {
                m[{x, y}] = {newh, i};
            }
        }
    }

    // run graph algo using in-degrees (toposort logic)
    for (auto removed : bad)
    {
        map<int, int> indeg;
        for (auto const &[k, v] : supporting)
        {
            for (auto i : v)
            {
                if (!indeg.count(i))
                    indeg[i] = 0;
                indeg[i]++;
            }
        }
        int cnt = -1;
        queue<int> q;
        q.push(removed);
        set<int> counted;

        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            cnt++;
            for (auto supported : supporting[cur])
            {
                indeg[supported]--;
                if (indeg[supported] <= 0)
                {
                    if (!counted.count(supported))
                    {
                        q.push(supported);
                        counted.insert(supported);
                    }
                }
            }
        }
        ans += cnt;
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