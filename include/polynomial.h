#pragma once

#include <string>
#include <iostream>

class Monomial {
private:

	double score = 0.;
	int x = 0;
	int y = 0;
	int z = 0;

public:

	Monomial(double score = 0., int x = 0, int y = 0, int z = 0) : score(score), x(x), y(y), z(z) {}

	bool operator==(const Monomial& other) {

	}

};

class Polinomial {
private:

public:

};
