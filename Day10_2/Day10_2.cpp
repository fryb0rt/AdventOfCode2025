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
	std::ifstream stream("..\\input10.txt");
	std::string line;
	int64_t sum = 0;
	int k = 0;
	while (std::getline(stream, line)) {
		auto s = split(line, ' ');
		std::vector<std::vector<int>> buttons;
		for (int i = 1; i < s.size() - 1; ++i) {
			buttons.push_back(parseList<int>(s[i], ','));
		}
		std::vector<int> values = parseList<int>(s.back(), ',');
		using SS = SimplexSolver<double>;
		SS solver(int(buttons.size()));
		for (int i = 0; i < values.size(); ++i) {
			SS::Constraint c;
			c.coefs.resize(buttons.size(), 0);
			c.type = SS::ConstraintType::EQUAL;
			c.value = double(values[i]);
			for (int j = 0; j < buttons.size(); ++j) {
				bool hasOne = false;
				for (int v : buttons[j]) {
					hasOne |= v == i;
				}
				c.coefs[j] = double(int(hasOne));
			}
			solver.addConstraint(c);
		}
		for (int i = 0; i < buttons.size(); ++i) {
			solver.setVariable(i, 1.0f, SS::VariableBounds::NON_NEGATIVE, SS::VariableType::INTEGER);
        }
		auto result = solver.execute(SS::Operation::MINIMIZE);
		solver.checkResult(result);
		std::cout << result.cost << std::endl;
		sum += int64_t(result.cost);
	}

	std::cout << sum << std::endl;
	return 0;
}
