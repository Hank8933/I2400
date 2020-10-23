// HW5.cpp : 定義主控台應用程式的進入點。
//

#include <tchar.h>
#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm {
public:
	int coef;
	int expo;
};                                                                          /////

class ArrayPolynomial {                                        /////
public:                                                                  /////
	PolynomialTerm terms[MAX_TERMS]; /////

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputTerms(int coef, int expo) /////
	{
		PolynomialTerm tmp;

		for (int i = 0; i < MAX_TERMS; i++) {
			if (terms[i].expo == expo) {
				if (coef) {
					terms[i].coef = coef;
					return;
				}
				for (int j = i; j < MAX_TERMS - 1; j++) {
					terms[j] = terms[j + 1];
				}
				return;
			}
			if (terms[i].expo < expo && coef) {
				tmp = terms[i];
				terms[i] = { coef, expo };
				expo = tmp.expo;
				coef = tmp.coef;
			}
		}

		return;
	}

	void addArrayBasedPoly(ArrayPolynomial& a, ArrayPolynomial& b) /////
	{
		for (int i = 0, j = 0, k = 0; i < MAX_TERMS && j < MAX_TERMS; k++) {
			if (a.terms[i].expo > b.terms[j].expo) {
				terms[k] = { a.terms[i].coef, a.terms[i].expo };
				i++;
			}
			else if (a.terms[i].expo == b.terms[j].expo) {
				terms[k] = { a.terms[i].coef + b.terms[j].coef, a.terms[i].expo };
				if (!terms[k].coef)
					k--;
				i++;
				j++;
			}
			else {
				terms[k] = { b.terms[j].coef, b.terms[j].expo };
				j++;
			}
		}

		return;
	}

	void reverseArrayBasedPoly() /////
	{
		int len = 0;

		while (terms[len++].coef);
		len--;
		
		for (int i = 0; i < len / 2; i++) {
			PolynomialTerm tmp = terms[i];
			terms[i] = terms[len - i - 1];
			terms[len - i - 1] = tmp;
		}

		return;
	}

	void printArrayBasedPoly() /////
	{
		if (terms[0].coef == 0)
			return;

		if (terms[0].expo == 0)
			std::cout << terms[0].coef;
		else
			std::cout << terms[0].coef << "X^" << terms[0].expo;

		for (int i = 1; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0)
				return;

			if (terms[i].expo == 0)
				std::cout << " + " << terms[i].coef;
			else
				std::cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}

		return;
	}

	int compute(int x)
	{
		int ret = 0;

		for (int i = 0; terms[i].coef; i++) {
			ret += terms[i].coef * pow(x, terms[i].expo);
		}
		
		return ret;
	}
};

class LinkedPolynomialTerm {
public:
	int coef;
	int expo;
	LinkedPolynomialTerm* nextTermPtr; /////
};                                                                  /////

class LinkPolynomial {                                /////
public:                                                          /////
	LinkedPolynomialTerm* polynomialTermPtr = nullptr; /////

