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
        int x, y;
    };

    std::vector<J> js;
    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        J j;
        char c;
        iss >> j.x >> c >> j.y;
        js.push_back(j);
    }
    
    int minX = 1000000, minY = 1000000, maxX =- 1000000, maxY= -1000000;
    for (auto j : js) {
        minX = std::min(minX, j.x);
        minY = std::min(minY, j.y);
        maxX = std::max(maxX, j.x);
        maxY = std::max(maxY, j.y);
    }
    struct Line {
        int minX, minY, maxX, maxY;
    };
    std::vector<Line> lines;
    for (int i = 0; i < js.size(); ++i) {
        J j = js[i];
        J j = js[i % js.size()];
        Line l;
        l.minX = std::min(minX, j.x);
        l.minY = std::min(minY, j.y);
        l.maxX = std::max(maxX, j.x);
        l.maxY = std::max(maxY, j.y);
        lines.push_back()
    }
    std::sort(js.begin(), js.end());
    struct I {
        int minY, maxY;
    };
    std::vector<std::vector<I>> field(maxX - minX + 1);
    for (int i = 0; i < field.size(); ++i) {
        int x = minX + i;
        for (const auto& j : js) {
            if (j.x >= x )
        }
    }
    std::vector<J> stack;
    stack.push_back(js[0]);
    while (stack.empty()) {
        J j = stack.back();

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
            int64_t y = js[i].y - js[k].y + 1;
                p.dist = x * y;
                ps.push_back(p);
        }
    }
    std::sort(ps.begin(), ps.end());
    std::cout << ps.back().dist << std::endl;
    return 0;
}
