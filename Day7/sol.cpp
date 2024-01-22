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

struct Hand
{
    string key;
    int value;
    Hand(string k, int v) : key(k), value(v) {}
};

vector<int> countHand(string s)
{
    unordered_map<char, int> m;
    vector<int> v{2, 0};
    int maxCount = 0;
    int maxChar;
    for (char c : s)
    {
        if (m.find(c) == m.end())
            m[c] = 0;
        m[c]++;
        if (maxCount < m[c])
        {
            maxCount = m[c];
            maxChar = c;
        }
    }
    if (maxCount == 5 || maxCount == 4 || maxCount == 1)
    {
        return {maxCount, 0};
    }
    else
    {
        int secondMax = 0;
        for (const auto &[k, v] : m)
        {
            if (k != maxChar)
                secondMax = max(secondMax, v);
        }
        return {maxCount, secondMax};
    }
}

vector<int> countHandv2(string s)
{
    unordered_map<char, int> m;
    vector<int> v{2, 0};
    int maxCount = 0;
    int maxChar;
    for (char c : s)
    {
        if (m.find(c) == m.end())
            m[c] = 0;
        m[c]++;
        if (maxCount < m[c] && c != 'J')
        {
            maxCount = m[c];
            maxChar = c;
        }
    }

    if (!m.count('J'))
        m['J'] = 0;
    if (maxCount == 5 || maxCount == 4 || maxCount == 1)
    {
        return {maxCount + m['J'], 0};
    }
    else
    {
        int secondMax = 0;
        for (const auto &[k, v] : m)
        {
            if (k != maxChar && k != 'J')
                secondMax = max(secondMax, v);
        }
        if (secondMax == 1)
            secondMax = 0;
        if (maxCount + m['J'] >= 4)
            return {maxCount + m['J'], 0};
        return {maxCount + m['J'], secondMax};
    }
}

bool compareChar(string s1, string s2)
{
    unordered_map<char, int> rank{{'A', 14}, {'K', 13}, {'Q', 12}, {'J', 11}, {'T', 10}};
    for (int i = 0; i < s1.length(); i++)
    {
        char c1 = s1[i];
        char c2 = s2[i];
        int r1 = isdigit(c1) ? c1 - '0' : rank[c1];
        int r2 = isdigit(c2) ? c2 - '0' : rank[c2];
        if (r2 > r1)
            return true;
        else if (r1 > r2)
            return false;
    }
    return false;
}

bool compareCharv2(string s1, string s2)
{
    unordered_map<char, int> rank{{'A', 14}, {'K', 13}, {'Q', 12}, {'J', 0}, {'T', 10}};
    for (int i = 0; i < s1.length(); i++)
    {
        char c1 = s1[i];
        char c2 = s2[i];
        int r1 = isdigit(c1) ? c1 - '0' : rank[c1];
        int r2 = isdigit(c2) ? c2 - '0' : rank[c2];
        if (r2 > r1)
            return true;
        else if (r1 > r2)
            return false;
    }
    return false;
}

bool compareHand(Hand h1, Hand h2)
{
    vector<int> v1 = countHand(h1.key);
    vector<int> v2 = countHand(h2.key);

    if (v1[0] == v2[0])
    {
        if (v1[1] == v2[1])
        {
            return compareChar(h1.key, h2.key);
        }
        return v1[1] < v2[1];
    }
    return v1[0] < v2[0];
}

bool compareHandv2(Hand h1, Hand h2)
{
    vector<int> v1 = countHandv2(h1.key);
    vector<int> v2 = countHandv2(h2.key);

    if (v1[0] == v2[0])
    {
        if (v1[1] == v2[1])
        {
            return compareCharv2(h1.key, h2.key);
        }
        return v1[1] < v2[1];
    }
    return v1[0] < v2[0];
}

void part1()
{
    auto lines = read();
    int ans = 0;
    vector<Hand> hands;
    for (auto line : lines)
    {
        vector<string> temp = split(line, ' ');
        hands.push_back(Hand(temp[0], stoi(temp[1])));
    }
    sort(hands.begin(), hands.end(), compareHand);
    for (int i = 1; i <= hands.size(); i++)
    {
        ans += i * hands[i - 1].value;
    }
    cout << ans << endl;
}

void part2()
{
    auto lines = read();
    int ans = 0;
    vector<Hand> hands;
    for (auto line : lines)
    {
        vector<string> temp = split(line, ' ');
        hands.push_back(Hand(temp[0], stoi(temp[1])));
    }
    sort(hands.begin(), hands.end(), compareHandv2);
    for (int i = 1; i <= hands.size(); i++)
    {
        ans += i * hands[i - 1].value;
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