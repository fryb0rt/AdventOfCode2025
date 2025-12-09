#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream stream("..\\input9.txt");
    std::string line;
    struct J {
        int64_t x, y;
    };

    std::vector<J> js;
    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        J j;
        char c;
        iss >> j.x >> c >> j.y;
        js.push_back(j);
    }
    const auto dir = [&](int i, int j) {
        const auto& a = js[i];
        const auto& b = js[j];
        if (a.x < b.x) {
            return 0;
        }
        if (a.y < b.y) {
            return 1;
        }
        if (a.x > b.x) {
            return 2;
        }
        if (a.y > b.y) {
            return 3;
        }
        };
    struct Box {
        int64_t minX, minY, maxX, maxY;
    };
    std::vector<Box> boxes;
    J prevCorner;
    for (int i = 0; i <= js.size(); ++i) {
        int a = i;
        int b = (i + 1) % js.size();
        int c = (i + 2) % js.size();
        int d = (i + 3) % js.size();
        int dirAB = dir(a, b);
        int dirBC = dir(b, c);
        int dirCD = dir(c, d);

    };
    
    const auto test = [&](int i, int j) {
        int min = std::min(i, j);
        int max = std::max(i, j);
        int x = js[min].x, y = js[min].y;
        int prevPrev= - 1, prev = min;
        for (int i = min; i <= max; ++i) {
            int d = dir()
            
        };
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
            const int64_t x = js[i].x - js[k].x + 1;
            const int64_t y = js[i].y - js[k].y + 1;
            if (test(i, k)) {
                p.dist = x * y;
                ps.push_back(p);
            }
        }
    }
    std::sort(ps.begin(), ps.end());
    std::cout << ps.back().dist << std::endl;
    return 0;
}
