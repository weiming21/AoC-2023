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

template <typename T>
vector<T> split(string str, char delimiter)
{
    vector<T> values;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter))
    {
        if constexpr (is_same_v<T, string>)
        {
            values.push_back(static_cast<T>(token));
        }
        else
        {
            values.push_back(static_cast<T>(stoll(token)));
        }
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

// UFDS
struct Parent
{
    string par;
    int rank;
};

string find(map<string, Parent> &parents, string s)
{
    string p = parents[s].par;
    if (s == p)
        return p;
    return find(parents, p);
}

void union_(map<string, Parent> &parents, string s1, string s2)
{
    string p1 = find(parents, s1);
    string p2 = find(parents, s2);
    if (parents[p1].rank > parents[p2].rank)
    {
        parents[p2].par = p1;
    }
    else if (parents[p1].rank < parents[p2].rank)
    {
        parents[p1].par = p2;
    }
    else
    {
        parents[p1].par = p2;
        parents[p2].rank++;
    }
}

int contract(vector<pair<string, string>> &edgelist, map<string, Parent> &parents, int V, int E)
{
    while (V > 2)
    {
        int i = rand() % E;
        string p1 = find(parents, edgelist[i].first);
        string p2 = find(parents, edgelist[i].second);

        if (p1 == p2)
            continue;
        else
        {
            V--;
            // cout << "Contracting " << p1.par << ',' << p2.par << endl;
            union_(parents, p1, p2);
        }
    }

    int cuts = 0;
    for (int i = 0; i < E; i++)
    {
        string p1 = find(parents, edgelist[i].first);
        string p2 = find(parents, edgelist[i].second);
        if (p1 != p2)
            cuts++;
    }
    return cuts;
}

// Karger's mincut algorithm
int karger(map<string, set<string>> &adjlist, vector<pair<string, string>> &edgelist)
{
    int V = adjlist.size(), E = edgelist.size();
    map<string, Parent> parents;
    for (auto const &[k, v] : adjlist)
    {
        parents[k].par = k;
        parents[k].rank = 0;
    }

    map<string, Parent> temp;
    int cuts;
    while (true)
    {
        // reset
        temp = parents;
        cuts = contract(edgelist, temp, V, E);
        cout << cuts << endl;

        if (cuts == 3)
            break;
    }

    string s = "";
    int size = 1;
    for (auto const &[k, v] : temp)
    {
        string p = find(temp, k);
        if (s.length() == 0)
        {
            s = p;
        }
        else if (s == p)
        {
            size++;
        }
    }

    cout << size << ',' << V - size << endl;
    return size * (V - size);
}

void part1()
{
    auto lines = read();
    int ans = 0;

    map<string, set<string>> adjlist;
    set<pair<string, string>> edgeset;

    for (auto line : lines)
    {
        string key = line.substr(0, 3);
        vector<string> vals = split<string>(line.substr(5), ' ');
        for (auto v : vals)
        {
            adjlist[key].insert(v);
            adjlist[v].insert(key);
            if (!edgeset.count({v, key}))
            {
                edgeset.insert({key, v});
            }
        }
    }
    vector<pair<string, string>> edgelist;
    std::copy(edgeset.begin(), edgeset.end(), back_inserter(edgelist));

    ans = karger(adjlist, edgelist);

    cout << ans << endl;
}

void part2()
{
    auto lines = read();
    int ans = 0;

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