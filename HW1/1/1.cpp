// HW1.cpp : 定義主控台應用程式的進入點。
//

// #include "stdafx.h"
#include <tchar.h> 

#include <iostream>
#include <string>

using namespace std;

void input(string sMessage, string& sInputString)
{
	cout << sMessage << endl;
	cin >> sInputString;

	return;
}

void writeBackwardI(string s)
{
	int length = s.size();

	if (length == 0)  // base case 
		return;

	for (int i = length - 1; i >= 0; i--)
		cout << s[i];
}

void writeBackwardR1(string s)
{
	int length = s.size();

	if (length == 0)  // base case 
		return;

	cout << s[length - 1];
	writeBackwardR1(s.substr(0, length - 1));
}

void writeBackwardR2(string s)
{
	int length = s.size();

	if (length == 0)  // base case 
		return;

	writeBackwardR2(s.substr(1, length - 1));
	cout << s[0];
}


int countI(string s, char c)
{
	int length = s.size();
	int sum = 0;

	for (int i = 0; i < length; i++) {
		if (s[i] == c) sum++;
	}

	return sum;
}

int countR(string s, char c)
{
	int length = s.size();

	if (length == 0) return 0;
	

	return ((s[length - 1] == c) ? 1 : 0) + countR(s.substr(0, length - 1), c);
}

unsigned char findI(string s)
{
	int length = s.size();

	for (int i = 1; i < length; i++) {
		if (s[i] < s[0]) s[0] = s[i];
	}

	return s[0];
}

char findR(string s)
{
	int length = s.size();

	if (length == 1) return s[0];

	if (s[length - 1] < s[0]) s[0] = s[length - 1];

	return findR(s.substr(0, length - 1));
}

string removeI(string s)
{
	int length = s.size();

	for (int i = 0; i < length-1; i++) {
		if (s[i] == s[i + 1]) {
			for (int j = i; j < length-1; j++) {
				s[j] = s[j + 1];
			}
			s[length - 1] = '\0';
			i--;
			length--;
		}
	}

	return s;
}

string removeR2(string s, int i)
{
	if (i == 0) return s;
	int length = s.size();

	if (s[i] == s[i - 1]) {
		for (int j = i; j < length; j++) {
			s[j] = s[j + 1];
		}
		return removeR2(s, i);
	}
	return removeR2(s, --i);
}

string removeR(string s)
{
	int length = s.size();

	s = removeR2(s, length - 1);

	return s;
}

int TI(int m, int n)
{
	int ret = 0;
	int tmp;
	if (n > m) {
		tmp = n;
		n = m;
		m = tmp;
	}

	for (int i = 0; i < n; i++) {
		ret += m;
	}

/*
	T(m, n) = 0, if m = 0 or n = 0
	T(m, n) = m + ... + m (n times), if m > n
	T(m, n) =  n + ... + n (m times), otherwise
*/

	return ret;
}

int TR(int m, int n)
{
	if (m == 0 || n == 0) return 0;

	int tmp;
	if (n > m) {
		tmp = n;
		n = m;
		m = tmp;
	}
/*
	T(m, n) = 0, if m = 0 or n = 0
	T(m, n) = m + T( m, n - 1 ), if m > n
	T(m, n) =  n + T( m - 1, n ), otherwise
*/
	return m + TR(m, n - 1);
}

int _tmain(int argc, _TCHAR* argv[])
{
	string commandStr;
	string inputStr, appendStr;
	char inputChr;
	int m, n;

	while (1) {
		input("\nEnter command: "
			"\n I to input a string, A to append a string, B to write the string backward, "
			"\n C to count the given character , F to find the smallest character,"
			"\n R to remove the repeated characters, T to compute, and X to Exit", commandStr);

		if (commandStr == "I" || commandStr == "i") {
			cout << "\nInput the string: ";
			cin >> inputStr;
		}
		else if (commandStr == "A" || commandStr == "a") {
			cout << "\nInput the string: ";
			cin >> appendStr;
			inputStr += appendStr;
			cout << "\nThe new string: " << inputStr << endl;
		}
		else if (commandStr == "B" || commandStr == "b") {
			if (inputStr.length() > 0) {
				cout << endl;
				writeBackwardI(inputStr);
				cout << endl;
				writeBackwardR1(inputStr);
				cout << endl;
				writeBackwardR2(inputStr);
				cout << endl;
			}
		}
		else	if (commandStr == "C" || commandStr == "c") {
			if (inputStr != "") {
				cout << "\nInput the character: ";
				cin >> inputChr;
				cout << "\nCount of " << inputChr << ": " << countI(inputStr, inputChr);
				cout << "\nCount of " << inputChr << ": " << countR(inputStr, inputChr) << endl;
			}
		}
		else if (commandStr == "R" || commandStr == "r") {
			if (inputStr != "") {
				cout << endl << "Repeated characters removed: " << removeI(inputStr);
				cout << endl << "Repeated characters removed: " << removeR(inputStr) << endl;;
			}
		}
		else if (commandStr == "F" || commandStr == "f") {
			if (inputStr != "") {
				cout << endl << "Smallest character found: " << findI(inputStr);
				cout << endl << "Smallest character found: " << findR(inputStr) << endl;
			}
		}
		else  if (commandStr == "T" || commandStr == "t")
		{
			cout << "\nInput two values, m and n: ";
			cin >> m >> n;
			cout << endl << "The result is " << TI(m, n);
			cout << endl << "The result is " << TR(m, n) << endl;
		}
		else  if (commandStr == "X" || commandStr == "x")
			return 0;
		else
			cout << "\nUnknown command!";
	}
	return 0;
}
