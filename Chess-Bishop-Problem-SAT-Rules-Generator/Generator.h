#pragma once
#include <vector>
#include <map>
#include <string>
#include "core\Solver.h"

/*
* Rule has form A or B
*/
class Rule
{
public:
	Rule(Minisat::Lit A, Minisat::Lit B); // Create Rule A or B (A, B can be true or false)
	~Rule();
	Minisat::Lit getA(); // Get Literal of A (for input into solver)
	Minisat::Lit getB(); // Get Literal of B (for input into solver)
private:
	Minisat::Lit A;
	Minisat::Lit B;
};

/*
* Representation of chess board fields.
* Also generates the fields depending on the board size.
*/
class Fields
{
public:
	Fields(int size);
	~Fields();

	Minisat::Lit getVar(int x, int y); // Get literal positioned at x and y on the chess board.
	int getX(Minisat::Lit var); // Get X position of literal represented by var.
	int getY(Minisat::Lit var); // Get Y position of literal represented by var.

	int getNumVar(); // Just for reference.
private:
	std::map<std::pair<int, int>, Minisat::Lit> var; // use mkLit(var, sign) as constructor of Lit!!
	std::map<Minisat::Lit, int> x;
	std::map<Minisat::Lit, int> y;
};

/*
* Generates the rules.
* The main object used in the GUI to do everything necessary.
*/
class Generator
{
public:
	Generator(int size = 8); // Call this and then just read results in form you need.
	~Generator();

	std::vector<std::string> getRulesForm1() const; // DIMACS format
	std::vector<std::string> getRulesForm2() const; // Simple format used by http://logictools.org
	int getDeskSize() const; // Might be needed.
	Fields &getVariables() const; // For use in Minisat Solver and to find position of each variable
	std::vector<Rule> &getRules() const; // For use in Minisat Solver

private:
	Fields vars; 
	std::vector<Rule> rules; // Form: Rule1 AND Rule2 AND ...

	int deskSize;
};

