#include <iostream>

using namespace std;
using std::cout;

#define delimeter "\n---------------------\n"

class String;

class String {

	int size;                //Размер строки в байтах
	char* str;               //адрес строки в динамической памяти

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
	explicit String(int size = 80) {
		this->size = size;
		this->str = new char[size] {};
		cout << delimeter << endl;
		cout << "Default constructor\t" << this << endl;
	}

	String(const char* string) {
		this->size = strlen(string) + 1;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)
		{
			this->str[i] = string[i];
		}
		cout << delimeter << endl;
		cout << "Constructor\t\t" << this << endl;
	}

	String(const String& other) {
		String(other.getString());
		cout << delimeter << endl;
		cout << "Copy Constructor\t" << this << endl;
	}

	String(String&& rvalue) noexcept {
		this->str = rvalue.str;
		this->size = rvalue.size;
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

ostream& operator<<(ostream& os, String& obj) {
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

void main() {
	setlocale(LC_ALL, "");

	String str1;
	str1.print();

	String str2(5);
	str2.print();

	String str3 = "Hello";
	str3.print();

	String str4 = "World";
	str4.print();

	String str5 = str3 + " " + str4;
	str5.print();
	cout << str5 << endl;

	String str6 = str3;
	str6 = str4;
	cout << str6 << endl;

	str3 = str3;
	cout << str3 << endl;
	
	String str7;
	cin >> str7;
	cout << str7 << endl;

	String str8 = String("hello");

	String str9 = "hello";

	String str10 (str8 + str9);
	str10.print();

	str9 = str9 + str8;
	str9.print();

	cout << str8 << endl;

	char str11[] = "asde";
	char* str(str11);
}