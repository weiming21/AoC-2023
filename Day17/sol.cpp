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

class Path
{
public:
    pair<int, int> coord;
    int dir;
    int count; // steps
    int cost;  // accumulated cost till cur step

    Path(pair<int, int> coord, int dir, int count, int cost) : coord(coord),
                                                               dir(dir),
                                                               count(count),
                                                               cost(cost) {}

    bool operator<(const Path &other) const
    {
        return tie(coord, dir, count) < tie(other.coord, other.dir, other.count);
    }
    bool operator==(const Path &other) const
    {
        return tie(coord, dir, count) == tie(other.coord, other.dir, other.count);
    }
};

class Compare
{
public:
    bool operator()(Path a, Path b)
    {
        return a.cost > b.cost;
    }
};

void part1()
{
    auto mat = read();
    int ans = numeric_limits<double>::infinity();

    int m = mat.size(), n = mat[0].size();
    map<Path, int> costmap;
    priority_queue<Path, vector<Path>, Compare> pq;
    // 0: left, 1: right, 2: up, 3: down
    map<int, pair<int, int>> dirmap{
        {0, {0, -1}}, {1, {0, 1}}, {2, {-1, 0}}, {3, {1, 0}}};
    pq.push(Path({0, 0}, 1, 0, 0));

    // Dijkstra
    while (!pq.empty())
    {
        Path cur = pq.top();
        pq.pop();
        pair<int, int> coord = cur.coord;
        int r = coord.first, c = coord.second;

        if (r == m - 1 && c == n - 1)
            ans = min(ans, costmap[cur]);

        vector<int> next_dir;
        if (cur.dir == 0 || cur.dir == 1)
        {
            next_dir = {2, 3};
        }
        else
        {
            next_dir = {0, 1};
        }
        if (cur.count < 3)
            next_dir.push_back(cur.dir);

        int rn, cn;
        pair<int, int> move;
        int new_count;
        for (int d : next_dir)
        {
            move = dirmap[d];
            rn = r + move.first, cn = c + move.second;
            new_count = d == cur.dir ? cur.count + 1 : 1;
            if (!(0 <= rn && rn < m && 0 <= cn && cn < n))
                continue;
            int new_cost = cur.cost + (mat[rn][cn] - '0');
            Path new_path = Path({rn, cn}, d, new_count, new_cost);
            if (!costmap.count(new_path) || (costmap.count(new_path) && costmap[cur] > new_cost))
            {
                costmap[new_path] = new_cost;
                pq.push(new_path);
            }
        }
    }

    cout << ans << endl;
}

void part2()
{
    auto mat = read();
    int ans = numeric_limits<double>::infinity();

    int m = mat.size(), n = mat[0].size();
    map<Path, int> costmap;
    priority_queue<Path, vector<Path>, Compare> pq;
    // 0: left, 1: right, 2: up, 3: down
    map<int, pair<int, int>> dirmap{
        {0, {0, -1}}, {1, {0, 1}}, {2, {-1, 0}}, {3, {1, 0}}};
    pq.push(Path({0, 0}, 1, 0, 0));

    // Dijkstra
    while (!pq.empty())
    {
        Path cur = pq.top();
        pq.pop();
        pair<int, int> coord = cur.coord;
        int r = coord.first, c = coord.second;

        if (r == m - 1 && c == n - 1 && cur.count >= 4)
            ans = min(ans, costmap[cur]);

        vector<int> next_dir;
        if (cur.count >= 4 || (r == 0 && c == 0))
        {
            if (cur.dir == 0 || cur.dir == 1)
            {
                next_dir = {2, 3};
            }
            else
            {
                next_dir = {0, 1};
            }
        }
        if (cur.count < 10)
            next_dir.push_back(cur.dir);

        int rn, cn;
        pair<int, int> move;
        int new_count;
        for (int d : next_dir)
        {
            move = dirmap[d];
            rn = r + move.first, cn = c + move.second;
            new_count = d == cur.dir ? cur.count + 1 : 1;
            if (!(0 <= rn && rn < m && 0 <= cn && cn < n))
                continue;
            int new_cost = cur.cost + (mat[rn][cn] - '0');
            Path new_path = Path({rn, cn}, d, new_count, new_cost);
            if (!costmap.count(new_path) || (costmap.count(new_path) && costmap[new_path] > new_cost))
            {
                costmap[new_path] = new_cost;
                pq.push(new_path);
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