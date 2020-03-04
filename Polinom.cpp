#include "Polinom.h"
using namespace std;

// afiseza intregul polinom
ostream& operator<<(ostream& output, const Polinom& P) {
	const Polinom* p = &P;
	while (p) {
		if (p != &P)
			output << "+ ";
		output << p->coef << "*x^" << p->exp << " ";
		p = p->next;
	}
	return output;
}
// citeste o pereche (coef,exp) despartite prin cate un spatiu
istream& operator>>(istream& input, Polinom& P) {
	double coef;
	int exp;
	input >> coef >> exp;
	if (P.exp == 0 and P.coef == 0) {
		P.exp = exp;
		P.coef = coef;
	}
	else P.Add(coef, exp);
	return input;
}

Polinom::Polinom(double coef, int exp) {
	this->coef = coef;
	this->exp = exp;
	this->next = NULL;
}

Polinom::Polinom(Polinom& P) {
	this->coef = P.coef;
	this->exp = P.exp;
	this->next = P.next;
}

// Adauga un element in polinom
void Polinom::Add(double coef, int exp) {
	Polinom* p = this;
	Polinom* aux = new Polinom(coef, exp);
	if (p->exp > aux->exp) {
		swap(p->coef, aux->coef);
		swap(p->exp, aux->exp);
		while (p->next) {
			p = p->next;
			swap(p->coef, aux->coef);
			swap(p->exp, aux->exp);
		}
		p->next = new Polinom(aux->coef, aux->exp);
	}
	else {
		while (p->next != NULL and p->next->exp < aux->exp)
			p = p->next;
		aux->next = p->next;
		p->next = aux;
	}
}
// Citeste n perechi (coef,exp) de la tastatura
void Polinom::input() {
	Polinom* p = this;
	cout << "N = ";
	int n;
	cin >> n;
	double coef;
	int exp;
	for (int i = 0; i < n; i++) {
		cin >> coef >> exp;
		if (i == 0) {
			this->coef = coef;
			this->exp = exp;
		}
		else p->Add(coef, exp);
	}
}
// Calculeaza valorea polinomului in variabila x
double Polinom::polinomOfX(double x) {
	Polinom* p = this;
	double sum = 0;
	while (p) {
		sum += p->coef * pow(x, p->exp);
		//cout<< p->coef << "*x^" << p->exp << "+";
		p = p->next;
	}
	//cout << " = ";
	return sum;
}

Polinom& Polinom::operator+(Polinom& P) {

	Polinom* aux = new Polinom(); ///folosit pentru a crea noul polinom 
	Polinom* root = aux; ///folosit pentru a returna adresa de inceput a polinomului suma
	aux->next = NULL;
	Polinom* U = this;
	Polinom* V = &P;
	while (U && V) {
		if (U->exp > V->exp) {
			aux->next = new Polinom(V->coef, V->exp);
			V = V->next;
		}
		else if (U->exp < V->exp) {
			aux->next = new Polinom(U->coef, U->exp);
			U = U->next;
		}
		else {
			aux->next = new Polinom(U->coef + V->coef, U->exp);
			U = U->next;
			V = V->next;
		}
		aux = aux->next;
	}
	while (U) {
		aux->next = new Polinom(U->coef, U->exp);
		aux = aux->next;
		U = U->next;
	}
	while (V) {
		aux->next = new Polinom(V->coef, V->exp);
		aux = aux->next;
		V = V->next;
	}
	return *root;
}

Polinom& Polinom::operator-(Polinom& P) {
	Polinom* aux = new Polinom(); ///folosit pentru a crea noul polinom 
	Polinom* root = aux; ///folosit pentru a returna adresa de inceput a polinomului suma
	aux->next = NULL;
	Polinom* U = this;
	Polinom* V = &P;
	while (U && V) {
		if (U->exp > V->exp) {
			aux->next = new Polinom(-1 * (V->coef), V->exp);
			V = V->next;
		}
		else if (U->exp < V->exp) {
			aux->next = new Polinom(U->coef, U->exp);
			U = U->next;
		}
		else {
			aux->next = new Polinom(U->coef - V->coef, U->exp);
			U = U->next;
			V = V->next;
		}
		aux = aux->next;
	}
	while (U) {
		aux->next = new Polinom(U->coef, U->exp);
		aux = aux->next;
		U = U->next;
	}
	while (V) {
		aux->next = new Polinom(-1 * (V->coef), V->exp);
		aux = aux->next;
		V = V->next;
	}
	return *root;
}

Polinom& Polinom::operator*(Polinom& P) {
	Polinom* aux = new Polinom(0, 0); ///folosit pentru a crea noul polinom 
	Polinom* root = aux; ///folosit pentru a returna adresa de inceput a polinomului suma
	aux->next = NULL;
	Polinom* U = this;
	Polinom* V;
	/// x^2+x^3+x^5
	/// x^1+x^4+x^5
	while (U) {
		V = &P;
		Polinom* temp = new Polinom();
		Polinom* tempRoot;
		temp->next = NULL;
		tempRoot = temp;
		while (V) {
			temp->Add(U->coef * V->coef, U->exp + V->exp);
			temp = temp->next;
			V = V->next;
		}
		*aux = *aux + *tempRoot;
	}
	return *aux;
}