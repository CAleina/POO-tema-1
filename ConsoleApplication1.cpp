#include "D:\POO\ConsoleApplication1\Header1.h"

Mat::Mat (int a, int b) {
	lin = a;
	col = b;
	matrice = new int* [a];
	for (int i = 0; i <= b; i++)
		matrice[i] = new int[b];
}

Mat::Mat() {
	lin = 0;
	col = 0;
	matrice = new int*[0];
}

Mat::Mat(Mat& A) {
	lin = A.lin;
	col = A.col;
	matrice = new int* [lin];
	for (int i = 0; i < col; i++)
		matrice[i] = new int[col];
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < col; j++)
			matrice[i][j] = A.matrice[i][j];
}

Mat::~Mat() {
	for (int i = 0; i < lin; i++)
		delete[] matrice[i];
	delete[] matrice;
}


Mat Mat::operator=(Mat& a) {
	for (int i = 0; i <= lin; i++)
		delete[] matrice[i];
	delete[] matrice;
	matrice = new int* [lin];
	for (int i = 0; i < col; i++)
		matrice[i] = new int[col];
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < col; j++)
			matrice[i][j] = a.matrice[i][j];
	lin = a.lin;
	col = a.col;
	return a;
}

Mat Mat::operator+(const Mat& a)const {
	if (lin != a.lin || col != a.col) {
		throw std::domain_error("Dimensiuni diferite ale matricilor");
	}
	Mat w(lin, col);
	for (int i = 0; i < lin; i++) {
		for (int j = 0; j < col; j++)
			w.matrice[i][j] = a.matrice[i][j] + matrice[i][j];
	}
	w.lin = lin;
	w.col = col;
	return w;
}

Mat Mat::operator-(const Mat& a)const {
	if (lin != a.lin || col != a.col) {
		throw std::domain_error("Dimensiuni diferite ale matricilor");
	}
	Mat w(lin, col);
	for (int i = 0; i < lin; i++) {
		for (int j = 0; j < col; j++)
			w.matrice[i][j] = a.matrice[i][j] - matrice[i][j];
	}
	w.lin = lin;
	w.col = col;
	return w;
}

vector<int>& Mat::operator[](int a) const {
	if (lin < a) {
		throw std::out_of_range("Index mai mare ca dimensiunea vectorului");
	}
	vector<int> V;
	for (int i = 0; i < col; i++)
		V[i] = matrice[a][i];
	return V;
}

Mat Mat::operator*(int v) const {
	Mat w(lin, col);
	w.lin = lin;
	w.col = col;
	for (int i = 0; i < lin; i++) {
		for (int j = 0; j < col; j++)
			w.matrice[i][j] = v * matrice[i][j];
	}
	return w;
}

Mat Mat::operator*(const Mat& a)const {
	if (col != a.lin) {
		throw std::domain_error("Matrici incompatibile");
	}
	Mat w(lin, a.col);
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < lin; j++)
			for (int k = 0; k < lin; k++)
				w.matrice[i][j] = matrice[i][k] * a.matrice[k][j] + w.matrice[i][j];
	return w;
}

std::istream& operator>>(std::istream& in, Mat& a) {
	delete[] a.matrice;
	int l, c, x, i, j;
	in >> l;
	a.lin = l;
	in >> c;
	a.col = c;
	a.matrice = new int* [a.lin];
	for (i = 0; i < a.lin; i++)
		a.matrice[i] = new int[a.col];
	for (i = 0; i < a.lin; i++) {
		for (j = 0; j < a.col; j++)
			in >> x;
		a.matrice[i][j] = x;
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Mat& a) {
	for (int i = 0; i < a.lin; i++) {
		for (int j = 0; j < a.col; j++)
			out << a.matrice[i][j] << " ";
	}
	return out;
}

int Mat::det(Mat& a) {
	if (col != lin)
		throw std::domain_error("Matricea nu este patratica");
	int d = 0;
	if (col == 2)
		d = matrice[1][1] * matrice[2][2] - matrice[1][2] * matrice[2][1];
	else
	{
		for (int i = 0; i < col; i++)
			d = d + matrice[1][i] * det(remove(a, 1, i));
	}
	return d;
}

Mat& Mat::removelin(Mat& a, int x) {
	if (x > a.lin)
		throw std::domain_error("Numarul este prea mare");
	delete[] a.matrice[x];
	a.lin--;
	return a;
}

Mat& Mat::removecol(Mat& a, int x) {
	if (a.col < x)
		throw std::domain_error("Numarul este prea mare");
	for (int i = 0; i <= a.lin; i++)
	{
		for (int j = x; j < a.col - 1; j++)
			a.matrice[i][j] = a.matrice[i][j + 1];;
	}
	Mat w(a.lin, a.col - 1);
	for (int i = 0; i < a.lin; i++)
	{
		for (int j = 0; j < a.col - 1; j++)
			w.matrice[i][j] = a.matrice[i][j];;
	}
	return w;
}

Mat& Mat::remove(Mat& a, int x, int y) {
	Mat w;
	w = removelin(a, x);
	w = removecol(a, y);
	return w;
}

int Mat::nrlin(Mat& a) {
	return a.lin;
}

int Mat::nrcol(Mat& a) {
	return a.col;
}

void testare() {
	Mat m1(2, 3), m2(2, 3), m3(2, 3);
	cin >> m1;
	assert(m1 == m3);
	assert(m1 * m2 == m3);
	assert(m1 - m2 == m3);
	cout << "Corect";
}

int main(){
	testare();
	return 0;
}