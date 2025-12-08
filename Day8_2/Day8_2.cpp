#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream stream("..\\input8.txt");
    std::string line;
    struct J {
        int64_t x, y, z;
        int c = -1;
    };

    std::vector<J> js;
    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        J j;
        char c;
        iss >> j.x >> c >> j.y >> c >> j.z;
        js.push_back(j);
    }
    struct P {
        int i, j;
        int64_t dist;
        bool operator<(const P& p) const {
            return dist < p.dist;
        }
    };
    std::vector<P> ps;
    for (int i = 0; i < js.size(); ++i) {
        for (int k = i + 1; k < js.size(); ++k) {
            P p;
            p.i = i;
            p.j = k;
            const int64_t x = js[i].x - js[k].x;
            const int64_t y = js[i].y - js[k].y;
            const int64_t z = js[i].z - js[k].z;
            p.dist = x * x + y * y + z * z;
            ps.push_back(p);
        }
    }
    std::sort(ps.begin(), ps.end());
    std::vector<std::vector<int>> groups;
    int64_t result = 0;
    for (int i = 0; i < ps.size(); ++i) {
        int& group1 = js[ps[i].i].c;
        int& group2 = js[ps[i].j].c;
        int group = std::max(group1, group2);
        if (group == -1) {
            group = groups.size();
            groups.push_back({});
            group1 = group;
            group2 = group;
            groups[group].push_back(ps[i].i);
            groups[group].push_back(ps[i].j);
        }
        else if (group1 != group2) {
            int maxGroup = std::min(group1, group2);
            if (maxGroup != -1) {
                for (int j : groups[maxGroup]) {
                    js[j].c = group;
                    groups[group].push_back(j);
                }
                groups[maxGroup].clear();
            }
            else {
                if (group1 == -1) {
                    group1 = group;
                    groups[group].push_back(ps[i].i);
                }
                else {
                    group2 = group;
                    groups[group].push_back(ps[i].j);
                }
            }
        }
        // Equal - nothing
        if (groups[group].size() == js.size()) {
            result = js[ps[i].i].x * js[ps[i].j].x;
            break;
        }
    }
    std::cout << result << std::endl;
    return 0;
}
