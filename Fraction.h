#ifndef FRACTION_H
#define FRACTION_H
#include<string>
using namespace std;
class Fraction
{
    private:
        int numerator, denominator;
    public:
        Fraction(int a, int b);
        Fraction reciprocal();
        Fraction multiply(int c);
        double todouble();
        string tostring();
};
#endif
