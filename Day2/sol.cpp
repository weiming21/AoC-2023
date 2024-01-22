// -*- C++ -*-
// g++ -std=c++17 -o sol sol.cpp
// ./sol 1 < input.txt  # part 1
// ./sol 2 < input.txt  # part 2

#include <iostream>
#include <cstdio>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>
#include <unordered_map>

using namespace std;

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
    auto values = read();
    int ans = 0;
    unordered_map<string, int> m{{"red", 12}, {"green", 13}, {"blue", 14}};

    for (auto val : values)
    {
        bool valid = true;
        string delimiter = ":";
        int i = val.find(delimiter) + 2;
        while (i < val.length())
        {
            string count = "";
            while (isdigit(val[i]))
            {
                count += val[i++];
            }

            i++; // skip the space

            for (int l = 3; l <= 5; l++)
            {
                string color = val.substr(i, l);
                if (m.count(color) != 0)
                {
                    if (m[color] < stoi(count))
                    {
                        valid = false;
                    }
                    i += l;
                    break;
                }
            }
            if (!valid)
                break;
        }
        if (valid)
        {
            string id = "";
            for (int j = 5; j < i; j++)
            {
                id += val[j];
            }
            ans += stoi(id);
        }
    }
    cout << ans << endl;
}

void part2()
{
    auto values = read();
    int ans = 0;

    for (auto val : values)
    {
        unordered_map<string, int> m{{"red", 0}, {"green", 0}, {"blue", 0}};
        string delimiter = ":";
        int i = val.find(delimiter) + 2;
        while (i < val.length())
        {
            string count = "";
            while (isdigit(val[i]))
            {
                count += val[i++];
            }

            i++; // skip the space

            for (int l = 3; l <= 5; l++)
            {
                string color = val.substr(i, l);
                if (m.find(color) != m.end())
                {
                    m[color] = max(m[color], stoi(count));
                    break;
                }
            }
        }
        int power = 1;
        for (auto const &[k, v] : m)
        {
            power *= v;
        }
        ans += power;
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