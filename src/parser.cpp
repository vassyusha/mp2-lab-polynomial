#include "parser.h"

bool parser::lexical(const std::string& s, int i) {
	int state = 0;
	char l = 'x';
	for (; i < s.size(); i++) {
		switch (state) {
		case 0:
			if (s[i] == '+' || s[i] == '-') state = 1;
			else if (s[i] == ' ') break;
			else return false;
			break;
		case 1:
			if (s[i] >= '0' && s[i] <= '9') state = 2;
			else if (s[i] == ' ') break;
			else return false;
			break;
		case 2:
			if (s[i] >= '0' && s[i] <= '9') state = 2;
			else if (s[i] == '.') state = 3;
			else return false;
			break;
		case 3:
			if (s[i] >= '0' && s[i] <= '9') state = 3;
			else if (s[i] == l && l <= 'z') {
				l++;
				state = 4;
			}
			else if (s[i] == ' ') {
				if (l > 'z') {
					l = 'x';
					state = 0;
					break;
				}
				return false;
			}
			else return false;
			break;
		case 4:
			if (s[i] == '^') state = 5;
			else return false;
			break;
		case 5:
			if (s[i] >= '0' && s[i] <= '9') state = 3;
			else return false;
			break;
		}
	} if (state == 3 && l > 'z') return true;
	return false;
}

int parser::readi(const std::string& s, int& pos) {
	int res = 0;

	for (pos; pos < s.size(); pos++) {
		if (s[pos] >= '0' && s[pos] <= '9') (res *= 10) += (s[pos] - '0');
		else return res;
	}
	return res;
}

double parser::readd(const std::string& s, int& pos) {
	double res = 0;
	double temp = 0.1;

	int state = 0;

	for (pos; pos < s.size(); pos++) {
		switch (state) {
		case 0:
			if (s[pos] == '.') state = 1;
			else {
				if (s[pos] >= '0' && s[pos] <= '9') (res *= 10) += (s[pos] - '0');
				else return res;
			}
			break;
		case 1:
			if (s[pos] >= '0' && s[pos] <= '9') {
				res += (s[pos] - '0') * temp;
				temp /= 10;
			}
			else return res;
		}
	}
	return res;
}

Monomial parser::makeM(const std::string& s, int& pos) {
	int sign = 1;
	while (s[pos] != '+' && s[pos] != '-')pos++;
	if (s[pos++] == '-')sign *= -1;
	if (s[pos] == ' ') pos++;
	double score = this->readd(s, pos);
	score *= sign;
	pos += 2;
	int x = this->readi(s, pos);
	pos += 2;
	int y = this->readi(s, pos);
	pos += 2;
	int z = this->readi(s, pos);
	Monomial m(score, x, y, z);
	return m;
}

Polynomial parser::pars(const std::string& s, int pos) {
	if (this->lexical(s, pos)) {
		Polynomial p;
		while (pos < s.size()) {
			p = p + this->makeM(s, pos);
		}
		return p;
	}
	else throw "incorrect input";
	
}