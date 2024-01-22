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

class Rule
{
public:
    string rating;
    string op;
    int val;
    string part;

    Rule(string part, string rating = "", string op = "", int val = 0) : rating(rating), op(op), val(int(val)), part(part) {}

    friend ostream &operator<<(ostream &os, const Rule &obj)
    {
        os << "rating: " << obj.rating << ", op: " << obj.op << ", val: " << obj.val << ", part: " << obj.part;
        return os;
    }

    string run(map<string, int> m)
    {
        if (rating.length() == 0)
            return part;

        bool ok = (op == ">") ? m[rating] > val : m[rating] < val;
        if (ok)
            return part;
        else
            return "";
    }
};

void part1()
{
    auto lines = read();
    int ans = 0;
    map<string, vector<Rule>> rulemap;

    int start;
    for (int i = 0; i < lines.size(); i++)
    {
        string line = lines[i];
        if (line.length() == 0)
        {
            start = i + 1;
            break;
        }
        int idx = line.find('{');
        string key = line.substr(0, idx);
        string rem = line.substr(idx + 1);
        vector<string> strs = split_into_str(rem, ',');
        vector<Rule> rules;
        for (auto s : strs)
        {
            int i = s.find(':');
            if (i != string::npos)
            {
                string next_part = s.substr(i + 1);
                string rating = string(1, s[0]);
                string op = string(1, s[1]);
                int val = stoi(s.substr(2, i - 2));
                rules.push_back(Rule(next_part, rating, op, val));
            }
            else
            {
                rules.push_back(Rule(s.substr(0, s.length() - 1)));
            }
        }
        rulemap[key] = rules;
    }

    for (int i = start; i < lines.size(); i++)
    {
        string line = lines[i];
        vector<string> ratings = split_into_str(line.substr(1, line.length() - 2), ',');
        map<string, int> ratingmap;
        int tot = 0;
        for (auto r : ratings)
        {
            string p = string(1, r[0]);
            int v = stoi(r.substr(2));
            ratingmap[p] = v;
            tot += v;
        }

        string cur = "in";
        while (true)
        {
            if (cur == "A" || cur == "R")
                break;
            for (Rule r : rulemap[cur])
            {
                string res = r.run(ratingmap);
                if (res.length() != 0)
                {
                    cur = res;
                    break;
                }
            }
        }
        if (cur == "A")
            ans += tot;
    }

    cout << ans << endl;
}

ll count_combi(map<string, pair<int, int>> m)
{
    ll cnt = 1;
    for (const auto &[k, v] : m)
    {
        cnt *= (v.second - v.first + 1);
    }
    return cnt;
}

void part2()
{
    auto lines = read();
    ll ans = 0;
    map<string, vector<Rule>> rulemap;

    for (auto line : lines)
    {
        if (line.length() == 0)
            break;
        int idx = line.find('{');
        string key = line.substr(0, idx);
        string rem = line.substr(idx + 1);
        vector<string> strs = split_into_str(rem, ',');
        vector<Rule> rules;
        for (auto s : strs)
        {
            int i = s.find(':');
            if (i != string::npos)
            {
                string next_part = s.substr(i + 1);
                string rating = string(1, s[0]);
                string op = string(1, s[1]);
                int val = stoi(s.substr(2, i - 2));
                rules.push_back(Rule(next_part, rating, op, val));
            }
            else
            {
                rules.push_back(Rule(s.substr(0, s.length() - 1)));
            }
        }
        rulemap[key] = rules;
    }

    map<string, pair<int, int>> ratingmap;
    for (string s : {"x", "m", "a", "s"})
    {
        ratingmap[s] = {1, 4000};
    }
    queue<tuple<string, map<string, pair<int, int>>>> q;
    q.push({"in", ratingmap});

    while (!q.empty())
    {
        tuple<string, map<string, pair<int, int>>> t = q.front();
        q.pop();
        string curpart = get<0>(t);
        vector<Rule> rules = rulemap[get<0>(t)];
        map<string, pair<int, int>> newmap = get<1>(t); // make a new copy

        for (Rule r : rules)
        {
            string next_part = r.part;
            string rating = r.rating;
            string op = r.op;
            int val = r.val;
            if (op == "<")
            {
                if (newmap[rating].second < val)
                {
                    if (next_part == "A")
                        ans += count_combi(newmap);
                    else if (next_part == "R")
                    {
                    }
                    else
                        q.push({next_part, newmap});
                    break;
                }
                else if (newmap[rating].first < val)
                {
                    map<string, pair<int, int>> newmap2 = newmap;
                    newmap[rating].second = val - 1;
                    newmap2[rating].first = val;
                    q.push({curpart, newmap});
                    q.push({curpart, newmap2});
                    break;
                }
                // otherwise out of range and move on to the next rule
            }
            else if (op == ">")
            {
                if (newmap[rating].first > val)
                {
                    if (next_part == "A")
                        ans += count_combi(newmap);
                    else if (next_part == "R")
                    {
                    }
                    else
                        q.push({next_part, newmap});
                    break;
                }
                else if (newmap[rating].second > val)
                {
                    map<string, pair<int, int>> newmap2 = newmap;
                    newmap[rating].first = val + 1;
                    newmap2[rating].second = val;
                    q.push({curpart, newmap});
                    q.push({curpart, newmap2});
                    break;
                }
                // otherwise out of range and move on to the next rule
            }
            else
            {
                if (next_part == "A")
                {
                    ans += count_combi(newmap);
                }
                else if (next_part == "R")
                {
                }
                else
                {
                    q.push({next_part, newmap});
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