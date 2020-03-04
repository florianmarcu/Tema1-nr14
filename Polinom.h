#include <iostream>
using namespace std;

class Polinom {
	double coef;
	int exp;
	Polinom* next;
public:
	//Polinom();
	Polinom(double coef = 0, int exp = 0);
	Polinom(Polinom&);
	double polinomOfX(double);
	void Add(double, int);
	void input();
	Polinom& operator+(Polinom&);
	Polinom& operator-(Polinom&);
	Polinom& operator*(Polinom&);
	friend ostream& operator<<(ostream&, const Polinom&);
	friend istream& operator>>(istream&, Polinom&);
};