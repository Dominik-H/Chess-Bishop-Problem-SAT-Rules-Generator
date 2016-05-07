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
	Rule(std::vector<Minisat::Lit> sp); // Special First Rule sp[0] or sp[1] or .... sp[n];
	~Rule();
	Minisat::Lit getA() const; // Get Literal of A (for input into solver)
	Minisat::Lit getB() const; // Get Literal of B (for input into solver)
	std::vector<Minisat::Lit> getSpecial() const;
	bool isSpecial() const { return spec; }
private:
	Minisat::Lit A;
	Minisat::Lit B;

	bool spec;
	std::vector<Minisat::Lit> special;
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

	Minisat::Lit getVar(int x, int y) const; // Get literal positioned at x and y on the chess board.
	int getX(Minisat::Lit var) const; // Get X position of literal represented by var.
	int getY(Minisat::Lit var) const; // Get Y position of literal represented by var.
	std::vector<Minisat::Lit> getVars() const;

	int getNumVar() const; // Just for reference.
private:
	std::map<std::pair<int, int>, Minisat::Lit> var; // use mkLit(var, sign) as constructor of Lit!!
	std::map<Minisat::Lit, int> x; // indexed from 0
	std::map<Minisat::Lit, int> y; // indexed from 0
	std::vector<Minisat::Lit> vars;
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

	// Each string in vector is one line!!!
	const std::vector<std::string> getRulesForm1(); // DIMACS format (p cnf ...)
	const std::vector<std::string> getRulesForm2(); // Simple format used by http://logictools.org

	int getDeskSize() const; // Might be needed.
	Fields getVariables() const; // For use in Minisat Solver and to find position of each variable
	std::vector<Rule> getRules() const; // For use in Minisat Solver

private:
	Fields vars; 
	std::vector<Rule> rules; // Form: Rule1 AND Rule2 AND ...

	std::vector<std::string> out1;
	std::vector<std::string> out2;

	int deskSize;
};

