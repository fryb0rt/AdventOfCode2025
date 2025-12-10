#include <string>
#include <vector>
#include <cassert>
#include <set>

std::vector<std::string> split(const std::string& s, char c, bool keepEmpty = false) {
	std::vector<std::string> result;
	int start = 0, end = int(s.size());
	for (int i = 0; i < end; ++i) {
		if (s[i] == c) {
			if (i - start > 0 || keepEmpty) {
				result.push_back(s.substr(start, i - start));
			}
			start = i + 1;
		}
	}
	if (end - start > 0 || keepEmpty) {
		result.push_back(s.substr(start, end - start));
	}
	return result;
}

template<typename T>
std::vector<T> parseList(const std::string& s, char sep) {
	int start = 0, end = int(s.size());
	while (start < end && !std::isdigit(s[start])) {
		++start;
	}
	while (end > start && !std::isdigit(s[end - 1])) {
		--end;
	}
	std::vector<std::string> spl = split(s.substr(start, end - start), sep);
	std::vector<T> res(spl.size());
	for (int i = 0; i < res.size(); ++i) {
		if constexpr (sizeof(T) == sizeof(long)) {
			res[i] = std::stoi(spl[i]);
		}
		else {
			res[i] = std::stoll(spl[i]);
		}
	}
	return res;
}

template<typename T>
class SimplexSolver {
public:
	enum class Relation {
		LEQUAL = 0,
		GEQUAL = 1,
		EQUAL = 2
	};
	struct Constraint {
		std::vector<T> coefs;
		Relation relation;
		T value;
	};

	enum class VariableType {
		NON_NEGATIVE = 0,
		NON_POSITIVE = 1,
		UNBOUNDED = 2
	};

private:
	struct Variable {
		T cost;
		VariableType type;
		int originalIndex;
	};
	std::vector<Variable> mVariables;

	std::vector<Constraint> mConstraints;

	const int mVariableCount;

	bool mMinimize;
public:
	SimplexSolver(const int variableCount, bool minimize) :mVariables(variableCount, { T(1), VariableType::NON_NEGATIVE, -1 }), mVariableCount(variableCount), mMinimize(minimize) {
	}

	void addConstraint(const Constraint& constraint) {
		assert(constraint.coefs.size() == mVariables.size());
		mConstraints.push_back(constraint);
	}

	void setVariable(const int index, const T cost, const VariableType type = VariableType::NON_NEGATIVE) {
		assert(index >= 0 && index < int(mVariables.size()));
		mVariables[index].cost = cost;
		mVariables[index].type = type;
	}

	void print() {
		std::cout << "Variables" << std::endl;
		for (int i = 0; i < int(mVariables.size()); ++i) {
			std::cout << char('a' + i);
			switch (mVariables[i].type) {
			case VariableType::NON_NEGATIVE:
				std::cout << " >= 0 ";
				break;
			case VariableType::UNBOUNDED:
				break;
			case VariableType::NON_POSITIVE:
				std::cout << " <= 0 ";
				break;
			}
			if (mVariables[i].originalIndex != -1) {
				std::cout << " (added to " << char('a' + mVariables[i].originalIndex) << ')';
			}
			std::cout << std::endl;
		}
		std::cout << "Cost" << std::endl;
		if (mMinimize) {
			std::cout << "Minimize: ";
		}
		else {
			std::cout << "Maximize: ";
		}
		for (int i = 0; i < int(mVariables.size()); ++i) {
			if (mVariables[i].cost != T(0)) {
				if (mVariables[i].cost > T(0) && i > 0) {
					std::cout << "+";
				}
				std::cout << mVariables[i].cost << char('a' + i) << " ";
			}
		}
		std::cout << std::endl;

		std::cout << "Constraints" << std::endl;
		for (const Constraint& c : mConstraints) {
			for (int i = 0; i < int(c.coefs.size()); ++i) {
				if (c.coefs[i] != T(0)) {
					if (c.coefs[i] > T(0) && i > 0) {
						std::cout << "+";
					}
					std::cout << c.coefs[i] << char('a' + i) << " ";
				}
			}
			switch (c.relation) {
			case Relation::LEQUAL:
				std::cout << " <= " << c.value << std::endl;
				break;
			case Relation::GEQUAL:
				std::cout << " >= " << c.value << std::endl;
				break;
			case Relation::EQUAL:
				std::cout << " = " << c.value << std::endl;
			}

		}
	}


	void convertToStandardForm() {
		// Search for new variables
		std::vector<int> newVars;
		for (int i = 0; i < int(mVariables.size()); ++i) {
			switch (mVariables[i].type) {
			case VariableType::NON_NEGATIVE:
				break;
			case VariableType::UNBOUNDED:
				newVars.push_back(i);
				break;
			case VariableType::NON_POSITIVE: {
				newVars.push_back(i);
				// Add new constraint as well
				Constraint c;
				c.value = T(0);
				c.relation = Relation::LEQUAL;
				c.coefs.resize(mVariables.size(), 0);
				c.coefs[i] = 1;
				mConstraints.push_back(c);
				break;
			}
			}
			mVariables[i].type = VariableType::NON_NEGATIVE;
		}
		// Add new variables
		for (int originalIndex : newVars) {
			Variable v;
			v.cost = -mVariables[originalIndex].cost;
			v.type = VariableType::NON_NEGATIVE;
			v.originalIndex = originalIndex;
			mVariables.push_back(v);
			// Add new variable to constraints
			for (Constraint& c : mConstraints) {
				c.coefs.push_back(-c.coefs[originalIndex]);
			}
		}
		// Finaly fix constraints
		for (Constraint& c : mConstraints) {
			if (c.value < T(0)) {
				c.value = -c.value;
				for (auto& coef : c.coefs) {
					coef = -coef;
				}
				if (c.relation == Relation::LEQUAL) {
					c.relation = Relation::GEQUAL;
				}
				else if (c.relation == Relation::GEQUAL) {
					c.relation = Relation::LEQUAL;
				}
			}
		}
		if (mMinimize) {
			for (auto& v : mVariables) {
				v.cost = -v.cost;
			}
		}
	}

