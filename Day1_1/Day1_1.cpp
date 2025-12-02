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
    int dial = 50, sum = 0;
    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        char c;
        int num;
        iss >> c >> num;
        num %= 100;
        if (c == 'L') {
            dial -= num;
        }
        else {
            dial += num;
        }
        if (dial < 0) { // Rotations left
            dial += 100; 

        }
        if (dial >= 100) { // Rotations right
            dial -= 100;
        }
        if (dial == 0) { // Landing exactly on zero
            ++sum; 
        }
    }
    std::cout << sum  << std::endl;
    return 0;
}