#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

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
		int64_t max = 9, min = 1;
		std::set<int64_t> found;
		for (int i = 1; i <= num2Str.length() / 2; ++i) {
			for (int64_t n = min; n <= max; ++n) {
				auto str = std::to_string(n);
				for (int r = std::max(2, int(num1Str.length() / i)); r <= num2Str.length() / i; ++r) {
					std::string s = "";
					for (int j = 0; j < r; ++j) {
						s += str;
					}
					const int64_t num = std::stoll(s);
					if (num <= num2 && num >= num1 && found.find(num) == found.end()) {
						sum += num;
						found.insert(num);
					}
				}
			}
			min *= 10;
			max = max * 10 + 9;
		}
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
	std::cout << sum << std::endl;
	return 0;
}