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
		int64_t max = 0;
		auto str = line.substr(line.size() - 12, 12);
		int64_t curr = std::stoll(str);
		for (int i = line.size() - 13; i >= 0; --i) {
			int j = 0;
			char n = line[i];
			auto str2 = n + str;
			for (int j = 0; j < str2.size(); ++j) {
				auto str3 = str2.substr(0, j) + str2.substr(j + 1);
				if (std::stoll(str3) > std::stoll(str)) {
					str = str3;
				}
			}
		}
		sum += std::stoll(str);
	}
	std::cout << sum << std::endl;
	return 0;
}