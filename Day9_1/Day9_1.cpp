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
            p.dist = x * y;
            ps.push_back(p);
        }
    }
    std::sort(ps.begin(), ps.end());
    std::cout << ps.back().dist << std::endl;
    return 0;
}
