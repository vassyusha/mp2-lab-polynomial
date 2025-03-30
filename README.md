# Лабораторная работа по предмету АиСД "Полиномы"

## Что надо реализовать?

Надо реализовать класс Полином, который будет хранить объекты вида
`k1 * x^n1 * y^m1 * z^p1 + k2 * x^n2 * y^m2 * z^p2 + ...`,
где `ki - коэффициент типа double;
0 <= ni, mi, pi <= 9 - натуральные степени соответственного монома.`

Подобных мономов в полиноме нет.

В классе должны быть реализованы сложение, вычитание, умножение, умножение на константу.

Также необходимо обеспечить возможность ввода полинома с клавиатуры.

## План работы

1. Реализовать класс Моном

2. На основе класса Моном, реализовать класс Полином

3. Реализовать считывание Полинома

