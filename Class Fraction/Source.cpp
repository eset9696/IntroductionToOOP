#include <iostream>

using namespace std;

class Fraction;
int calcNOD(int a, int b);
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
		this->integer = round(value);
		this->numerator = 0;
		this->denominator = 1;
		cout << "1 Parameter Constructor:\t" << this << endl;
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
	~Fraction() { cout << "Destructor:\t\t\t" << this << endl; }
	//Operators
	Fraction& operator=(const Fraction& other) {
		this->integer = other.getInteger();
		this->numerator = other.getNumerator();
		setDenominator(other.getDenominator());
		cout << "Copy Assignment:\t\t" << this << endl;
		return *this;
	}
	Fraction& operator+=(const Fraction& other) {
		/*this->integer += other.getInteger();
		this->numerator = this->numerator * other.getDenominator() + other.getNumerator() * this->denominator;
		this->denominator *= other.getDenominator();
		this->reduce();*/
		return *this = *this + other;
	}
	Fraction& operator-=(const Fraction& other) {
		/*int buffer = other.getNumerator() + other.getInteger() * other.getDenominator();
		this->toImproper();
		this->numerator = this->numerator * other.getDenominator() - buffer * this->denominator;
		this->denominator *= other.getDenominator();
		this->reduce();
		return *this;*/
		*this = *this - other;
		reduce();
		return *this;
	}
	Fraction& operator*=(const Fraction& other) {
		/*int buffer = other.getNumerator() + other.getInteger() * other.getDenominator();
		this->toImproper();
		this->numerator = this->numerator * buffer;
		this->denominator *= other.getDenominator();
		this->reduce();
		return *this;*/
		return *this = *this * other;
	}
	Fraction& operator/=(const Fraction& other) {
		/*int buffer = other.getNumerator() + other.getInteger() * other.getDenominator();
		this->toImproper();
		this->numerator = this->numerator * other.getDenominator();
		this->denominator *= buffer;
		this->reduce();
		return *this;*/
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
		/*if(this->numerator >= this->denominator){
			this->integer = this->integer + this->numerator / this->denominator;
			this->numerator = this->numerator % this->denominator;
		}else if(-this->numerator >= this->denominator){
			this->integer = -(this->integer + -this->numerator / this->denominator);
			this->numerator = -(this->numerator % this->denominator);
		}*/
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
int& getIntFromConsole(std::istream& os){
	int value;
	bool isCorrectInput;
	do { //Проверка на дурака
		os >> value;
		if (!(isCorrectInput = cin.good())) {
			cin.clear(), cin.ignore();
			cout << "Введено некорректное значение, введите целое число: \t" << endl;
		}
	} while (!isCorrectInput);
	return value;
}
std::istream& operator>>(std::istream& os, Fraction& obj) {
	int integer, numerator, denominator;
	cout << "Введите целую часть дроби: \t" << endl;
	integer = getIntFromConsole(os);
	cout << "Введите числитель дроби: \t" << endl;
	numerator = getIntFromConsole(os);
	cout << "Введите знаменатель дроби: \t" << endl;
	denominator = getIntFromConsole(os);
	obj.setInteger(integer), obj.setNumerator(numerator), obj.setDenominator(denominator);
	return os;
}
//#define CONSTRUCTORS_CHECK
//#define METHODS_CHECK
//#define OPERATORS_CHECK
//#define FUNCTIONS_CHECK
//#define INCREMENT_CHECK
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
	Fraction A;
	cin >> A;
	A.print();
	Fraction B = 1.95;
	B.print();
}
