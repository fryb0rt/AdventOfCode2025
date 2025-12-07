#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream stream("..\\input7.txt");
    std::string line;
    int64_t sum = 0;

    std::vector<std::string> field;
    std::vector<std::vector<int64_t>> count;
    while (std::getline(stream, line)) {
        field.push_back(line);
    }
    int X = field[0].size();
    count.resize(field.size(), std::vector<int64_t>(X, 0));
    for (int i = 0; i < X; ++i) {
        if (field[0][i] == 'S') {
            field[1][i] = '|';
            count[1][i] = 1;
        }
    }
    for (int i = 1; i + 1 < field.size(); ++i) {
        for (int x = 0; x < X; ++x) {
            if (field[i][x] == '|') {
                if (field[i + 1][x] == '.' || field[i + 1][x] == '|') {
                    field[i + 1][x] = '|';
                    count[i + 1][x] += count[i][x];
                }
                else {
                    if (x > 0 && field[i + 1][x - 1] != '^') {
                        field[i + 1][x - 1] = '|';
                        count[i + 1][x - 1] += count[i][x];
                    }
                    if (x < X - 1 && field[i + 1][x + 1] != '^') {
                        field[i + 1][x + 1] = '|';
                        count[i + 1][x + 1] += count[i][x];
                    }
                }
            }
        }
    }
    for (int x = 0; x < X; ++x) {
        sum += count.back()[x];
    }
    std::cout << sum << std::endl;
    return 0;
}