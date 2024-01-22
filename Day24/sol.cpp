// -*- C++ -*-
// g++ -std=c++17 -o sol -I eigen-3.4.0 sol.cpp
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
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/LU>
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

struct Path
{
    vector<double> pos;
    vector<double> vel;
    Path(vector<double> pos, vector<double> vel) : pos(pos), vel(vel) {}
};

bool isFuture(double xf, double yf, double xp, double yp, double vx, double vy)
{
    bool validx = vx < 0 ? xf < xp : xf > xp;
    bool validy = vy < 0 ? yf < yp : yf > yp;

    return validx & validy;
}

bool check(Path path1, Path path2, double min_pos, double max_pos)
{

    vector<double> pos1 = path1.pos, pos2 = path2.pos, vel1 = path1.vel, vel2 = path2.vel;
    double x1 = pos1[0], x2 = pos2[0], y1 = pos1[1], y2 = pos2[1];
    double vx1 = vel1[0], vx2 = vel2[0], vy1 = vel1[1], vy2 = vel2[1];

    // y = mx + c
    double m1 = vy1 / vx1, m2 = vy2 / vx2; // m =  dy/dx
    double c1 = y1 - m1 * x1, c2 = y2 - m2 * x2;

    if (m1 == m2)
    {
        if (c1 != c2) // parallel but not on the same line
            return false;
        else // check if can catch up
        {
            if (vx1 < vx2)
                return x1 > x2;
            else if (vx1 > vx2)
                return x1 < x2;
            else // same speed
                return false;
        }
    }

    // m1x + c1 = y
    // m2x + c2 = y
    // solve simultaneous equations
    double x = (c2 - c1) / (m1 - m2);
    double y = m1 * x + c1;
    bool within = (min_pos <= x && x <= max_pos) && (min_pos <= y && y <= max_pos);

    // cout << x1 << ',' << y1 << ';' << x2 << ',' << y2 << endl;
    // cout << m1 << ',' << c1 << ';' << m2 << ',' << c2 << endl;
    // cout << x << ',' << y << ' ' << within << endl;
    // cout << endl;

    // check if is future path
    bool future1 = isFuture(x, y, x1, y1, vx1, vy1);
    bool future2 = isFuture(x, y, x2, y2, vx2, vy2);

    return within & future1 & future2;
}

void part1()
{
    auto lines = read();
    int ans = 0;

    vector<Path> paths;

    for (auto line : lines)
    {
        int idx = line.find('@');
        vector<double> pos = split<double>(line.substr(0, idx - 1), ',');
        vector<double> vel = split<double>(line.substr(idx + 1), ',');
        // cout << (ll)pos[0] << ' ' << (ll)pos[1] << endl;

        paths.push_back(Path(pos, vel));
    }

    double min_pos = 200000000000000;
    double max_pos = 400000000000000;
    for (int i = 0; i < paths.size(); i++)
    {
        for (int j = i + 1; j < paths.size(); j++)
        {
            if (check(paths[i], paths[j], min_pos, max_pos))
                ans++;
        }
    }

    cout << ans << endl;
}

void part2()
{
    auto lines = read();

    vector<Path> paths;

    for (auto line : lines)
    {
        int idx = line.find('@');
        vector<double> pos = split<double>(line.substr(0, idx - 1), ',');
        vector<double> vel = split<double>(line.substr(idx + 1), ',');
        paths.push_back(Path(pos, vel));
    }

    // pxr + t0vxr = px0 + t0vx0
    // pyr + t0vyr = py0 + t0vy0
    // t0 = (pxr - px0) / (vx0 - vxr)
    // t0 = (pyr - py0) / (vy0 - vyr)
    // (pxr - px0) * (vy0 - vyr) = (pyr - py0) * (vx0 - vxr)
    // pxr*vy0 - pxr*vyr - px0*vy0 + px0*vyr = pyr*vx0 - pyr*vxr - py0*vx0 + py0*vxr
    // (pxr - px1) * (vy1 - vyr) = (pyr - py1) * (vx1 - vxr)
    // pxr*vy1 - pxr*vyr - px1*vy1 + px1*vyr = pyr*vx1 - pyr*vxr - py1*vx1 + py1*vxr
    // pxr(vy0-vy1) + vyr(px0-px1) - px0*vy0 + px1*vy1 = pyr(vx0-vx1) + vxr(py0 - py1) - py0*vx0 + py1*vx1
    // pxr(vy0-vy1) + pyr(vx1-vx0) + vxr(py1-py0) + vyr(px0-px1) =  px0*vy0 - py0*vx0 + py1*vx1 - px1*vy1

    // Alternatively
    // p0 + t[i]*v0 == p[i] + t[i]*v[i] for every i, and so (p0 - p[i]) x (v0 - v[i]) == 0.

    Eigen::Matrix<long double, 4, 4> A(4, 4);
    Eigen::Vector<long double, 4> b(4);

    // use 4 pair of hailstones (8) to generate 4 set of equations
    long double c1, c2, c3, c4, rhs;
    for (int i = 0; i < 4; i++)
    {
        Path p1 = paths[0], p2 = paths[i + 1];
        c1 = p1.vel[1] - p2.vel[1];
        c2 = p2.vel[0] - p1.vel[0];
        c3 = p2.pos[1] - p1.pos[1];
        c4 = p1.pos[0] - p2.pos[0];
        rhs = p1.pos[0] * p1.vel[1] - p1.pos[1] * p1.vel[0] + p2.pos[1] * p2.vel[0] - p2.pos[0] * p2.vel[1];

        Eigen::Vector<long double, 4> row(c1, c2, c3, c4);
        A.row(i) = row;
        b(i) = rhs;
    }

    cout << A << endl;
    cout << b << endl;

    Eigen::Vector<long double, 4> sol = A.colPivHouseholderQr().solve(b);

    long double pxr = sol(0);
    long double pyr = sol(1);
    long double vxr = sol(2);

    // (pxr - px0) / (vx0 - vxr) = (pzr - pz0) / (vz0 - vzr) = t0 => pzr = t0*vz0 + pz0 - t0*vzr
    // (pxr - px1) / (vx1 - vxr) = (pzr - pz1) / (vz1 - vzr) = t1 => pzr = t1*vz1 + pz1 - t1*vzr
    long double t0 = (pxr - paths[0].pos[0]) / (paths[0].vel[0] - vxr);
    long double t1 = (pxr - paths[1].pos[0]) / (paths[1].vel[0] - vxr);

    long double vz0 = paths[0].vel[2], vz1 = paths[1].vel[2], pz0 = paths[0].pos[2], pz1 = paths[1].pos[2];
    long double vzr = (t0 * vz0 + pz0 - t1 * vz1 - pz1) / (t0 - t1);
    long double pzr = t0 * vz0 + pz0 - t0 * vzr;

    std::cout.unsetf(std::ios::floatfield);
    std::cout.precision(20);

    cout << pxr << ' ' << pyr << ' ' << pzr << endl;

    long double ans = round(pxr) + round(pyr) + round(pzr);

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