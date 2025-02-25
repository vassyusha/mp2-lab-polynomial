#include "polynomial.h"

Monomial::Monomial(double score, int x, int y, int z) {
	if (x < 0 || y < 0 || z < 0 || x >10 || y > 10 || z>10) throw "powers should be in [0,10]";
	this->score = score;
	this->x = x;
	this->y = y;
	this->z = z;
}

bool Monomial::operator==(const Monomial& other)const {
	if (this->x == other.x && this->y == other.y && this->z == other.z) return true;
	else return false;
}
bool Monomial::operator!=(const Monomial& other)const {
	return !((*this) == other);
}

bool Monomial::operator>(const Monomial& other)const {
	if (this->x > other.x) return true;
	if (this->x < other.x) return false;
	if (this->y > other.y) return true;
	if (this->y < other.y) return false;
	if (this->z > other.z) return true;
	return false;
}

bool Monomial::operator<(const Monomial& other)const {
	if ((*this) == other || (*this) > other) return false;
	return true;
}

Monomial Monomial::operator+(const Monomial& other) {
	if (!((*this) == other)) throw "you are going to create polynomial, please, chose another method";
	return Monomial(this->score + other.score, this->x, this->y, this->z);
}

Monomial Monomial::operator*(const Monomial& other) {
	if (this->score * other.score == 0.) return Monomial();
	return Monomial(this->score * other.score, this->x + other.x, this->y + other.y, this->z + other.z);
}


Polynomial Polynomial::operator+(const Polynomial& other) const {
	Polynomial p;
	TList<Monomial>::iterator it1 = this->poly.begin(), it2 = other.poly.begin(), it = p.poly.begin();
	if (it2 == other.poly.end()) p.poly = this->poly;
	else if (it1 == this->poly.end()) p.poly = other.poly;
	else {
		while (it1 != this->poly.end() && it2 != other.poly.end()) {
			if (this->poly.at(it1) < other.poly.at(it2)) {
				it = p.poly.insert(this->poly.at(it1), it);
				++it1;
			}
			else {
				if (this->poly.at(it1) == other.poly.at(it2)) {
					it = p.poly.insert(this->poly.at(it1) + other.poly.at(it2), it);
					++it1;
					++it2;
				}
				else {
					it = p.poly.insert(other.poly.at(it2), it);
					++it2;
				}

			}
		}
		if (it1 == this->poly.end()) for (; it2 != other.poly.end(); ++it2) it = p.poly.insert(other.poly.at(it2), it);
		else for (; it1 != this->poly.end(); ++it1) it = p.poly.insert(this->poly.at(it1), it);
	}
	return p;
}

Polynomial Polynomial::operator*(const Monomial& m) const {
	Polynomial p;
	TList<Monomial>::iterator it = this->poly.begin();
	for (; it != this->poly.end(); ++it)
		p = p + (this->poly.at(it) * m);

	return p;
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
	Polynomial p, p1;
	TList<Monomial>::iterator it = this->poly.begin();
	for (; it != this->poly.end(); ++it) {
		p1 = other * (this->poly.at(it));
		p = p + p1;
	}
	return p;
}