#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream stream("..\\input6.txt");
    std::string line;
    int64_t sum = 0;


    std::vector<std::vector<int64_t>> numbers;
    std::vector<std::string> strNumbers;
    std::vector<char> operations;
    while (std::getline(stream, line)) {
        if (line[0] != '*' && line[0] != '+') {
            strNumbers.push_back(line);
        }
        else {
            std::istringstream iss(line);
            while (iss) {
                char c;
                iss >> c;
                if (!iss) {
                    break;
                }
                operations.push_back(c);
            }
        }
    }
    std::vector<int64_t> n;
    for (int i = 0; i < strNumbers[0].size(); ++i) {
        int num = 0;
        bool only_space = true;
        for (int j = 0; j < strNumbers.size(); ++j) {
            if (strNumbers[j][i] == ' ') {
                continue;
            }
            else {
                num = num * 10 + (strNumbers[j][i] - '0');
                only_space = false;
            }
        }
        if (!only_space) {
            n.push_back(num);
        }
        else {
            numbers.push_back(n);
            n.clear();
        }
    }
    numbers.push_back(n);
    for (int i = 0; i < operations.size(); ++i) {
        if (operations[i] == '+') {
            int64_t res = 0;
            for (int j = 0; j < numbers[i].size(); ++j) {
                res += numbers[i][j];
            }
            sum += res;
        }
        else {
            int64_t res = 1;
            for (int j = 0; j < numbers[i].size(); ++j) {
                res *= numbers[i][j];
            }
            sum += res;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}