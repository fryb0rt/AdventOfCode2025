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
        intervals.push_back(Interval{ num1, num2 });
    }
    while (std::getline(stream, line)) {
        int64_t num = std::stoll(line);
        for (Interval i : intervals) {
            if (num >= i.a && num <= i.b) {
                ++sum;
                break;
            }
        }
    }
    std::cout << sum << std::endl;
    return 0;
}