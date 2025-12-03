#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream stream("..\\input3.txt");
    std::string line;
    int64_t sum = 0;
    while (std::getline(stream, line)) {
        int max = 0;
        for (int i = 0; i < line.size(); ++i) {
            int num = line[i] - '0';
            for (int j = i+1; j < line.size(); ++j) {
                max = std::max(max, num * 10 + (line[j] - '0'));
            }
        }
        sum += max;
    }
    std::cout << sum  << std::endl;
    return 0;
}