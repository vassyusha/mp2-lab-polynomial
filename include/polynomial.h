#pragma once

#include <string>
#include <iostream>
#include "list.h"

class Polynomial;

class Monomial {
private:

	double score = 0.;
	int x = 0;
	int y = 0;
	int z = 0;
	
public:

	Monomial(double score = 0., int x = 0, int y = 0, int z = 0) : score(score), x(x), y(y), z(z) {}

	bool operator==(const Monomial& other);

	bool operator>(const Monomial& other);

	bool operator<(const Monomial& other);

	Monomial operator+(const Monomial& other);

	Monomial operator*(const Monomial& other);

	friend ostream& operator<<(ostream& ostr, const Monomial& m)
	{
		ostr << m.score << "x^" << m.x << "y^" << m.y << "z^" << m.z << " ";

		return ostr;
	}

	double get_score() const { return this->score; }

};

class Polynomial {
private:

	TList<Monomial> poly;

public:

	Polynomial() {};
	Polynomial(const Monomial& mon) {
		poly.insert(mon, poly.end());
	}

	Polynomial operator+(const Polynomial& other) const;

	Polynomial operator*(const Monomial& m) const;

	Polynomial operator*(const Polynomial& other) const;

	friend ostream& operator<<(ostream& ostr, const Polynomial& p)
	{
		ostr << p.poly;

		return ostr;
	}

};
