#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream stream("..\\input4.txt");
    std::string line;
    int64_t sum = 0;
    std::vector<std::string> field;
    while (std::getline(stream, line)) {
        field.push_back(line);
    }
    bool removed = false;
    do {
        removed = false;
        for (int y = 0; y < field.size(); ++y) {
            for (int x = 0; x < field[0].size(); ++x) {
                if (field[y][x] != '@') {
                    continue;
                }
                const auto check = [&field](int x, int y) {
                    return x >= 0 && y >= 0 && x < field[0].size() && y < field.size() && field[y][x] == '@';
                    };
                int cnt = 0;
                cnt += check(x - 1, y);
                cnt += check(x + 1, y);
                cnt += check(x - 1, y - 1);
                cnt += check(x + 1, y - 1);
                cnt += check(x - 1, y + 1);
                cnt += check(x + 1, y + 1);
                cnt += check(x, y - 1);
                cnt += check(x, y + 1);
                if (cnt < 4) {
                    ++sum;
                    removed = true;
                    field[y][x] = '.';
                }
            }
        }
    } while (removed);
    std::cout << sum << std::endl;
    return 0;
}