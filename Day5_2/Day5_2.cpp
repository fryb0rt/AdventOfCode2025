#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream stream("..\\input5.txt");
    std::string line;
    int64_t sum = 0;

    struct Interval {
        int64_t a, b;
        bool operator<(const Interval& other) const {
            return a < other.a || (a == other.a && b < other.b);
        }
    };
    std::vector<Interval> intervals;
    while (std::getline(stream, line)) {
        if (line.empty()) {
            break;
        }
        int dash = line.find('-', 0);
        auto num1Str = line.substr(0, dash);
        int64_t num1 = std::stoll(num1Str);
        ++dash;
        auto num2Str = line.substr(dash);
        int64_t num2 = std::stoll(num2Str);
        Interval n{ num1, num2 };
        for (int i = 0; i < intervals.size(); ++i) {
            Interval in = intervals[i];
            if (in.a >= n.a && in.b <= n.b) {
                intervals.erase(intervals.begin() + i);
                --i;
                continue;
            }
            if (n.a >= in.a && n.b <= in.b) {
                n.a = n.b + 1;
                break;
            }
            if (n.a <= in.b && n.b > in.b) {
                n.a = in.a;
                intervals.erase(intervals.begin() + i);
                --i;
                continue;
            }
            if (n.b >= in.a && n.a < in.a) {
                n.b = in.b;
                intervals.erase(intervals.begin() + i);
                --i;
                continue;
            }
        }
        if (n.a <= n.b) {
            intervals.push_back(n);
        }
    }
    for (int i = 0; i < intervals.size(); ++i) {
        Interval in = intervals[i];
        sum += in.b - in.a + int64_t(1);
    }
    std::cout << sum << std::endl;
    return 0;
}