	void clear() /////
	{
		LinkedPolynomialTerm* tmpPtr;

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputLinkTerms(int coef, int expo) /////
	{
		LinkedPolynomialTerm* tmpPtr;

		tmpPtr = new LinkedPolynomialTerm;
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;

		if (!polynomialTermPtr || polynomialTermPtr->expo <= expo) {  // 擺第一
			if (polynomialTermPtr && polynomialTermPtr->expo == expo) { // 重複取代
				if (coef) {
					tmpPtr->nextTermPtr = polynomialTermPtr->nextTermPtr;
				}
				else {
					tmpPtr = polynomialTermPtr->nextTermPtr;
				}
			}
			else if (!coef)
				return;
			else
				tmpPtr->nextTermPtr = polynomialTermPtr;
			polynomialTermPtr = tmpPtr;
		}
		else {
			LinkedPolynomialTerm* tmp = polynomialTermPtr;
			while (true) {
				if (tmp->nextTermPtr && tmp->nextTermPtr->expo <= expo) {  // 擺中間
					if (tmp->nextTermPtr->expo == expo) {  // 重複取代
						if (coef) {
							tmpPtr->nextTermPtr = tmp->nextTermPtr->nextTermPtr;
						}
						else {
							tmpPtr = tmp->nextTermPtr->nextTermPtr;
						}
					}
					else if (!coef) break;
					else
						tmpPtr->nextTermPtr = tmp->nextTermPtr;
					tmp->nextTermPtr = tmpPtr;
					break;
				}
				else if (!tmp->nextTermPtr) {  // 擺最後
					if (coef) {
						tmp->nextTermPtr = tmpPtr;
						tmpPtr->nextTermPtr = nullptr;
					}
					break;
				}
				tmp = tmp->nextTermPtr;
			}
		}

		return;
	}

	void addLinkBasedPoly(LinkPolynomial& aPol, LinkPolynomial& bPol) /////
	{
		LinkedPolynomialTerm
			* tmp = polynomialTermPtr,
			* aPtr = aPol.polynomialTermPtr,
			* bPtr = bPol.polynomialTermPtr;

		while (aPtr || bPtr) {
			if ((aPtr && !bPtr) || ((aPtr && bPtr) && aPtr->expo > bPtr->expo)) {
				if (!tmp) {
					tmp = polynomialTermPtr = new LinkedPolynomialTerm{ aPtr->coef, aPtr->expo };
				}
				else {
					tmp->nextTermPtr = new LinkedPolynomialTerm{ aPtr->coef, aPtr->expo };
					tmp = tmp->nextTermPtr;
				}
				aPtr = aPtr->nextTermPtr;
			}
			else if ((aPtr && bPtr) && aPtr->expo == bPtr->expo) {
				if (!tmp) {
					if (aPtr->coef + bPtr->coef)
						tmp = polynomialTermPtr = new LinkedPolynomialTerm{ aPtr->coef + bPtr->coef, aPtr->expo };
				}
				else if (aPtr->coef + bPtr->coef) {
					tmp->nextTermPtr = new LinkedPolynomialTerm{ aPtr->coef + bPtr->coef, aPtr->expo };
					tmp = tmp->nextTermPtr;
				}
				aPtr = aPtr->nextTermPtr;
				bPtr = bPtr->nextTermPtr;
			}
			else {
				if (!tmp) {
					tmp = polynomialTermPtr = new LinkedPolynomialTerm{ bPtr->coef, bPtr->expo };
				}
				else {
					tmp->nextTermPtr = new LinkedPolynomialTerm{ bPtr->coef, bPtr->expo };
					tmp = tmp->nextTermPtr;
				}
				bPtr = bPtr->nextTermPtr;
			}
		}

		return;
	}

	void reverseLinkBasedPoly() /////
	{
		if (!polynomialTermPtr || !polynomialTermPtr->nextTermPtr)
			return;

		LinkedPolynomialTerm
			* pre = nullptr,
			* cur = polynomialTermPtr,
			* next = polynomialTermPtr->nextTermPtr;

		while (next) {
			cur->nextTermPtr = pre;
			pre = cur;
			cur = next;
			next = next->nextTermPtr;
		}
		cur->nextTermPtr = pre;
		polynomialTermPtr = cur;

		return;
	}

	void printLinkBasedPoly()                                                            /////
	{
		LinkedPolynomialTerm* termPtr = polynomialTermPtr; /////

		if (termPtr == nullptr)
			return;

		if (termPtr->expo == 0)
			cout << termPtr->coef;
		else
			cout << termPtr->coef << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;

		while (termPtr != nullptr) {
			if (termPtr->coef == 0)
				return;

			if (termPtr->expo == 0)
				cout << " + " << termPtr->coef;
			else
				cout << " + " << termPtr->coef << "X^" << termPtr->expo;

			termPtr = termPtr->nextTermPtr;
		}

		return;
	}

	int compute(int x)
	{
		int ret = 0;
		LinkedPolynomialTerm* tmp = polynomialTermPtr;

		while (tmp) {
			ret += tmp->coef * pow(x, tmp->expo);
			tmp = tmp->nextTermPtr;
		}

		return ret;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	ArrayPolynomial a, b, d;                                                              /////
	LinkPolynomial aPol, bPol, dPol;                                             /////

	int coef, expo, x;

	// aPtr = bPtr = dPtr = nullptr; /////

	while (1) {
		a.clear(); b.clear(); d.clear();                                    /////
					  // aPtr->clear(aPtr); bPtr->clear(bPtr); dPtr->clear(dPtr); /////


		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			a.inputTerms(coef, expo);             /////
			aPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\na = ";
		a.printArrayBasedPoly();     /////
		cout << "\na = ";
		aPol.printLinkBasedPoly(); /////
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			b.inputTerms(coef, expo);             /////
			bPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\nb = ";
		b.printArrayBasedPoly();      /////

		cout << "\nb = ";
		bPol.printLinkBasedPoly(); /////

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		d.addArrayBasedPoly(a, b); /////
		cout << "\na + b = ";
		d.printArrayBasedPoly();     /////

		dPol.addLinkBasedPoly(aPol, bPol); /////
		cout << "\na + b = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		d.reverseArrayBasedPoly(); /////
		cout << "\nreversed d = ";
		d.printArrayBasedPoly();     /////

		dPol.reverseLinkBasedPoly(); /////
		cout << "\nreversed d = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		cout << "\ninput X: ";
		cin >> x;

		cout << "\nd = ";
		cout << d.compute(x);      //////

		cout << "\nd = ";
		cout << dPol.compute(x); //////

		cout << "\n";

		aPol.clear(); bPol.clear(); dPol.clear(); /////
	}

	return 0;
}
