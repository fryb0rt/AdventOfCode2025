#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../Utils.h"

int main()
{
	std::ifstream stream("..\\input12.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<int> ps;
	while (std::getline(stream, line)) {
		if (line.find('x') == std::string::npos) {
			// Gift
			int count = 0;
			while (std::getline(stream, line) && line.size() > 0) {
				for (auto c : line) {
					count += c == '#';
				}
			}
			ps.push_back(count);
		}
		else {
			//Regions
			do {
				auto spl = split(line, ':');
				auto gifts = parseList<int>(spl[1], ' ');
				auto spl2 = split(spl[0], 'x');
				int x = std::stoi(spl2[0]);
				int y = std::stoi(spl2[1]);
				int64_t k = x * y;
				for (int j = 0; j < gifts.size(); ++j) {
					k -= gifts[j] * ps[j];
				}
				sum += k > 0;

			} while (std::getline(stream, line));
		}
	}
	std::cout << sum << std::endl;
	return 0;
}
