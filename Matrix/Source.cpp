#include <iostream>
#include <ctime>

#define delimeter "\n-------------------------\n"

using namespace std;

class Matrix;
double** Allocate(const int rows, const int cols);
void FillRand(int**& matrix, const int rows, const int cols);
void Print(const int** matrix, const int rows, const int cols);
void ClearMat(Matrix& obj);
class Matrix{
	int rows;
	int cols;
	double** matrix;
public:
	int getRows()const{
		return rows;
	}
	int getCols()const {
		return cols;
	}
	double** getMatrix() const {
		return matrix;
	}
	double** getMatrix() {
		return matrix;
	}

	//constructors

	Matrix(int rows = 0, int cols = 0) {
		this->rows = rows;
		this->cols = cols;
		this->matrix = new double* [rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new double[cols] {};
		}
		cout << delimeter << endl;
		cout << "Default constructor:\t" << this << endl;
	}

	Matrix(double** other, int rows, int cols) {
		this->rows = rows;
		this->cols = cols;
		this->matrix = new double* [rows];
		for(int i = 0; i < rows; i++) {
			matrix[i] = new double [cols];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols;  j++) {
				matrix[i][j] = other[i][j];
			}
		}
		cout << delimeter << endl;
		cout << "Constructor:\t\t" << this << endl;
	}

	Matrix(const Matrix& other) {
		this->rows = other.rows;
		this->cols = other.cols;
		this->matrix = new double* [rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new double[cols];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				matrix[i][j] = other.getMatrix()[i][j];
			}
		}
		cout << delimeter << endl;
		cout << "Copy constructor:\t" << this << endl;
	}

	Matrix(Matrix&& other) noexcept {
		this->rows = other.rows;
		this->cols = other.cols;
		this->matrix = other.matrix;
		other.matrix = nullptr;
		other.rows = 0;
		other.cols = 0;
		cout << delimeter << endl;
		cout << "Move constructor:\t" << this << endl;
	}

	~Matrix(){
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		cout << delimeter << endl;
		cout << "Destructor:\t\t" << this << endl;
	}

	//operators

	Matrix& operator=(const Matrix& other){
		if (this == &other) return *this;
		this->ClearMat();
		this->rows = other.rows;
		this->cols = other.cols;
		this->matrix = new double* [rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new double[cols];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				matrix[i][j] = other.getMatrix()[i][j];
			}
		}
		cout << "Copy assignment:\t" << endl;
		return *this;
	}

	Matrix& operator=(Matrix&& other) noexcept {
		if (this == &other) return *this;
		this->ClearMat();
		this->rows = other.rows;
		this->cols = other.cols;
		this->matrix = other.matrix;
		other.matrix = nullptr;
		other.rows = 0;
		other.cols = 0;
		cout << "Move assignment:\t" << endl;
		return *this;
	}

	const double* operator[](int index) const {

		return matrix[index];
	}

	double*& operator[](int index) {
		
		return matrix[index];
	}

	//Methods

	void print() const {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	void ClearMat() {
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}
};

Matrix operator+(const Matrix& left, const Matrix& right){
	if (left.getRows() != right.getRows() || left.getCols() != right.getCols()) return left;
	Matrix result(left.getRows(), left.getCols());
	for (int i = 0; i < left.getRows(); i++) {
		for(int j = 0; j < left.getCols(); j++) {
			result[i][j] = left[i][j] + right[i][j];
		}
	}
	return result;
}

Matrix operator-(const Matrix& left, const Matrix& right) {
	if (left.getRows() != right.getRows() || left.getCols() != right.getCols()) return left;
	Matrix result(left.getRows(), left.getCols());
	for (int i = 0; i < left.getRows(); i++) {
		for (int j = 0; j < left.getCols(); j++) {
			result[i][j] = left[i][j] - right[i][j];
		}
	}
	return result;
}

Matrix operator*(const Matrix& left, const Matrix& right) {
	if (left.getCols() != right.getRows()) return left;
	Matrix result(left.getRows(), left.getCols());
	for (int i = 0; i < left.getRows(); i++) {
		for (int j = 0; j < left.getCols(); j++) {
			for (int k = 0; k < left.getCols(); k++)
			{
				result[i][j] += left[i][k] * right[k][j];
			}
		}
	}
	return result;
}

ostream& operator<<(ostream& os, const Matrix& obj) {
	for (int i = 0; i < obj.getRows(); i++)
	{
		for (int j = 0; j < obj.getCols(); j++)
		{
			cout << obj.getMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	return os;
}

//istream& operator>>(istream& is, const Matrix& obj) {
//	for (int i = 0; i < obj.getRows(); i++)
//	{
//		for (int j = 0; j < obj.getCols(); j++)
//		{
//			cin >> obj.getMatrix()[i][j];
//		}
//	}
//	return is;
//}

double** Allocate(const int rows, const int cols) {
	double** matrix = new double*[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new double[cols];
	}
	return matrix;
}

void FillRand(double**& matrix, const int rows, const int cols) {
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = rand() % 10;
		}
	}
}

void FillMat(double**& matrix, const int rows, const int cols) {
	double count = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = ++count;
		}
	}
}

void Print(double** matrix, const int rows, const int cols) {
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void ClearMat(double** matrix, const int rows, const int cols) {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;

}
void main(){
	setlocale(LC_ALL, "");
	srand(0);

	int rows1 = 3;
	int cols1 = 4;

	int rows2 = 4;
	int cols2 = 5;

	double** mx1 = Allocate(rows1, cols1);
	FillMat(mx1, rows1, cols1);
	double** mx2 = Allocate(rows2, cols2);
	FillMat(mx2, rows2, cols2);

	Matrix matx1(mx1, rows1, cols1);
	cout << "matx1:\n" << matx1 << endl;

	Matrix matx2(mx2, rows2, cols2);
	cout << "matx2:\n" << matx2 << endl;

	Matrix matx3 = matx1 + matx2;
	cout << "matx3 = matx1 + matx2:\n" << matx3 << endl;

	Matrix matx4 = matx3 - matx2;
	cout << "matx4 = matx3 - matx2:\n" << matx4 << endl;

	Matrix matx5 = matx1 * matx2;
	cout << "matx5 = matx1 * matx2:\n" << matx5 << endl;

	Matrix matx6;
	matx6 = matx5 * matx1;
	cout << "matx6 = matx5 + matx1 move assignment:\n" << matx6 << endl;
	
	Matrix matx7;
	matx7 = matx6;
	cout << "matx7 = matx6 copy assignment:\n" << matx7 << endl;

	ClearMat(mx1, rows1, cols1);
	ClearMat(mx2, rows2, cols2);

}