	struct Result {
		std::vector<T> variables;
		T cost;
	};

	Result execute() {
		convertToStandardForm();
		const T M(100000000);
		// Initialize our variables
		int varCount = int(mVariables.size());
		for (const auto& c : mConstraints) {
			if (c.relation != Relation::GEQUAL) {
				// EQUAL = 1 artificial
				// LEQUAL = 1 slack
				++varCount;
			}
			else {
				// GEQUAL = 1 artificial + 1 surplass
				varCount += 2;
			}
		}
		// Create equations from constraints
		struct Equation {
			std::vector<T> coefs;
			T constant;
			T basisValue;
			int basis;
			// constant = ....coefs * x
		};
		std::vector<Equation> equations;
		int newVarIndex = int(mVariables.size());
		std::set<int> artificial;
		for (int i = 0; i < int(mConstraints.size()); ++i) {
			Equation e;
			e.coefs.resize(varCount, 0);
			for (int j = 0; j < int(mConstraints[i].coefs.size()); ++j) {
				e.coefs[j] = mConstraints[i].coefs[j];
			}
			e.constant = mConstraints[i].value;
			if (mConstraints[i].relation == Relation::LEQUAL) {
				e.coefs[newVarIndex] = T(1); // 1 slack
				e.basis = newVarIndex;
				e.basisValue = T(0);
				++newVarIndex;
			}
			else if (mConstraints[i].relation == Relation::GEQUAL) {
				e.coefs[newVarIndex] = -T(1); // 1 surplas
				e.coefs[newVarIndex + 1] = T(1); // 1 artificial
				artificial.insert(newVarIndex + 1);
				e.basis = newVarIndex + 1;
				e.basisValue = -M;
				newVarIndex += 2;
			}
			else {
				e.coefs[newVarIndex] = T(1); // 1 artificial
				artificial.insert(newVarIndex);
				e.basis = newVarIndex;
				e.basisValue = -M;
				++newVarIndex;
			}
			equations.emplace_back(e);
		}
		Equation costFunction;
		costFunction.constant = T(0);
		costFunction.coefs.resize(varCount, 0);
		for (int j = 0; j < int(mVariables.size()); ++j) {
			costFunction.coefs[j] = mVariables[j].cost;
		}
		for (int a : artificial) {
			costFunction.coefs[a] = -M;
		}


		const auto findPivotAndUpdateCost = [&]() {
			int pivot = -1;
			T prevValue = 0;
			for (int i = 0; i < mVariables.size(); ++i) {
				T value = costFunction.coefs[i];
				for (const Equation& eq : equations) {
					value -= eq.basisValue * eq.coefs[i];
				}
				if (prevValue < value) {
					prevValue = value;
					pivot = i;
				}
			}
			return pivot;
			};

		const auto replaceVariable = [&](Equation& eq, const Equation& var, const int pivot) {
			const T multiplier = eq.coefs[pivot];
			for (int i = 0; i < varCount; ++i) {
				eq.coefs[i] -= multiplier * var.coefs[i];
			}
			eq.constant -= multiplier * var.constant;
			};
		int pivot = findPivotAndUpdateCost();
		while (pivot != -1) {
			// Find minimum pivot variable increase
			T minimum = T(0);
			int minimumEqIndex = 0;
			for (int i = 0; i < int(equations.size()); ++i) {
				const Equation& e = equations[i];
				if (e.coefs[pivot] <= 0) {
					continue;
				}
				const T pivotValue = e.constant / e.coefs[pivot];
				if (minimum == T(0) || minimum > pivotValue) {
					minimum = pivotValue;
					minimumEqIndex = i;
				}
			}

			// Compute pivot value using equation
			const T div = equations[minimumEqIndex].coefs[pivot];
			for (int j = 0; j < varCount; ++j) {
				equations[minimumEqIndex].coefs[j] /= div;
			}
			equations[minimumEqIndex].constant /= div;
			equations[minimumEqIndex].basis = pivot;
			equations[minimumEqIndex].basisValue = costFunction.coefs[pivot];

			// Update remaining equations
			for (int i = 0; i < int(equations.size()); ++i) {
				if (i != minimumEqIndex) {
					replaceVariable(equations[i], equations[minimumEqIndex], pivot);
				}
			}
			pivot = findPivotAndUpdateCost();
		}
		Result r;
		r.variables.resize(mVariableCount, 0);
		r.cost = T(0);
		for (const Equation& eq : equations) {
			if (eq.basis < mVariableCount) {
				r.variables[eq.basis] = eq.constant;
				r.cost += eq.constant * mVariables[eq.basis].cost;
			}
		}
		if (mMinimize) {
			r.cost = -r.cost;
		}
		return r;
	}
private:
	Constraint invert(const Constraint& constraint) {
		Constraint result = constraint;
		for (T& coef : result.coefs) {
			coef = -coef;
		}
		result.value = -result.value;
		result.relation = Relation::LEQUAL;
		return result;
	}
};