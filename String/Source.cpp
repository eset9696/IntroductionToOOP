#include <iostream>

using namespace std;
using std::cout;

#define delimeter "\n---------------------\n"

class String;

class String {

	int size;                //Размер строки в байтах
	char* str;             //адрес строки в динамической памяти

public:

	const char* getString() const {
		return str;
	}
	char* getString() {
		return str;
	}

	int getSize()const {
		return size;
	}

	//Constructors
	explicit String(int size = 80) : size(size), str(new char[size] {}) {
		//this->size = size;
		//this->str = new char[size] {};
		cout << delimeter << endl;
		cout << "Default constructor\t" << this << endl;
	}

	String(const char* string) : size(strlen(string) + 1), str(new char[size] {}) {
		//this->size = strlen(string) + 1;
		//this->str = new char[size] {};
		for (int i = 0; i < size; i++)
		{
			this->str[i] = string[i];
		}
		cout << delimeter << endl;

		cout << "Constructor\t\t" << this << endl;
	}

	String(const String& other) : size(other.size), str(new char[size] {}) {
		//String(other.getString());
		for (int i = 0; i < size; i++)
		{
			this->str[i] = other[i];
		}
		cout << delimeter << endl;
		cout << "Copy Constructor\t" << this << endl;
	}

	String(String&& rvalue) noexcept : size(rvalue.size), str(rvalue.str) {
		//this->str = rvalue.str; // shallow copy
		//this->size = rvalue.size;
		rvalue.str = nullptr;
		rvalue.size = 0;
		cout << delimeter << endl;
		cout << "Move Constructor\t" << this << endl;
	}

	~String() {
		delete[] str;
		cout << delimeter << endl;
		cout << "Destructor\t\t" << this << endl;
	}

	// Operators

	String& operator=(const String& other) {
		if (this == &other) return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)
		{
			this->str[i] = other.getString()[i];
		}
		cout << "Copy assignment \t" << this << endl;
		return *this;
	}

	String& operator=(String&& rvalue) noexcept {
		if (this == &rvalue) return *this;
		delete[] this->str;
		str = rvalue.str;
		size = rvalue.size;
		rvalue.str = nullptr;
		rvalue.size = 0;
		cout << "Move assignment \t" << this << endl;
		return *this;
	}

	char operator[](int index) const {
		return str[index];
	}

	char& operator[](int index) {
		return str[index];
	}

	//Methods

	void print()const {
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}

};

ostream& operator<<(ostream& os, const String& obj) {
	cout << "Size:\t" << obj.getSize() << endl;
	cout << "String:\t" << obj.getString();
	return os;
}

istream& operator>>(istream& is, String& obj) {
	char buffer[256] = {};
	is >> buffer;
	obj = String(buffer);
	return is;
}

String operator+(const String& left, const String& right) {
	String cat(left.getSize() + right.getSize() - 1);
	for (int i = 0; i < left.getSize(); i++) {
		cat[i] = left[i];
	}
	for (int i = 0; i < right.getSize(); i++) {
		cat[i + left.getSize() - 1] = right[i];
	}
	return cat;
}

#define BASE_CHECK
//#define CALLING_CONSTRUCTORS

void main() {
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK

	String str1;
	str1.print();

	String str2(5);
	str2.print();

	String str3 = "Hello";
	str3.print();

	String str4 = "World";
	str4.print();

	String str5 = move(str3 + " " + str4);
	str5.print();
	cout << str5 << endl;

	String str6 = str5;
	cout << str6 << endl;

#endif // BASE_CHECK
#ifdef CALLING_CONSTRUCTORS
	String str1; // Default constructor
	str1.print();

	String str2(5); 
	str2.print();

	String str3 = "Hello"; //Single argument constructor
	str3.print();

	String str4;
	str4.print();

	String str5 = str3 + " " + str4;
	str5.print();
	cout << str5 << endl;
#endif // CALLING_CONSTRUCTORS


}