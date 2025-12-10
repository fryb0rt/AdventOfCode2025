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
    struct Line {
        int x1, y1, x2, y2;
    };
    std::vector<Line> linesX, linesY;
    for (int i = 0; i < js.size(); ++i) {
        J a = js[i];
        J b = js[(i + 1) % js.size()];
        Line l;
        l.x1 = a.x;
        l.y1 = a.y;
        l.x2 = b.x;
        l.y2 = b.y;
        if (l.y1 != l.y2) {
            if (l.y1 > l.y2) {
                std::swap(l.x1, l.x2);
                std::swap(l.y1, l.y2);
            }
            linesY.push_back(l);
        }
        if (l.x1 != l.x2) {
            if (l.x1 > l.x2) {
                std::swap(l.x1, l.x2);
                std::swap(l.y1, l.y2);
            }
            linesX.push_back(l);
        }
    }
    int64_t m = 0;
    for (int i = 0; i < js.size(); ++i) {
        for (int k = i + 1; k < js.size(); ++k) {
            int minX = std::min(js[i].x, js[k].x);
            int maxX = std::max(js[i].x, js[k].x);
            int minY = std::min(js[i].y, js[k].y);
            int maxY = std::max(js[i].y, js[k].y);
            int64_t r = (maxX - minX + 1) * (maxY - minY + 1);
            if (minX == maxX || minY == maxY) {
                continue;
            }
            for (J& j : js) {
                if (j.x > minX && j.x < maxX && j.y > minY && j.y < maxY) {
                    r = -1;
                    break;
                }
            }
            for (Line& line : linesX) {
                if (line.x1 <= minX && line.x2 >= maxX && line.y1 > minY && line.y1 < maxY) {
                    r = -1;
                    break;
                }
            }
            for (Line& line : linesY) {
                if (line.y1 <= minY && line.y2 >= maxY && line.x1 > minX && line.x1 < maxX) {
                    r = -1;
                    break;
                }
            }
            int cnt = 1;
            float sx = (maxX + minX) / 2.f;
            float sy = (maxY + minY) / 2.f;
            cnt = 0;
            for (Line& line : linesY) {
                if (float(line.y1) <= sy && sy <= float(line.y2)) {
                    if (float(line.x1) == sx)
                    {
                        r = -1;
                        break;
                    }
                    if (float(line.x1) < sx) {
                        ++cnt;
                    }
                }
            }
            if (r > m && cnt % 2 == 1)
            {
                m = r;
            }
        }
    }
    std::cout << m << std::endl;
    return 0;
}