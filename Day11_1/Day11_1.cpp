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
	int start = -1;
	for (int i = 0; i < v.size(); ++i) {
		if (v[i].name == "svr") {
			start = i;
		}
		for (auto& s : v[i].c) {
			for (int j = 0; j < v.size(); ++j) {
				if (v[j].name == s) {
					v[i].e.push_back(j);
				}
			}
		}
	}
	std::vector<int> s;
	s.push_back(start);
	while (!s.empty()) {
		int vv = s.back();
		s.pop_back();
		
		if (vv == v.size() - 1) {
			++sum;
			continue;
		}
		for (int i : v[vv].e) {
			if (i == start) {
				continue;
			}
			s.push_back(i);
		}
	}

	std::cout << sum << std::endl;
	return 0;
}
