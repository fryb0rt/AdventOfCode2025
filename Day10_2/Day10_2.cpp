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
	using SS = SimplexSolver<float>;
	/*SS solver(2, true);
	solver.addConstraint(SS::Constraint{ .coefs{5,4},.relation = SS::Relation::LEQUAL, .value = 32 });
	solver.addConstraint(SS::Constraint{ .coefs{1,2},.relation = SS::Relation::LEQUAL, .value = 10 });
	solver.setVariable(0, -2);
	solver.setVariable(1, -3);*/
	/*SS solver(3, false);
	solver.addConstraint(SS::Constraint{ .coefs{2,1,1},.relation = SS::Relation::LEQUAL, .value = 18 });
	solver.addConstraint(SS::Constraint{ .coefs{1,2,2},.relation = SS::Relation::LEQUAL, .value = 30 });
	solver.addConstraint(SS::Constraint{ .coefs{2,2,2},.relation = SS::Relation::LEQUAL, .value = 24 });
	solver.setVariable(0, 6);
	solver.setVariable(1, 5);
	solver.setVariable(2, 4);*/
	/*SS solver(3, true);
	solver.addConstraint(SS::Constraint{ .coefs{3,2,1},.relation = SS::Relation::EQUAL, .value = 10 });
	solver.addConstraint(SS::Constraint{ .coefs{2,5,3},.relation = SS::Relation::EQUAL, .value = 15 });
	solver.setVariable(0, -2);
	solver.setVariable(1, -3);
	solver.setVariable(2, -4);*/
	/*SS solver(3, true);
	solver.addConstraint(SS::Constraint{ .coefs{2,5,-1},.relation = SS::Relation::LEQUAL, .value = 18 });
	solver.addConstraint(SS::Constraint{ .coefs{1,-1,-2},.relation = SS::Relation::LEQUAL, .value = -14 });
	solver.addConstraint(SS::Constraint{ .coefs{3,2,2},.relation = SS::Relation::EQUAL, .value = 26 });
	solver.setVariable(0, -6);
	solver.setVariable(1, 7);
	solver.setVariable(2, 4);*/
	//SS solver(2, false);
	//solver.addConstraint(SS::Constraint{ .coefs{1,3},.relation = SS::Relation::LEQUAL, .value = 200 });
	//solver.addConstraint(SS::Constraint{ .coefs{1,1},.relation = SS::Relation::EQUAL, .value = 80 });
	//solver.addConstraint(SS::Constraint{ .coefs{1,0},.relation = SS::Relation::GEQUAL, .value = 10 });
	//solver.addConstraint(SS::Constraint{ .coefs{0,1},.relation = SS::Relation::GEQUAL, .value = 30 });
	//solver.setVariable(0, 1);
	//solver.setVariable(1, 2);
	//std::cout << solver.execute().cost << std::endl;
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
		using SS = SimplexSolver<float>;
		SS solver(buttons.size(), true);
		for (int i = 0; i < values.size(); ++i) {
			SS::Constraint c;
			c.coefs.resize(buttons.size(), 0);
			c.relation = SS::Relation::EQUAL;
			c.value = values[i];
			for (int j = 0; j < buttons.size(); ++j) {
				bool hasOne = false;
				for (int v : buttons[j]) {
					hasOne |= v == i;
				}
				c.coefs[j] = int(hasOne);
			}
			solver.addConstraint(c);
		}
		//solver.print();
		sum += int64_t(solver.execute().cost);
	}

	std::cout << sum << std::endl;
	return 0;
}
