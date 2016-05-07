#include "Generator.h"

Rule::Rule(Minisat::Lit A, Minisat::Lit B)
{

}

Rule::~Rule()
{
}

Minisat::Lit Rule::getA()
{

}

Minisat::Lit Rule::getB()
{

}

Fields::Fields(int size)
{

}

Fields::~Fields()
{
}

Minisat::Lit Fields::getVar(int x, int y)
{

}

int Fields::getX(Minisat::Lit var)
{

}

int Fields::getY(Minisat::Lit var)
{

}

int Fields::getNumVar()
{

}

Generator::Generator(int size)
	:vars(size)
{

}


Generator::~Generator()
{
}

std::vector<std::string> Generator::getRulesForm1() const
{

}

std::vector<std::string> Generator::getRulesForm2() const
{

}

int Generator::getDeskSize() const
{

}

Fields &Generator::getVariables() const
{

}

std::vector<Rule> &Generator::getRules() const
{

}
