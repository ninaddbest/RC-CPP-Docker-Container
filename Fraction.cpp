#include <iostream>
#include<string>
#include "Fraction.h"
using namespace std;


Fraction::Fraction(int a, int b)
{
    numerator=a;
    denominator=b;
}

Fraction Fraction::reciprocal()
{
    return Fraction(denominator, numerator);
}

Fraction Fraction::multiply(int c)
{
    return Fraction(numerator * c, denominator);
}

double Fraction::todouble()
{
    return static_cast<double>(numerator) / denominator;
}

string Fraction::tostring()
{
if(numerator==0)
{
    cout << "The fraction is 0";
}
else
{
cout << "The Fraction is " << numerator << "/" << denominator;

}

return "Exit";
}
