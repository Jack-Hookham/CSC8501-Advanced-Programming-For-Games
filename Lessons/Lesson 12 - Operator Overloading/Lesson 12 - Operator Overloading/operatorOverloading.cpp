#include <iostream>

using namespace std;

/**
* define a generic matrix class
*/
template <typename T>
class Matrix
{
public:
	Matrix(int x = default_x, int y = default_y);
	Matrix(const Matrix<T>& src);
	~Matrix();
	// overloaded operators on class
	Matrix<T>& operator=(const Matrix<T>& rhs);
	template <typename E>
	friend ostream& operator<<(ostream& ostr, const Matrix<E>& mtx);
	template <typename E>
	friend Matrix<E> operator*(const Matrix<E>& a, const Matrix<E>& b);

	int get_x_size() const { return x_size; }
	int get_y_size() const { return y_size; }
	T get_element(int x, int y) const;
	void set_element(int x, int y, T elem);
	// constant elements
	static const int default_x = 3;
	static const int default_y = 3;
protected:
	T** cells;
	int x_size;
	int y_size;
};

template <typename T>
Matrix<T>::Matrix(int x, int y) :
	x_size(x), y_size(y) {
	cells = new T*[x_size];
	for (int i = 0; i < x_size; ++i) {
		cells[i] = new T[y_size];
		memset(cells[i], 0, (y_size * sizeof(T)));
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& src) :
	x_size(src.x_size), y_size(src.y_size)
{
	cells = new T*[x_size];
	for (int i = 0; i < x_size; ++i)
	{
		cells[i] = new T[y_size];
		memcpy_s(cells[i], (y_size * sizeof(T)), src.cells[i], (y_size * sizeof(T)));
		//memcpy(cells[i], src.cells[i], y_size * sizeof(T)); // same but less safe than memcpy_s
	}
}

template <typename T>
Matrix<T>::~Matrix() {
	for (int i = 0; i < x_size; ++i) {
		delete[] cells[i];
	}
	delete[] cells;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
	if (this == &rhs) return (*this);

	// release old memory
	for (int i = 0; i < x_size; ++i) {
		delete[] cells[i];
	}
	delete[] cells;

	// allocate new memory
	cells = new T*[rhs.x_size];
	for (int i = 0; i < rhs.x_size; ++i) {
		cells[i] = new T[rhs.y_size];
		memset(cells[i], 0, (rhs.y_size * sizeof(T)));
	}

	// copy values
	for (int i = 0; i < rhs.x_size; ++i) {
		for (int j = 0; j < rhs.y_size; ++j) {
			cells[i][j] = rhs.cells[i][j];
		}
	}
	return *this;
}

// friend functions

template <typename E>
ostream& operator<<(ostream& ostr, const Matrix<E>& mtx) {
	for (int i = 0; i < mtx.x_size; ++i) {
		for (int j = 0; j < mtx.y_size; ++j) {
			ostr << mtx.cells[j][i] << ", ";
		}
		ostr << "\n";
	}
	ostr << "\n";
	return ostr;
}

template <typename E>
Matrix<E> operator*(const Matrix<E>& a, const Matrix<E>& b) {
	Matrix<E> result(a.x_size, b.y_size);
	for (int i = 0; i < a.x_size; ++i) {
		for (int j = 0; j < a.x_size; ++j) {
			for (int k = 0; k < a.x_size; ++k) {
				result.cells[i][j] += (a.cells[k][j] * b.cells[i][k]);
			}
		}
	}
	return result;
}

template <typename T>
T Matrix<T>::get_element(int x, int y) const {
	return (cells[x][y]);
}

template <typename T>
void Matrix<T>::set_element(int x, int y, T elem) {
	cells[x][y] = elem;
}


int main() {
	Matrix<int> mtx1;
	mtx1.set_element(0, 0, 1);
	mtx1.set_element(1, 1, 4);
	mtx1.set_element(2, 2, 6);
	cout << "matrix 1:\n" << mtx1;

	Matrix<int> mtx2;
	mtx2.set_element(0, 0, 1);
	mtx2.set_element(1, 1, 4);
	mtx2.set_element(2, 2, 2);

	cout << "matrix 2:\n" << mtx2;

	Matrix<int> mtx3;
	mtx3 = mtx2;
	cout << "matrix 3 assigned from matrix 2:\n" << mtx3;

	Matrix<int> product = (mtx1 * mtx3);
	cout << "matrix product assigned from mtx1 * mtx3:\n" << product;

	int x;
	cin >> x;
	return 0;
}