#include <iostream>
#include <cmath>

using namespace std;
//#define STRUCT_POINT
//#define DISTACE_CHECK
//#define CONSTRUCTORS_CHECK
//#define INCREMENT_CHECK
#define delimiter "\n----------------------\n"

class Point {
	double x;
	double y;
public:
	
	void print(){
		cout << getX() << "\t" << getY() << endl;
	}
	void setX(double x){
		this->x = x;
	}
	void setY(double y){
		this->y = y;
	}
	double getX()const{
		return x;
	}
	double getY()const{
		return y;
	}
							//Counstructors:
	/*Point() {
		x = y = double(); // - значение по умолчанию для заданного типа
		//таким образом мы якобы вызываем конструктор по умолчанию для заданного типа
		cout << "DefoultCountructor:\t" << this << endl;
	}
	Point(double x) {
		this->x = x;
		this->y = 0;
		cout << "1ArgCountructor:\t" << this << endl;
	}*/

	Point(double x = 0, double y = 0) {
		this->x = x;
		this->y = y;
		cout << "Countructor:\t" << this << endl;
	}
	Point(const Point& other) {
		this->x = other.x;
		this->y = other.y;
		cout << "CopyCountructor:\t" << this << endl;
	}
	~Point() {
		cout << "Destructor:\t" << this << endl;
	}
							//Operators
	Point& operator=(const Point& other){
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	Point& operator+=(const Point& other) {
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
	Point& operator++() {
		x++;
		y++;
		return *this;
	}
	Point operator++(int) {
		Point old = *this;
		x++;
		y++;
		return old;
	}						//Methods
	double distance(const Point& other)const{
		double x_distace = this->x - other.x;
		double y_distace = this->y - other.y;
		double distance = sqrt(x_distace * x_distace + y_distace * y_distace);
		return distance;
	}
};
ostream& operator<<(ostream& os, const Point obj) {
	return os << "X = " << obj.getX() << "\tY = " << obj.getY();
}
double distance(const Point& A, const Point& B) {
	double x_distace = A.getX() - B.getX();
	double y_distace = A.getY() - B.getY();
	double distance = sqrt(x_distace * x_distace + y_distace * y_distace);
	return distance;
}

void main(){
	setlocale(LC_ALL, "");

#ifdef STRUCT_POINT
	int a; //Объявление переменной а типа int
	Point A; // Объявление переменной А типа Point или же создание объекта А структуры Point или же создание экземпляра А струкруты Point
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;
	Point* pA = &A;
	cout << pA->x << "\t" << pA->y << endl;
#endif // !STRUCT_POINT

#ifdef DISTANCE_CHECK
	Point A;
	A.setX(2);
	A.setY(3);
	cout << A.getX() << "\t" << A.getY() << endl;

	Point B;
	B.setX(7);
	B.setY(8);
	cout << B.getX() << "\t" << B.getY() << endl;

	cout << delimiter << endl;
	cout << "Расстояние от точки 'А' до точки 'В':\t" << A.distance(B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние от точки 'А' до точки 'В':\t" << B.distance(A) << endl;
	cout << delimiter << endl;
	cout << "Расстояние от точки 'А' до точки 'В':\t" << distance(A, B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние от точки 'А' до точки 'В':\t" << distance(B, A) << endl;
	cout << delimiter << endl;

#endif // !DISTANCE_CHECK

#ifdef CONSTRUCTORS_CHECK

	Point A;
	A.print();
	
	Point B = 5; // Single-argument constructor 
	B.print();

	Point C(2, 3);
	C.print();
	Point D = C; // copy constructor
	D.print();

	Point E;
	E = D;
	E.print();

#endif // !CONSTRUCTORS_CHECK
#ifdef INCREMENT_CHECK

	int a, b, c = 0;
	a = b = c = 0;
	cout << a << "\t" << b << "\t" << c << "\t" << endl;

	Point A, B, C;
	A = B = C = Point(2, 3);
	A.print();
	B.print();
	C.print();
	A = B++;
	A.print();
	B.print();

#endif // !INCREMENT_CHECK
	Point A (2, 3);
	A.print();

	Point B(7, 8);
	B.print();

	A;
	cout << A << endl;
}
