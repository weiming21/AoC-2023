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

void bfs(map<string, vector<string>> g, map<string, char> module, map<string, int> &state, map<string, map<string, int>> &pulses, ll &low, ll &high)
{
    queue<tuple<string, string, int>> q; // cur, parent, pulse
    q.push({"broadcaster", "button", 0});
    low++;

    while (!q.empty())
    {
        tuple<string, string, int> cur = q.front();
        q.pop();
        string name = get<0>(cur);
        string parent = get<1>(cur);
        int p = get<2>(cur);
        // cout << name << " " << parent << " " << p << endl;
        if (name == "broadcaster")
        {
        }
        else if (module[name] == '%')
        {
            if (p == 1)
                continue;
            else
            {
                p = state[name] ? 0 : 1; // on / off-> low / high
                state[name] = 1 - state[name];
            }
        }
        else
        {
            pulses[name][parent] = p;
            bool allHigh = true;
            for (auto [input, v] : pulses[name])
            {
                if (v == 0)
                {
                    allHigh = false;
                    break;
                }
            }
            p = allHigh ? 0 : 1;
        }

        for (auto neigh : g[name])
        {
            q.push({neigh, name, p});
            if (p)
                high++;
            else
                low++;
        }
        // cout << low << "," << high << endl;
    }
};

void part1()
{
    auto lines = read();
    ll ans = 0;
    map<string, vector<string>> g;
    map<string, char> module;
    map<string, int> state;               // 0 = off, 1 = on
    map<string, map<string, int>> pulses; // 0 = low, 1 = high

    for (auto line : lines)
    {
        int idx = line.find('-');
        string key = line.substr(0, idx - 1);
        string rem = line.substr(idx + 2);
        vector<string> vals = split_into_str(rem, ',');
        if (key != "broadcaster")
        {
            char pre = key[0];
            key = key.substr(1);
            module[key] = pre;
        }
        state[key] = 0;
        for (auto v : vals)
        {
            v = v.substr(1);
            g[key].push_back(v);
            pulses[v][key] = 0;
        }
    }

    int n = 1000;
    ll low = 0, high = 0;
    for (int i = 0; i < n; i++)
    {
        bfs(g, module, state, pulses, low, high);
    }

    cout << low << ',' << high << endl;
    ans = low * high;
    cout << ans << endl;
}

void bfs_p2(map<string, vector<string>> g, map<string, char> module, map<string, int> &state, map<string, map<string, int>> &pulses, int cur_cycle, vector<string> &targets, vector<int> &cycles)
{
    queue<tuple<string, string, int>> q; // cur, parent, pulse
    q.push({"broadcaster", "button", 0});

    while (!q.empty())
    {
        tuple<string, string, int> cur = q.front();
        q.pop();
        string name = get<0>(cur);
        string parent = get<1>(cur);
        int p = get<2>(cur);

        // cout << name << " " << parent << " " << p << endl;
        if (name == "broadcaster")
        {
        }
        else if (module[name] == '%')
        {
            if (p == 1)
                continue;
            else
            {
                p = state[name] ? 0 : 1; // on / off-> low / high
                state[name] = 1 - state[name];
            }
        }
        else
        {
            pulses[name][parent] = p;
            bool allHigh = true;
            for (auto [input, v] : pulses[name])
            {
                if (v == 0)
                {
                    allHigh = false;
                    break;
                }
            }
            p = allHigh ? 0 : 1;
        }

        auto it = find(targets.begin(), targets.end(), name);
        if ((it != targets.end()) & (p == 1))
        {
            cycles.push_back(cur_cycle);
            targets.erase(it);
        }
        if (targets.size() == 0)
            break;

        for (auto neigh : g[name])
        {
            q.push({neigh, name, p});
        }
        // cout << low << "," << high << endl;
    }
};

void part2()
{
    auto lines = read();
    ll ans = 1;
    map<string, vector<string>> g;
    map<string, char> module;
    map<string, int> state;               // 0 = off, 1 = on
    map<string, map<string, int>> pulses; // 0 = low, 1 = high
    string final = "rg";                  // the module leading to "rx";
    vector<string> semi_final;            // the modules leading to "rg";

    for (auto line : lines)
    {
        int idx = line.find('-');
        string key = line.substr(0, idx - 1);
        string rem = line.substr(idx + 2);
        vector<string> vals = split_into_str(rem, ',');
        if (key != "broadcaster")
        {
            char pre = key[0];
            key = key.substr(1);
            module[key] = pre;
        }
        state[key] = 0;
        for (auto v : vals)
        {
            v = v.substr(1);
            g[key].push_back(v);
            pulses[v][key] = 0;
            if (v == final)
                semi_final.push_back(key);
        }
    }

    vector<int> cycles;
    ll n = 0;
    while (true)
    {
        n++;
        bfs_p2(g, module, state, pulses, n, semi_final, cycles);
        if (semi_final.size() == 0)
            break;
    }

    for (auto itr : cycles)
    {
        ans = lcm(ans, itr);
    }

    // cout << n << endl;
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