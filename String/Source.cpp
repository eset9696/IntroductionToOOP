#include <iostream>

using namespace std;
using std::cout;

#define delimeter "\n---------------------\n"

class String;
int length(const char* str);

class String {

	int size;                //Размер строки в байтах
	char* str;               //адрес строки в динамической памяти
	
public:

	char* getString()const {
		return str;
	}

	int getSize()const {
		return size;
	}
	void setString(char* str) {
		for (int i = 0; i < size; i++)
		{
			this->str[i] = str[i];
		}
	}

	void setSize(int size) {
		this->size = size;
	}

	//Constructors
	String(int size = 80) {
		this->size = size;
		this->str = new char[size] {};
		cout << delimeter << endl;
		cout << "Default constructor\t" << this << endl;
	}

	String(const char string[]) {
		this->size = length(string);
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)
		{
			this->str[i] = string[i];
		}
		cout << delimeter << endl;
		cout << "1 Arg Constructor\t" << this << endl;
	}
	String(const String& other) {
		this->size = other.getSize();
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)
		{
			this->str[i] = other.getString()[i];
		}
		cout << delimeter << endl;
		cout << "Copy Constructor\t" << this << endl;
	}
	
	~String(){
		delete[] str;
		cout << delimeter << endl;
		cout << "Destructor\t\t" << this << endl;
	}

	String& operator=(const String& other) {
		this->size = other.getSize();
		for (int i = 0; i < size; i++)
		{
			this->str[i] = other.getString()[i];
		}
		cout << "Copy assignment \t" << this << endl;
		return *this;
	}

	//Methods

	void print()const {
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}

};
int length(const char* str){
	int length = 0;
	for (int i = 0; str[i]; i++)
	{
		length++;
	}
	return ++length;
}
ostream& operator<<(ostream& os, String& obj) {
	cout << "Size:\t" << obj.getSize() << endl;
	cout << "String:\t" << obj.getString();
	return os;
}
istream& operator>>(istream& is, String& obj) {
	const int size = 60;
	char buffer[size] = {};
	is.getline(buffer, size);
	obj.setString(buffer);
	obj.setSize(length(buffer));
	return is;
}
String operator+(String& left, String& right) {
	int size = left.getSize() + right.getSize();
	char temp[256] = {};
	for (int i = 0, j = 0; i < size; i++) {
		i < left.getSize() - 1?	temp[i] = left.getString()[i]: temp[i] = right.getString()[j++];
	}
	return String(
		temp
	);
}

void main() {
	setlocale(LC_ALL, "");

	String str1;
	str1.print();

	String str2 = 5;
	str2.print();

	String str3 = "Hello";
	str3.print();

	String str4 = "World";
	str4.print();

	String str5 = str3 + str4;
	str5.print();
	cout << str5 << endl;

	String str6;
	str6 = str5;
	cout << str6 << endl;

	String str7;
	cin >> str7;
	cout << str7 << endl;

}