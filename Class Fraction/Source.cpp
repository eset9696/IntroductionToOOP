#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class Fraction;
int calcNOD(int a, int b);
int calcDenominator(double value);
Fraction operator+(Fraction left, Fraction right);
Fraction operator-(Fraction left, Fraction right);
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);
bool operator<(Fraction left, Fraction right);
bool operator>(Fraction left, Fraction right);
bool operator==(Fraction left, Fraction right);
bool operator!=(const Fraction& left, const Fraction& right);
bool operator<=(const Fraction& left, const Fraction& right);
bool operator>=(const Fraction& left, const Fraction& right);

class Fraction {

	int integer;
	int numerator;
	int denominator;

public:

	int getInteger()const {
		return integer;
	}

	int getNumerator()const {
		return numerator;
	}

	int getDenominator()const {
		return denominator;
	}

	void setInteger(int integer) {
		this->integer = integer;
	}

	void setNumerator(int numerator) {
		this->numerator = numerator;
	}

	void setDenominator(int denominator) {
		if (denominator == 0) denominator = 1;
		this->denominator = denominator;
	}

	// Constructiors
	Fraction() {
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "Defoult Constructor:\t\t" << this << endl;
	}

	Fraction(int integer) {
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1 Parameter Constructor:\t" << this << endl;
	}

	Fraction(double value) {
		this->denominator = calcDenominator(value);
		this->integer = int(value);
		this->numerator = (value - int(value)) * denominator;
		cout << "1 Parameter double Constructor: " << this << endl;
	}

	Fraction(char* buffer) {
		int denom = 1;
		int pos = INT_MAX;
		char substr_int[256] = {};
		char substr_numer[256] = {};
		for (int i = 0, j = 0; buffer[i]; i++) {
			if (buffer[i] == '.') {
				pos = i;
			}
			if(i < pos){
				substr_int[i] = buffer[i];
			}
			else if(i > pos) {
				substr_numer[j++] = buffer[i];
				denom *= 10;
			}
		}
		/*for (int i = 0; i < pos; i++) { substr_int[i] = buffer[i]; }
		for (int i = pos + 1, j = 0; buffer[i]; i++, j++) {
			substr_numer[j] = buffer[i];
			denom *= 10;
		}*/
		this->integer = atoi(buffer);
		this->numerator = atoi(substr_numer);
		this->denominator = denom;
		cout << "1 Parameter from char* Constructor: " << this << endl;
	}

	Fraction(int numerator, int denominator) {
		this->integer = 0;
		this->numerator = numerator;
		setDenominator(denominator);
		cout << "2 Parameters Constructor:\t" << this << endl;
	}

	Fraction(int integer, int numerator, int denominator) {
		this->integer = integer;
		this->numerator = numerator;
		setDenominator(denominator);
		cout << "3 Parameters Constructor:\t" << this << endl;
	}

	Fraction(const Fraction& other) {
		this->integer = other.getInteger();
		this->numerator = other.getNumerator();
		setDenominator(other.getDenominator());
		cout << "Copy constructor:\t\t" << this << endl;
	}

	~Fraction() { 
		cout << "Destructor:\t\t\t" << this << endl; 
	}

	//Operators
	Fraction& operator=(const Fraction& other) {
		this->integer = other.getInteger();
		this->numerator = other.getNumerator();
		setDenominator(other.getDenominator());
		cout << "Copy Assignment:\t\t" << this << endl;
		return *this;
	}

	Fraction& operator+=(const Fraction& other) {
		
		return *this = *this + other;
	}

	Fraction& operator-=(const Fraction& other) {
		
		*this = *this - other;
		reduce();
		return *this;
	}

	Fraction& operator*=(const Fraction& other) {
		
		return *this = *this * other;
	}

	Fraction& operator/=(const Fraction& other) {
		
		return *this = *this / other;
	}

	Fraction& operator-() {
		toImproper();
		numerator *= -1;
		return this->toProper();
	}

	Fraction& operator++() { //Prefix increment
		integer++;
		return *this;
	}

