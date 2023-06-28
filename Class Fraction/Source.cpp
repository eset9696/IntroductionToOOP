#include <iostream>

using namespace std;

class Fraction{
	int integer;
	int numerator;
	int denominator;
public:
	int getInteger()const{
		return integer;
	}
	int getNumerator()const {
		return numerator;
	}
	int getDenominator()const {
		return denominator;
	}
	void setInteger(int integer){
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
	Fraction(int numerator, int denominator) {
		this->integer = 0;
		this->numerator = numerator;
		setDenominator(denominator);
		cout << "2 Parameters Constructor:\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator){
		this->integer = integer;
		this->numerator = numerator;
		setDenominator(denominator);
		cout << "3 Parameters Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other){
		this->integer = other.getInteger();
		this->numerator = other.getNumerator();
		setDenominator(other.getDenominator());
		cout << "Copy constructor:\t\t" << this << endl;
	}
	~Fraction(){ cout << "Destructor:\t\t\t" << this << endl; }
	//Operators
	Fraction& operator=(const Fraction& other) {
		this->integer = other.getInteger();
		this->numerator = other.getNumerator();
		setDenominator(other.getDenominator());
		cout << "Copy Assignment:\t\t" << this << endl;
		return *this;
	}
	Fraction& operator+=(const Fraction& other) {
		this->integer += other.getInteger();
		this->numerator = this->numerator * other.getDenominator() + other.getNumerator() * this->denominator;
		this->denominator *= other.getDenominator();
		this->reduce();
		return *this;
	}
	Fraction& operator-=(const Fraction& other) {
		int buffer = other.getNumerator() + other.getInteger() * other.getDenominator();
		this->toImproper();
		this->numerator = this->numerator * other.getDenominator() - buffer * this->denominator;
		this->denominator *= other.getDenominator();
		this->reduce();
		return *this;
	}
	Fraction& operator*=(const Fraction& other) {
		int buffer = other.getNumerator() + other.getInteger() * other.getDenominator();
		this->toImproper();
		this->numerator = this->numerator * buffer;
		this->denominator *= other.getDenominator();
		this->reduce();
		return *this;
	}

	Fraction& operator/=(const Fraction& other) {
		int buffer = other.getNumerator() + other.getInteger() * other.getDenominator();
		this->toImproper();
		this->numerator = this->numerator * other.getDenominator();
		this->denominator *= buffer;
		this->reduce();
		return *this;
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
	Fraction& operator--(){
		integer--;
		return *this;
	}
	Fraction operator--(int) {
		Fraction old = *this;
		integer--;
		return old;
	}
	//Methods
	void print(){
		if (integer) cout << integer;
		if(numerator){
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0) cout << 0;
		cout << endl;
	}
	void toProper(){
		if(this->numerator >= this->denominator){
			this->integer = this->integer + this->numerator / this->denominator;
			this->numerator = this->numerator % this->denominator;
		}else if(-this->numerator >= this->denominator){
			this->integer = -(this->integer + -this->numerator / this->denominator);
			this->numerator = -(this->numerator % this->denominator);
		}
	}
	void toImproper() {
		if (this->numerator < this->denominator) {
			this->numerator = this->integer * this->denominator + this->numerator;
			this->integer = 0;
		}
	}
	void reduce() {
		this->toProper();
		for(int i = 2; i <= this->numerator;){
			if (this->numerator % i == 0 && this->denominator % i == 0) {
				this->numerator /= i;
				this->denominator /= i;
			}
			else i++;
		}
	}
};
//Functions
Fraction& operator+(const Fraction& left, const Fraction& right){
	Fraction result = left;
	Fraction tempR = right; //Фиг знает почему, но если удалить эту строку то в знаменатель запишется какой то мусор
	return result += right;
}
Fraction& operator-(const Fraction& left, const Fraction& right) {
	Fraction result = left;
	Fraction tempR = right;
	return result -= right;
}
Fraction& operator*(const Fraction& left, const Fraction& right) {
	Fraction result = left;
	Fraction tempR = right;
	return result *= right;
}
Fraction& operator/(const Fraction& left, const Fraction& right) {
	Fraction result = left;
	Fraction tempR = right;
	return result /= right;
}
//#define CONSTRUCTORS_CHECK
//#define METHODS_CHECK
//#define OPERATORS_CHECK
#define FUNCTIONS_CHECK
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
	Fraction A(0, 3, 4);
	A.print();
	A.reduce();
	A.print();
	A.toProper();
	A.print();
	A.toImproper();
	A.print();
#endif // METHODS_CHECK
#ifdef OPERATORS_CHECK
	Fraction A(3, 2, 3);
	Fraction B(1, 3, 5);
	A.print();
	B.print();
	A += B;
	A.print();
	A -= B;
	A.print();
	A *= B;
	A.print();
	A /= B;
	A.print();
	B.print();
#endif // OPERATORS_CHECK
#ifdef FUNCTIONS_CHECK
	Fraction A(3, 2, 3);
	Fraction B(1, 3, 5);
	A.print();
	B.print();
	Fraction C;
	C = A + B;
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

}