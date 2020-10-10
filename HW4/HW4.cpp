// HW4.cpp : 定義主控台應用程式的進入點。
//

#include <tchar.h>
#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

typedef struct {
	int coef;
	int expo;
} polynomialTerm;

typedef struct linkedTerm {
	int coef;
	int expo;
	linkedTerm* nextTermPtr;
} linkedPolynomialTerm;

void clear(polynomialTerm t[])
{
	for (int i = 0; i < MAX_TERMS; i++) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void clear(linkedPolynomialTerm*& polynomialTermPtr)
{
	linkedPolynomialTerm* tmpPtr;

	while (polynomialTermPtr != nullptr) {
		tmpPtr = polynomialTermPtr;
		polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		delete tmpPtr;
	}
}

void inputTerms(polynomialTerm terms[], int coef, int expo)
{

	polynomialTerm tmp;

	for (int i = 0; i < MAX_TERMS; i++) {
		if (terms[i].expo == expo) {
			terms[i].coef = coef;
			return;
		}
		if (terms[i].expo < expo) {
			tmp = terms[i];
			terms[i] = { coef, expo };
			expo = tmp.expo;
			coef = tmp.coef;
		}
	}

	return;
}

void inputLinkTerms(linkedPolynomialTerm*& polyPtr, int coef, int expo)
{
	linkedPolynomialTerm* tmpPtr;

	tmpPtr = new linkedPolynomialTerm;
	tmpPtr->coef = coef;
	tmpPtr->expo = expo;

	if (!polyPtr || polyPtr->expo <= expo) {  // 擺第一
		if (polyPtr && polyPtr->expo == expo)  // 重複取代
			tmpPtr->nextTermPtr = polyPtr->nextTermPtr;
		else
			tmpPtr->nextTermPtr = polyPtr;
		polyPtr = tmpPtr;
	}
	else {
		linkedPolynomialTerm* tmp = polyPtr;
		while (true) {
			if (tmp->nextTermPtr && tmp->nextTermPtr->expo <= expo) {  // 擺中間
				if (tmp->nextTermPtr->expo == expo)  // 重複取代
					tmpPtr->nextTermPtr = tmp->nextTermPtr->nextTermPtr;
				else
					tmpPtr->nextTermPtr = tmp->nextTermPtr;
				tmp->nextTermPtr = tmpPtr;
				break;
			}
			else if (!tmp->nextTermPtr) {  // 擺最後
				tmp->nextTermPtr = tmpPtr;
				tmpPtr->nextTermPtr = nullptr;
				break;
			}
			tmp = tmp->nextTermPtr;
		}
	}


	return;
}


void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[])
{

	for (int i = 0, j = 0, k = 0; i < MAX_TERMS && j < MAX_TERMS; k++) {
		if (a[i].expo > b[j].expo) {
			d[k] = { a[i].coef, a[i].expo };
			i++;
		}
		else if (a[i].expo == b[j].expo) {
			d[k] = { a[i].coef + b[j].coef, a[i].expo };
			if (!d[k].coef)
				k--;
			i++;
			j++;
		}
		else {
			d[k] = { b[j].coef, b[j].expo };
			j++;
		}
	}

	return;
}

linkedPolynomialTerm* addLinkBasedPoly(linkedPolynomialTerm* aPtr, linkedPolynomialTerm* bPtr)
{
	linkedPolynomialTerm* dPtr = nullptr;

	linkedPolynomialTerm* tmp = dPtr;
	while (aPtr || bPtr) {
		if ((aPtr && !bPtr) || ((aPtr && bPtr) && aPtr->expo > bPtr->expo)) {
			if (!tmp) {
				tmp = dPtr = new linkedPolynomialTerm{ aPtr->coef, aPtr->expo };
			}
			else {
				tmp->nextTermPtr = new linkedPolynomialTerm{ aPtr->coef, aPtr->expo };
				tmp = tmp->nextTermPtr;
			}
			aPtr = aPtr->nextTermPtr;
		}
		else if ((aPtr && bPtr) && aPtr->expo == bPtr->expo) {
			if (!tmp) {
				if (aPtr->coef + bPtr->coef)
					tmp = dPtr = new linkedPolynomialTerm{ aPtr->coef + bPtr->coef, aPtr->expo };
			}
			else if (aPtr->coef + bPtr->coef) {
				tmp->nextTermPtr = new linkedPolynomialTerm{ aPtr->coef + bPtr->coef, aPtr->expo };
				tmp = tmp->nextTermPtr;
			}
			aPtr = aPtr->nextTermPtr;
			bPtr = bPtr->nextTermPtr;
		}
		else {
			if (!tmp) {
				tmp = dPtr = new linkedPolynomialTerm{ bPtr->coef, bPtr->expo };
			}
			else {
				tmp->nextTermPtr = new linkedPolynomialTerm{ bPtr->coef, bPtr->expo };
				tmp = tmp->nextTermPtr;
			}
			bPtr = bPtr->nextTermPtr;
		}
	}


	return dPtr;
}

void printArrayBasedPoly(polynomialTerm terms[])
{
	if (terms[0].coef == 0)
		return;

	if (terms[0].expo == 0)
		cout << terms[0].coef;
	else
		cout << terms[0].coef << "X^" << terms[0].expo;

	for (int i = 1; i < MAX_TERMS; i++) {
		if (terms[i].coef == 0)
			return;

		if (terms[i].expo == 0)
			cout << " + " << terms[i].coef;
		else
			cout << " + " << terms[i].coef << "X^" << terms[i].expo;
	}
}

void printLinkBasedPoly(linkedPolynomialTerm* polyPtr)
{
	linkedPolynomialTerm* termPtr = polyPtr;

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
}

int _tmain(int argc, _TCHAR* argv[])
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	linkedPolynomialTerm* aPtr, * bPtr, * dPtr;

	int coef, expo;

	aPtr = bPtr = dPtr = nullptr;

	while (1) {
		clear(a); clear(b); clear(d);
		clear(aPtr); clear(bPtr); clear(dPtr);

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(a, coef, expo);
			inputLinkTerms(aPtr, coef, expo);
		}

		cout << "\n\na = ";
		printArrayBasedPoly(a);
		cout << "\na = ";
		printLinkBasedPoly(aPtr);
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(b, coef, expo);
			inputLinkTerms(bPtr, coef, expo);
		}

		cout << "\n\nb = ";
		printArrayBasedPoly(b);

		cout << "\nb = ";
		printLinkBasedPoly(bPtr);

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		addArrayBasedPoly(a, b, d);
		cout << "\na + b = ";
		printArrayBasedPoly(d);

		dPtr = addLinkBasedPoly(aPtr, bPtr);
		cout << "\na + b = ";
		printLinkBasedPoly(dPtr);

		cout << "\n";
	}
	return 0;
}
