#include <iostream>
#include <cmath>

using namespace std;

struct ComplexNum
{
    double real;
    double imaginary;
};

ComplexNum addCompNum (ComplexNum& c1, ComplexNum& c2)
{
    ComplexNum newc = {c1.real + c2.real, c1.imaginary, c2.imaginary};
    return newc;
}

void printCompNUm (ComplexNum& c)
{
    double a = c1.real, b = c1.imaginary;
    double r = sqrt(a * a + b * b),
           cosa = a / r,
           sina = b / r;
    cout << "c = " << a << " + i * " << b << '\n'
         << "c = " << r << " * ( cos " << c1.imaginary << " + i * sin " << sina << " )" << '\n';
}

int main()
{
    return 0;
}
