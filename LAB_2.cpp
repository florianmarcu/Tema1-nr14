#include <iostream>
#include "Polinom.h"

using namespace std;

int main()
{
	Polinom* P = new Polinom();
	//P->input();
	cin >> *P;
	cout << P->polinomOfX(10)<<endl;
	//cin >> *P;
	//cout << P->polinomOfX(1) << endl;
	cout << *P;
}

