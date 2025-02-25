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

TEST(Monomial, monomialsWithSimilarPowersAreEqual) {
	Monomial m1(1.2, 2, 3, 4), m2(2.2, 2, 3, 4);
	EXPECT_TRUE(m1 == m2);
}

TEST(Monomial, canCompareMonomials) {
	Monomial m1(1.2, 2, 3, 4), m2(2.2, 3, 3, 4);
	EXPECT_TRUE(m1 < m2);
}

TEST(Monomial, canAddMonomialsWithEqualPowers) {
	Monomial m1(1.2, 2, 3, 4), m2(2.2, 2, 3, 4);
	Monomial m(3.4, 2, 3, 4);
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



TEST(Polynomial, canMakePolynomial) {
	Monomial m1(2., 1, 0, 0);
	Monomial m2(1.5, 0, 1, 0);
	Polynomial p = Polynomial(m1)+ Polynomial(m2);
	
	ASSERT_NO_THROW(p*p);
	std::cout << p*p << "\n";
}

TEST(parser, pars) {
	std::string s = "- 12.x^1y^0z^3 - 3.7x^0y^1z^2 + 3.3x^2y^2z^1";
	parser p;
	ASSERT_NO_THROW(p.pars(s, 0));
	std::cout << p.pars(s, 0);
}