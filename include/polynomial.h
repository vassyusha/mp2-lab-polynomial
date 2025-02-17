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
		if (this->x == other.x && this->y == other.y && this->z == other.z) return true;
		else return false;
	}

	bool operator>(const Monomial& other) {
		if (this->x > other.x) return true;
		if (this->y > other.y) return true;
		if (this->z > other.z) return true;
		return false;
	}

	bool operator<(const Monomial& other) {
		if ((*this) == other || (*this) > other) return false;
		return true;
	}

};

class Polinomial {
private:

public:

};
