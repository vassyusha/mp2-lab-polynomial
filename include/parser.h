#pragma once
#include "polynomial.h"
class parser
{
private:
	bool lexical(const std::string& s, int i = 0);

	int readi(const std::string& s, int& pos);
	double readd(const std::string& s, int& pos);

	Monomial makeM(const std::string& s, int& pos);
public:
	Polynomial pars(const std::string& s, int pos = 0);
};

