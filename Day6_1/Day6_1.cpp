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
    std::vector<char> operations;
    while (std::getline(stream, line)) {
        if (line[0] != '*' && line[0] != '+') {
            std::istringstream iss(line);
            std::vector<int64_t> n;
            while (iss) {
                int64_t num;
                iss >> num;
                if (!iss) {
                    break;
                }
                n.push_back(num);
            }
            numbers.push_back(n);
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
    for (int i = 0; i < operations.size(); ++i) {
        if (operations[i] == '+') {
            int64_t res = 0;
            for (int j = 0; j < numbers.size(); ++j) {
                res += numbers[j][i];
            }
            sum += res;
        }
        else {
            int64_t res = 1;
            for (int j = 0; j < numbers.size(); ++j) {
                res *= numbers[j][i];
            }
            sum += res;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}