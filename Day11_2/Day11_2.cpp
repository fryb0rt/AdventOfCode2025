#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../Utils.h"

struct V {
	std::string name;
	std::vector<std::string> c;
	std::vector<int> e;
};

int64_t search2(const std::vector<V>& v, std::vector<int64_t>& count, int start, int end, int skip1, int skip2) {
	if (count[start] != -1) {
		return count[start];
	}
	if (start == skip1 || start == skip2) {
		return 0;
	}
	if (start == end) {
		return 1;
	}
	int64_t sum = 0;
	for (int i : v[start].e) {
		sum += search2(v, count, i, end, skip1, skip2);
	}
	count[start] = sum;
	return sum;
}

int main()
{
	std::ifstream stream("..\\input11.txt");
	std::string line;
	int64_t sum = 0;
	int k = 0;
	std::vector<V> v;
	while (std::getline(stream, line)) {
		auto s = split(line, ' ');
		V vv;
		vv.name = s[0].substr(0, s[0].size() - 1);
		for (int i = 1; i < s.size(); ++i) {
			vv.c.push_back(s[i]);
		}
		v.push_back(vv);
	}
	v.push_back(V{ "out" });
	int start = -1, dac, fft;

	for (int i = 0; i < v.size(); ++i) {
		if (v[i].name == "svr") {
			start = i;
		}
		if (v[i].name == "dac") {
			dac = i;
		}
		if (v[i].name == "fft") {
			fft = i;
		}
		for (auto& s : v[i].c) {
			for (int j = 0; j < v.size(); ++j) {
				if (v[j].name == s) {
					v[i].e.push_back(j);
				}
			}
		}
	}
	auto search = [&](int start, int end, int skip1, int skip2) {
		std::vector<int64_t> count(v.size(), -1);
		std::cout << "Search: " << start << std::endl;
		return search2(v, count, start, end, skip1, skip2);
		};

	auto a = search(start, dac, fft, v.size() - 1);
	auto b = search(dac, fft, v.size() - 1, v.size() - 1);
	auto c = search(fft, v.size() - 1, dac, dac);
	sum = a * b * c;
	auto d = search(start, fft, dac, v.size() - 1);
	auto e = search(fft, dac, v.size() - 1, v.size() - 1);
	auto f= search(dac, v.size() - 1, fft, fft);
	sum += d * e * f;
	std::cout << sum << std::endl;
	return 0;
}
