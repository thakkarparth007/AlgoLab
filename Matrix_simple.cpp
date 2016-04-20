#include <bits/stdc++.h>

using namespace std;

#define T double

class Matrix {
public:
	int rows, cols;
	vector< vector<T> > matr;
	
	Matrix(int m, int n) {
		if(m == 0 || n == 0) {
			cout << "Lol. Error.\n";
			exit(0);
		}
		matr = vector< vector<T> >(m, vector<T>(n));
		rows = m;
		cols = n;
	}

	Matrix operator+(Matrix m) {
		if(rows != m.rows && cols != m.cols) {
			return Matrix(0,0);
		}
		Matrix ans(rows, cols);
		for(int i = 0; i < rows; i++)
			for(int j = 0; j < cols; j++)
				ans.matr[i][j] = matr[i][j] + m.matr[i][j];
		return ans;
	}

	Matrix operator-(Matrix m) {
		if(rows != m.rows || cols != m.cols) {
			return Matrix(0,0);
		}
		Matrix ans(rows, cols);
		for(int i = 0; i < rows; i++)
			for(int j = 0; j < cols; j++)
				ans[i][j] = matr[i][j] - m[i][j];
		return ans;

	}
	
	Matrix operator*(Matrix m) {
		/*
			a b		e f
			c d		g h
			
			P1 = a(f-h)
			P2 = (a+b)h
			P3 = (c+d)e
			P4 = d(g-e)
			P5 = (a+d)(e+h)
			P6 = (b-d)(g+h)
			P7 = (a-c)(e+f)
			
			ae+bg = -P2 + P4 + P5 + P6
			af+bh = P1 + P2
			ce+dg = P3 + P4
			cf+dh = P1 - P3 + P5 - P7
		*/
		if(cols != m.rows) {
			return Matrix(0, 0);
		}
		
		if(cols < 3 || rows < 3) {
			Matrix ret(rows,m.cols);
			for(int i = 0; i < rows; i++) {
				for(int j = 0; j < m.cols; j++) {
					for(int k = 0; k < cols; k++) {
						ret[i][j] += matr[i][k] * m[k][j];
					}
				}
			}
			return ret;
		}
		
		Matrix 	a = submatrix(0, rows/2-1, 0, cols/2-1),
				b = submatrix(0, rows/2-1, cols/2, cols-1),
				c = submatrix(rows/2, rows-1, 0, cols/2-1),
				d = submatrix(rows/2, rows-1, cols/2, cols-1);
		
		Matrix	e = m.submatrix(0, rows/2-1, 0, cols/2-1),
				f = m.submatrix(0, rows/2-1, cols/2, cols-1),
				g = m.submatrix(rows/2, rows-1, 0, cols/2-1),
				h = m.submatrix(rows/2, rows-1, cols/2, cols-1);

		Matrix P1 = a*(f-h);
		Matrix P2 = (a+b)*h;
		Matrix P3 = (c+d)*e;
		Matrix P4 = d*(g-e);
		Matrix P5 = (a+d)*(e+h);
		Matrix P6 = (b-d)*(g+h);
		Matrix P7 = (a-c)*(e+f);
		
		Matrix  topleft = P6 + P5 + P4 - P2,
				topright = P1 + P2,
				botleft = P3 + P4,
				botright = P1 - P3 + P5 - P7;
		
		Matrix ret(rows, cols);
		
		for(int i = 0; i < rows/2; i++)
			for(int j = 0; j < cols/2; j++)
				ret[i][j] = topleft[i][j];
		
		for(int i = 0; i < rows/2; i++)
			for(int j = cols/2; j < cols; j++)
				ret[i][j] = topright[i][j-cols/2];

		for(int i = rows/2; i < rows; i++)
			for(int j = 0; j < cols/2; j++)
				ret[i][j] = botleft[i-rows/2][j];

		for(int i = rows/2; i < rows; i++)
			for(int j = cols/2; j < cols; j++)
				ret[i][j] = botright[i-rows/2][j-cols/2];
					
		return ret;
	}
	
	// cheating. Lol.
	vector<T>& operator[](int r) {
		return matr[r];
	}
	
	Matrix submatrix(int startRow, int endRow, int startCol, int endCol) {
		Matrix ret(endRow-startRow+1, endCol-startCol+1);
			
		for(int i = startRow; i <= endRow; i++)
			for(int j = startCol; j <= endCol; j++)
				ret[i-startRow][j-startCol] = matr[i][j];
		return ret;
	}
	
	void print() {
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				cout << matr[i][j] << " ";
			}
			cout << "\n";
		}
	}
};

int main() {
	int n;
	cin >> n;
	Matrix A(n,n), B(n,n);
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cin >> A[i][j];
		}
	}
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cin >> B[i][j];
		}
	}
	
	cout << "\nResult: \n";
	A = A * B;
	A.print();
	return 0;
}


