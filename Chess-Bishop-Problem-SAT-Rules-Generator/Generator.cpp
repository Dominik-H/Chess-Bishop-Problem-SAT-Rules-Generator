#include "Generator.h"

Rule::Rule(Minisat::Lit A, Minisat::Lit B)
{
	this->A = A;
	this->B = B;
	spec = false;
}

Rule::Rule(std::vector<Minisat::Lit> sp)
{
	special = sp;
	spec = true;
}

Rule::~Rule()
{
}

Minisat::Lit Rule::getA() const
{
	if (!spec)
		return A;

	std::exit(-1);
}

Minisat::Lit Rule::getB() const
{
	if (!spec)
		return B;

	std::exit(-1);
}

std::vector<Minisat::Lit> Rule::getSpecial() const
{
	if (spec)
		return special;

	std::exit(-1);
}

Fields::Fields(int size)
{
	if (size < 1)
	{
		exit(-1);
	}

	int numFields = size * size;

	for (int i = 0; i < numFields; ++i) 
	{
		int x_pos = i % size;
		int y_pos = i / size;

		std::pair<int, int> pos = std::pair<int, int>(x_pos, y_pos);
		Minisat::Lit l = Minisat::mkLit(i, true);

		vars.push_back(l);
		var.insert(std::make_pair(pos, l));
		x.insert(std::make_pair(l, x_pos));
		y.insert(std::make_pair(l, y_pos));
	}
}

Fields::~Fields()
{
}

Minisat::Lit Fields::getVar(int x, int y) const
{
	return var.find(std::pair<int, int>(x, y))->second;
}

int Fields::getX(Minisat::Lit var) const
{
	return x.find(var)->second;
}

int Fields::getY(Minisat::Lit var) const
{
	return y.find(var)->second;
}

std::vector<Minisat::Lit> Fields::getVars() const
{
	return vars;
}

int Fields::getNumVar() const
{
	return x.size();
}

Generator::Generator(int size)
	:vars(size)
{
	if (size < 1)
	{
		exit(-1);
	}

	rules.push_back(Rule(vars.getVars()));
	deskSize = size;
	int numFields = size * size;

	for (int i = 0; i < numFields; ++i)
	{
		Minisat::Lit l = Minisat::mkLit(i, true);
		int pos_x = vars.getX(l);
		int pos_y = vars.getY(l);

		int n_x = pos_x;
		int n_y = pos_y;

		while (++n_x < size && ++n_y < size)
		{
			Minisat::Lit n_l = vars.getVar(n_x, n_y);
			Rule r = Rule(~l, ~n_l);
			rules.push_back(r);
		}

		n_x = pos_x;
		n_y = pos_y;

		while (--n_x >= 0 && ++n_y < size)
		{
			Minisat::Lit n_l = vars.getVar(n_x, n_y);
			Rule r = Rule(~l, ~n_l);
			rules.push_back(r);
		}
	}
}


Generator::~Generator()
{
}

const std::vector<std::string> Generator::getRulesForm1()
{
	if (out1.empty())
	{
		std::string line = "p cnf ";
		line += std::to_string(vars.getNumVar());
		line += " ";
		line += std::to_string(rules.size());
		out1.push_back(line);

		for (uint32_t i = 0; i < rules.size(); ++i)
		{
			line.erase();

			if (rules[i].isSpecial())
			{
				std::vector<Minisat::Lit> lits = rules[i].getSpecial();
				line = std::to_string(Minisat::var(lits[0]) + 1);

				for (uint32_t j = 1; j < lits.size(); ++j)
				{
					line += " ";
					line += std::to_string(Minisat::var(lits[j]) + 1);
				}

				line += " 0";
			}
			else
			{
				line = "-";
				line += std::to_string(Minisat::var(rules[i].getA()) + 1);
				line += " -";
				line += std::to_string(Minisat::var(rules[i].getB()) + 1);
				line += " 0";
			}

			out1.push_back(line);
		}
	}

	return out1;
}

const std::vector<std::string> Generator::getRulesForm2()
{
	if (out2.empty())
	{
		std::string line = "";

		for (uint32_t i = 0; i < rules.size(); ++i)
		{
			line.erase();

			if (rules[i].isSpecial())
			{
				std::vector<Minisat::Lit> lits = rules[i].getSpecial();
				line = std::to_string(Minisat::var(lits[0]) + 1);

				for (uint32_t j = 1; j < lits.size(); ++j)
				{
					line += " ";
					line += std::to_string(Minisat::var(lits[j]) + 1);
				}
			}
			else
			{
				line = "-";
				line += std::to_string(Minisat::var(rules[i].getA()) + 1);
				line += " -";
				line += std::to_string(Minisat::var(rules[i].getB()) + 1);
			}

			out2.push_back(line);
		}
	}

	return out2;
}

int Generator::getDeskSize() const
{
	return deskSize;
}

Fields Generator::getVariables() const
{
	return vars;
}

std::vector<Rule> Generator::getRules() const
{
	return rules;
}