	Fraction operator++(int) { //Postfix increment
		Fraction old = *this;
		integer++;
		return old;
	}

	Fraction& operator--() {
		integer--;
		return *this;
	}

	Fraction operator--(int) {
		Fraction old = *this;
		integer--;
		return old;
	}

	//Methods
	void print() {
		if (integer) cout << integer;
		if (numerator) {
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0) cout << 0;
		cout << endl;
	}

	Fraction& toProper() {
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}

	Fraction& toImproper() {
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}

	Fraction Inverted()const {
		Fraction inverted = *this;
		inverted.toImproper();
		std::swap(inverted.numerator, inverted.denominator);
		return inverted;
	}

	Fraction& reduce() {
		this->toProper();
		for (int i = 2; i <= this->numerator;) {
			if (this->numerator % i == 0 && this->denominator % i == 0) {
				this->numerator /= i;
				this->denominator /= i;
			}
			else i++;
		}
		return *this;
	}

	Fraction& reduceEVKLD_KOA() { // Эвклид Олега Анатольевича
		toProper();
		int more, less, rest;
		more = denominator;
		less = numerator;
		if (less == 0) return *this;
		do{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; //Greatest common Divisor - наибольший общий делитель
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}

	Fraction& reduceEVKLD() {
		toProper();
		int nod = calcNOD(numerator, denominator);
		numerator /= nod;
		denominator /= nod;
		return *this;
	}
};

//Functions
int calcNOD(int a, int b) {
	if (a != 0) {
		calcNOD(b % a, a);
	}
	else {
		return a + b;
	}
}

int calcDenominator(double value) {
	bool check = 1;
	int denominator = 1;
	while (check) {
		int int_val = value;
		if (int_val != value) {
			denominator *= 10;
			value *= 10;
		}
		else {
			check = 0;
		}
	}
	return denominator;
}

double toDoubleNumber(const char* buffer) {
	double result = 0;
	int denominator = 1;
	int pos = 0;
	char substr_int[256] = {};
	char substr_numer[256] = {};
	for (int i = 0; buffer[i]; i++) {
		if(buffer[i] == '.'){
			pos = i;
		}
	}
	for (int i = 0; i < pos; i++) {substr_int[i] = buffer[i];}
	for (int i = pos + 1; buffer[i]; i++) { 
		substr_numer[i] = buffer[i];
		denominator *= 10;
	}

	return result;
}
Fraction operator+(Fraction left, Fraction right) {

	left.toImproper();
	right.toImproper();
	return Fraction
	(
		left.getNumerator() * right.getDenominator() + right.getNumerator() * left.getDenominator(),
		left.getDenominator() * right.getDenominator()
	).toProper().reduceEVKLD();
}

Fraction operator-(Fraction left, Fraction right) {
	return Fraction(left + -right);
}

Fraction operator*(Fraction left, Fraction right) {
	left.toImproper();
	right.toImproper();
	return Fraction
	(
		left.getNumerator() * right.getNumerator(),
		left.getDenominator() * right.getDenominator()
	).toProper().reduceEVKLD();
}

Fraction operator/(Fraction left, Fraction right) {
	return Fraction(left * right.Inverted());
}

bool operator<(Fraction left, Fraction right) {
	left.toImproper();
	right.toImproper();
	return left.getNumerator() * right.getDenominator() < right.getNumerator() * left.getDenominator();
}

bool operator>(Fraction left, Fraction right) {
	left.toImproper();
	right.toImproper();
	return left.getNumerator() * right.getDenominator() > right.getNumerator() * left.getDenominator();
}

bool operator==(Fraction left, Fraction right) {
	left.toImproper();
	right.toImproper();
	return left.getNumerator() * right.getDenominator() == right.getNumerator() * left.getDenominator();
}

bool operator!=(const Fraction& left, const Fraction& right) {
	return !(left == right);
}

bool operator<=(const Fraction& left, const Fraction& right) {
	return !(left > right);
}

bool operator>=(const Fraction& left, const Fraction& right) {
	return !(left < right);
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj){
	if (obj.getInteger()) os << obj.getInteger();
	if (obj.getNumerator()) {
		if (obj.getInteger())os << "(";
		os << obj.getNumerator() << "/" << obj.getDenominator();
		if (obj.getInteger())os << ")";
	}
	else if (obj.getInteger() == 0) os << 0;
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& obj) {
	/*int integer, numerator, denominator;

	is >> integer >> numerator >> denominator;

	obj.setInteger(integer);
	obj.setNumerator(numerator);
	obj.setDenominator(denominator);*/

	const int SIZE = 256;
	char buffer[SIZE] = {};
	
	is >> buffer;

	int number[3] = {};

	int n = 0;  //counter of entered numbers

	for (int i = 0; buffer[i]; i++) {
		if(buffer[i] == '.'){
			obj = Fraction(buffer);
			return is;
		}
	}

	char delimeters[] = "()/";
	for(char* pch = strtok(buffer, delimeters); pch; pch = strtok(NULL, delimeters)) {
		number[n++] = atoi(pch);
	}

	switch(n) {
	case 1: 
		obj = Fraction(number[0]);
		break;
	case 2:
		obj = Fraction(number[0], number[1]);
		break;
	case 3:
		obj = Fraction(number[0], number[1], number[2]);
		break;
	}
	return is;
}

//#define CONSTRUCTORS_CHECK
//#define METHODS_CHECK
//#define OPERATORS_CHECK
//#define FUNCTIONS_CHECK
//#define INCREMENT_CHECK
//#define INPUT_CHECK_1
//#define INPUT_CHECK_2
void main() {
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A;
	A.print();

	Fraction B(5);
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	Fraction E = D;
	E.print();

	Fraction F(2, 11, 5);
	F = B;
	F.print();

#endif // CONSTRUCTORS_CHECK

#ifdef METHODS_CHECK
	Fraction A(1, 3);
	A.print();
	Fraction B(5, 11);
	Fraction D = A;
	bool a;
	a = A <= B;
	cout << "A <= B: " << a << endl;
	a = A >= B;
	cout << "A >= B: " << a << endl;
	a = A == B;
	cout << "A == B: " << a << endl;
#endif // METHODS_CHECK

#ifdef OPERATORS_CHECK
	Fraction A(2, 3, 4);
	Fraction B(3, 16, 20);
	A.print();
	B.print();
	A *= B;
	A.print();
	A -= B;
	A.print();
	A *= B;
	A.print();
	A /= B;
	A.print();
	B.print();
	cout << A << "\t" << B << endl;
#endif // OPERATORS_CHECK

#ifdef FUNCTIONS_CHECK
	Fraction A(3, 2, 3);
	Fraction B(1, 3, 5);
	A.print();
	B.print();
	Fraction C;
	C = (A + B);
	A.print();
	B.print();
	C.print();
	C = C - B;
	A.print();
	B.print();
	C.print();
	C = A * B;
	A.print();
	B.print();
	C.print();
	C = A / B;
	A.print();
	B.print();
	C.print();
#endif // FUNCTIONS_CHECK

#ifdef INCREMENT_CHECK
	Fraction A(1, 3, 4);
	A.print();
	++A;
	A.print();
	A++;
	A.print();
	--A;
	A.print();
	A--;
	A.print();
#endif // INCREMENT_CHECK

	/*Fraction A(840, 3600);
	
	A.print();
	A.reduceEVKLD_KOA();
	A.print();*/

	
#ifdef INPUT_CHECK_1
	Fraction A;
	cout << "Введите простую дробь:\t";
	cin >> A;
	A.print();
	A.reduce();
	A.print();
#endif // INPUT_CHECK_1
	
#ifdef INPUT_CHECK_2
	Fraction A, B, C;
	cin >> A >> B >> C;
	A.print();
	B.print();
	C.print();
#endif // INPUT_CHECK_2
	//int a = 3; // No converion
	//double b = 3; // Conversion from less to more
	//int c = b; // Convrion from more to less without data loss
	//int d = 4.5; // Convrion from more to less with data loss
	Fraction A;
	cin >> A;
	cout << A << endl;
}
