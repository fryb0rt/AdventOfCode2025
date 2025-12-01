#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream stream("..\\input1.txt");
    std::string line;
    int dial = 50, sum = 0, rot = 0;
    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        char c;
        int num;
        iss >> c >> num;
        rot += num / 100;
        num %= 100;
        int previous = dial;
        if (c == 'L') {
            dial -= num;
        }
        else {
            dial += num;
        }
        // We will not be going through 0 since we are on it
        if (dial < 0 && previous == 0) {
            --rot;
        }
        if (dial < 0) { // Rotations left
            dial += 100;
            ++rot;
        }
        if (dial > 100) { // Rotations right
            ++rot;
            dial -= 100;
        }
        if (dial == 100) { // This is not rotation - this is landing on 0
            dial = 0;
        }
        if (dial == 0) { // Landing exactly on zero
            ++sum;
        }
    }
    std::cout << sum << " " << rot << " " << (rot + sum) << std::endl;
    return 0;
}