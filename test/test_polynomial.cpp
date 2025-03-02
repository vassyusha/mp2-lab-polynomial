#include "polynomial.h"
#include "parser.h"

#include <gtest.h>

TEST(Monomial, canMakeZeroMonomial) {
	ASSERT_NO_THROW(Monomial());
}

TEST(Monomial, canMakeConstMonomial) {
	ASSERT_NO_THROW(Monomial(2.1));
}

TEST(Monomial, cantMakeMonomialWithPowersOutOfRange) {
	ASSERT_ANY_THROW(Monomial(2.3, 11, 12, 13));
}

TEST(Monomial, canMakeUsualMonomial) {
	ASSERT_NO_THROW(Monomial(3.3, 2, 3, 4));
}

TEST(Monomial, canCompareMonomials) {
	Monomial m1(1.2, 2, 3, 4), m2(2.2, 3, 3, 4);
	EXPECT_TRUE(m1 < m2);
}

TEST(Monomial, SumOfMonomialsWithEqualPowersIsMonomial) {
	Monomial m1(1.2, 2, 3, 4), m2(2.2, 2, 3, 4);
	Monomial m(3.4, 2, 3, 4);
	Monomial mm;
	ASSERT_NO_THROW(mm = m1 + m2);
	EXPECT_EQ(m, m1 + m2);
}

TEST(Monomial, canMultiplyMonomialOnZero) {
	Monomial m1(1.2, 2, 3, 4), m2;
	EXPECT_EQ(m2, m1 * m2);
}

TEST(Monomial, canMultiplyMonomialOnConst) {
	Monomial m1(1.2, 2, 3, 4), m2(4);
	Monomial m(4.8, 2, 3, 4);
	EXPECT_EQ(m, m1 * m2);
}

TEST(Monomial, canMultiplyMonomials) {
	Monomial m1(1.2, 2, 3, 4), m2(2, 3, 4, 5);
	Monomial m(2.4, 5, 7, 9);
	EXPECT_EQ(m, m1 * m2);
}


TEST(parser, throwsForIncorrectInput) {
	std::string s = "-12.x^3y^4z";
	parser p;
	ASSERT_ANY_THROW(p.pars(s,0));
}

TEST(parser, canParsCorrectMonomial) {
	std::string s = "+1.2x^1y^2z^3";
	parser p;
	ASSERT_NO_THROW(p.pars(s, 0));
}

TEST(parser, correctlyParsesMonomial) {
	std::string s = "+1.2x^1y^2z^3";
	parser p;
	Polynomial pol(Monomial(1.2, 1, 2, 3)), pol1;
	pol1 = p.pars(s, 0);
	EXPECT_EQ(pol, pol1);
}

TEST(parser, canParsPolynomial) {
	std::string s = "- 12.x^1y^0z^3 - 3.7x^0y^1z^2 + 3.3x^2y^2z^1";
	parser p;
	ASSERT_NO_THROW(p.pars(s, 0));
}

TEST(parser, correctlyParsesPolynomial) {
	std::string s = "- 12.x^1y^0z^3 - 3.7x^0y^1z^2 + 3.3x^2y^2z^1";
	parser p;
	Polynomial pol = Polynomial(Monomial(-12., 1, 0, 3)) + Polynomial(Monomial(-3.7, 0, 1, 2)) + Polynomial(Monomial(3.3, 2, 2, 1));
	EXPECT_EQ(pol, p.pars(s, 0));
}


TEST(Polynomial, canMakeEmptyPolynomial) {
	ASSERT_NO_THROW(Polynomial());
}

TEST(Polynomial, canMakePolynomialOutOfMonomial) {
	Monomial m(1, 2, 3, 4);
	ASSERT_NO_THROW(Polynomial(m));
}

TEST(Polynomial, canAddPolynomials) {
	parser p;
	Polynomial p1 = p.pars("-3.2x^1y^0z^0"), p2 = p.pars("+1.x^0y^1z^2");
	ASSERT_NO_THROW(p1 + p2);
}

TEST(Polynomial, canCorrectlyAddPolynomials) {
	parser p;
	Polynomial p1 = p.pars("-3.2x^1y^0z^0"), p2 = p.pars("+1.x^0y^1z^2");
	Polynomial pol = p.pars("+1.x^0y^1z^2 -3.2x^1y^0z^0");
	EXPECT_EQ(pol, p1 + p2);
}

TEST(Polynomial, canMultiplyPolinomialOnMonomial) {
	parser p;
	Polynomial p1 = p.pars("+1.x^0y^1z^2 -3.2x^1y^0z^0");
	Monomial m(1.2, 3, 4, 5);
	ASSERT_NO_THROW(p1 *m);
}

TEST(Polynomial, canCorrectlyMultiplyPolinomialOnMonomial) {
	parser p;
	Polynomial p1 = p.pars("+1.x^0y^1z^2 -3.2x^1y^0z^0");
	Polynomial p2 = p.pars("+1.2x^3y^5z^7 -3.84x^4y^4z^5");
	Monomial m(1.2, 3, 4, 5);
	EXPECT_EQ(p2, p1 * m);
}

TEST(Polynomial, canMultiplyPolynomials) {
	Monomial m1(2., 1, 0, 0);
	Monomial m2(1.5, 0, 1, 0);
	Polynomial p = Polynomial(m1)+ Polynomial(m2);
	
	ASSERT_NO_THROW(p*p);

}

TEST(Polynomial, canCorrectlyMultiplyPolynomials) {
	Monomial m1(2., 1, 0, 0);
	Monomial m2(1.5, 0, 1, 0);
	Polynomial p1 = Polynomial(m1) + Polynomial(m2);
	parser p;
	Polynomial p2 = p.pars("+2.25x^0y^2z^0 + 6.x^1y^1z^0 + 4.x^2y^0z^0");
	EXPECT_EQ(p2,p1 * p1);
}
