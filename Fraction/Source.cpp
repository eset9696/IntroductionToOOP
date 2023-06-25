#include <iostream>

using namespace std;

#define delimiter "\n------------------------\n"
#define METHODS_CHECK

class Fraction;

class Fraction {
private:
	int integer;
	int numenator;
	int denumenator;
public:
	void setInteger(int integer) {
		this->integer = integer;
	}
	void setNumenator(int numenator) {
		this->numenator = numenator;
	}
	void setDenumenator(int denumenator) {
		this->denumenator = denumenator;
	}
	int getInteger()const {
		return this->integer;
	}
	int getNumenator()const {
		return this->numenator;
	}
	int getDenumenator()const {
		return this->denumenator;
	}
	//Constructors; 
	Fraction(int integer = 0, int numenator = 0, int denumenator = 1) {
		this->integer = integer;
		this->numenator = numenator;
		this->denumenator = denumenator;
	}
	Fraction(const Fraction& other) {
		this->integer = other.getInteger();
		this->numenator = other.getNumenator();
		this->denumenator = other.getDenumenator();
	}
	~Fraction() {}
	//Operators
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.getInteger();
		this->numenator = other.getNumenator();
		this->denumenator = other.getDenumenator();
		return *this;
	}
	Fraction& operator+=(const Fraction& other) // Для арифметических операций с полями класса перегрузим операторы присваивания
	{
		this->integer += other.getInteger();
		this->numenator += other.getNumenator();
		this->denumenator += other.getDenumenator();
		return *this;
	}
	Fraction& operator-=(const Fraction& other)
	{
		this->integer -= other.getInteger();
		this->numenator -= other.getNumenator();
		this->denumenator -= other.getDenumenator();
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		this->integer *= other.getInteger();
		this->numenator *= other.getNumenator();
		this->denumenator *= other.getDenumenator();
		return *this;
	}
	Fraction& operator/=(const Fraction& other)
	{
		this->integer /= other.getInteger();
		this->numenator /= other.getNumenator();
		this->denumenator /= other.getDenumenator();
		return *this;
	}
	Fraction& operator%=(const Fraction& other)
	{
		this->integer %= other.getInteger();
		this->numenator %= other.getNumenator();
		this->denumenator %= other.getDenumenator();
		return *this;
	}
	//Methods
	void print()const {
		cout << "Целая часть дроби равна: " << getInteger() << ", числитель дроби равен: "
			<< getNumenator() << ", знаменатель дроби равен: " << getDenumenator() << endl;
	}
	Fraction& sum(const Fraction& other) { // Для корректного сложения дробей создал отдельный метод
		Fraction buffer;
		int other_numenator = other.getInteger() * other.getDenumenator() + other.getNumenator();
		int numenator = this->integer * this->denumenator + this->numenator;

		if (this->denumenator == other.getDenumenator()) {
			buffer.setInteger((numenator + other_numenator) / this->denumenator);
			buffer.setNumenator((numenator + other_numenator) % this->denumenator);
			buffer.setDenumenator(other.getDenumenator());
		}
		else {
			buffer.setNumenator((numenator * other.getDenumenator() + other_numenator * this->denumenator) %
				(this->denumenator * other.getDenumenator()));
			buffer.setInteger((numenator * other.getDenumenator() + other_numenator * this->denumenator) /
				(this->denumenator * other.getDenumenator()));
			buffer.setDenumenator(this->denumenator * other.getDenumenator());
		}
		return buffer;
	}
	Fraction& sub(const Fraction& other) {
		Fraction buffer;
		int other_numenator = other.getInteger() * other.getDenumenator() + other.getNumenator();
		int numenator = this->integer * this->denumenator + this->numenator;

		if (this->denumenator == other.getDenumenator()) {
			buffer.setInteger((numenator - other_numenator) / this->denumenator);
			buffer.setNumenator((numenator - other_numenator) % this->denumenator);
			buffer.setDenumenator(other.getDenumenator());
		}
		else {
			buffer.setNumenator((numenator * other.getDenumenator() - other_numenator * this->denumenator) %
				(this->denumenator * other.getDenumenator()));
			buffer.setInteger((numenator * other.getDenumenator() - other_numenator * this->denumenator) /
				(this->denumenator * other.getDenumenator()));
			buffer.setDenumenator(this->denumenator * other.getDenumenator());
		}
		return buffer;
	}
	Fraction& multiply(const Fraction& other) {
		Fraction buffer;

		int other_numenator = other.getInteger() * other.getDenumenator() + other.getNumenator();
		int numenator = this->integer * this->denumenator + this->numenator;

		buffer.setNumenator((numenator * other_numenator) %
			(this->denumenator * other.getDenumenator()));
		buffer.setInteger((numenator * other_numenator) /
			(this->denumenator * other.getDenumenator()));
		buffer.setDenumenator(this->denumenator * other.getDenumenator());

		return buffer;
	}
	Fraction& divide(const Fraction& other) {
		Fraction buffer;

		int other_numenator = other.getInteger() * other.getDenumenator() + other.getNumenator();
		int numenator = this->integer * this->denumenator + this->numenator;

		buffer.setNumenator((numenator * other.getDenumenator()) %
			(this->denumenator * other_numenator));
		buffer.setInteger((numenator * other.getDenumenator()) /
			(this->denumenator * other_numenator));
		buffer.setDenumenator(this->denumenator * other.getNumenator());

		return buffer;
	}
};
void reduction(Fraction& other){
	for(int i = 2; i < 101; i++){
		if(other.getNumenator() % i == 0 && other.getDenumenator() % i == 0){
			other.setNumenator(other.getNumenator() / i);
			other.setDenumenator(other.getDenumenator() / i);
		}
	}
}
Fraction operator+(const Fraction& left, const Fraction& right) { // Вообще оно так работать должно? В общем дело было вечером делать было нечего
	return Fraction
	(
		left.getInteger() + right.getInteger(),
		left.getNumenator() + right.getNumenator(),
		left.getDenumenator() + right.getDenumenator()
	);
}
Fraction operator-(const Fraction& left, const Fraction& right) {
	return Fraction
	(
		left.getInteger() - right.getInteger(),
		left.getNumenator() - right.getNumenator(),
		left.getDenumenator() - right.getDenumenator()
	);
}
Fraction operator*(const Fraction& left, const Fraction& right) {
	return Fraction
	(
		left.getInteger() * right.getInteger(),
		left.getNumenator() * right.getNumenator(),
		left.getDenumenator() * right.getDenumenator()
	);
}
Fraction operator/(const Fraction& left, const Fraction& right) {
	return Fraction
	(
		left.getInteger() / right.getInteger(),
		left.getNumenator() / right.getNumenator(),
		left.getDenumenator() / right.getDenumenator()
	);
}
Fraction operator%(const Fraction& left, const Fraction& right) {
	return Fraction
	(
		left.getInteger() % right.getInteger(),
		left.getNumenator() % right.getNumenator(),
		left.getDenumenator() % right.getDenumenator()
	);
}
void main() {
	setlocale(LC_ALL, "");
	Fraction A(0, 3, 4);
	A.print();
	Fraction B(0, 3, 10);
	B.print();

#ifdef METHODS_CHECK
	Fraction C;
	C = A.sum(B);
	C.print();
	reduction(C);
	C.print();
	C = A.sub(B);
	C.print();
	C = A.multiply(B);
	C.print();
	C = A.divide(B);
	C.print();
#endif // METHODS_CHECK


}