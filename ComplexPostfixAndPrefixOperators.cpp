#include <iostream>

using namespace std;

class Complex
{
private:
	float r;
	float i;

public:
	Complex(const float r, const float i) {
		this->r = r;
		this->i = i;
	}

	Complex operator++(int) {
		r += 1;
		return *this;
	}

	Complex& operator++(void) {
		r += 1;
		return *this;
	}

	friend ostream& operator<<(ostream& os, const Complex& c) {
		os << "(" << c.r << ", " << c.i << ")";
		return os;
	}
};

int main() {
	Complex c(1, 2);

	cout << c++;

	return 0;
}
