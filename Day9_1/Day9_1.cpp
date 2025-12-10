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
    int64_t m = 0;
    for (int i = 0; i < js.size(); ++i) {
        for (int k = i + 1; k < js.size(); ++k) {
            const int64_t x = js[i].x - js[k].x + 1;
            const int64_t y = js[i].y - js[k].y + 1;
            const int64_t r = x * y;
            if (m < r) {
                m = r;
            }
        }
    }
    std::cout << m << std::endl;
    return 0;
}
