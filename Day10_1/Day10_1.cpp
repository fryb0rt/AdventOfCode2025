#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main()
{
    std::ifstream stream("..\\input10.txt");
    std::string line;
    int64_t sum = 0;
    while (std::getline(stream, line)) {
        auto p1 = line.find_first_of(']');
        unsigned int current = 0;
        for (int i = 1; i < p1; ++i) {
            unsigned int val = line[i] == '.' ? 0 : 1;
            current |= val << (i - 1);
        }
        p1 = line.find_first_of('(');
        auto p2 = line.find_first_of('{');
        auto s = line.substr(p1 + 1, p2 - p1 - 1);
        size_t i = 0, l;
        std::vector<std::vector<int>> switches;
        do {
            i = s.find_first_of(')', 0);
            auto s2 = s.substr(0, i);
            std::istringstream iss(s2);
            std::vector<int> sw;
            do {
                int num;
                char c;
                iss >> num;
                sw.push_back(num);
                iss >> c;
            } while (iss);
            switches.push_back(sw);
            l = s.find_first_of('(', 0);
            s = s.substr(l+1);
        } while (l != std::string::npos);
        
        std::unordered_map<unsigned int, int> table;
        struct S{
            unsigned int v;
            unsigned int steps;
        };
        std::vector<S> stack;
        stack.push_back(S{ 0,0 });
        table.insert({ current, 10000000 });
        while (!stack.empty()) {
            S s = stack.back();
            stack.pop_back();
            ++s.steps;
            if (s.steps >= table[current]) {
                continue;
            }
            for (const auto& v : switches) {
                S s2 = s;
                for (int i : v) {
                    s2.v ^= 1 << i;
                }auto it = table.find(s2.v);
                if (it == table.end() || it->second > s2.steps) {
                    table[s2.v] = s2.steps;
                    stack.push_back(s2);
                }
            }
        }
        sum += table[current];
    }
   
    std::cout << sum << std::endl;
    return 0;
}
