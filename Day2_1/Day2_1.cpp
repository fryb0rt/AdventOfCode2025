#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream stream("..\\input2.txt");
    std::string line;
    int64_t sum = 0;

    const auto process = [&](int start, int end) {
        int dash = line.find('-', start);
        auto num1Str = line.substr(start, dash - start);
        int64_t num1 = std::stoll(num1Str);
        ++dash;
        auto num2Str = line.substr(dash, end - dash);
        int64_t num2 = std::stoll(num2Str);
        auto str = num1Str.substr(0, num1Str.length() / 2);
        if (str.empty()) {
            str = "0";
        }
        do {
            const int64_t num = std::stoll(str + str);
            if (num <= num2) {
                if (num >= num1 && str[0] != '0') {
                    sum += num;
                }
            }
            else {
                break;
            }
            str = std::to_string(std::stoll(str) + 1);
        } while (true);
    };
    while (std::getline(stream, line)) {
        int prev = 0;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == ',') {
                process(prev, i);
                prev = i + 1;
            }
        }
        process(prev, line.size());
    }
    std::cout << sum  << std::endl;
    return 0;
}