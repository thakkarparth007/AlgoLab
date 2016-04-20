#include <bits/stdc++.h>

using namespace std;

template<typename T>
class Matrix {
public:
	int rows, cols;
	vector< vector<T> > matr;
	
	Matrix<T>(int m, int n) {
		if(m == 0 || n == 0) {
			cout << "Lol. Error.\n";
			exit(0);
		}
		matr = vector< vector<T> >(m, vector<T>(n));
		rows = m;
		cols = n;
	}

	Matrix<T> operator+(Matrix<T> m) {
		if(rows != m.rows && cols != m.cols) {
			return Matrix<T>(0,0);
		}
		Matrix ans(rows, cols);
		for(int i = 0; i < rows; i++)
			for(int j = 0; j < cols; j++)
				ans.matr[i][j] = matr[i][j] + m.matr[i][j];
		return ans;
	}

	Matrix<T> operator-(Matrix<T> m) {
		if(rows != m.rows || cols != m.cols) {
			return Matrix<T>(0,0);
		}
		Matrix<T> ans(rows, cols);
		for(int i = 0; i < rows; i++)
			for(int j = 0; j < cols; j++)
				ans[i][j] = matr[i][j] - m[i][j];
		return ans;

	}
	
	Matrix<T> operator*(Matrix<T> m) {
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
			return Matrix<T>(0, 0);
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
		
		Matrix<T> 	a = submatrix(0, rows/2-1, 0, cols/2-1),
					b = submatrix(0, rows/2-1, cols/2, cols-1),
					c = submatrix(rows/2, rows-1, 0, cols/2-1),
					d = submatrix(rows/2, rows-1, cols/2, cols-1);
		
		Matrix<T>	e = m.submatrix(0, rows/2-1, 0, cols/2-1),
					f = m.submatrix(0, rows/2-1, cols/2, cols-1),
					g = m.submatrix(rows/2, rows-1, 0, cols/2-1),
					h = m.submatrix(rows/2, rows-1, cols/2, cols-1);

		Matrix<T> P1 = a*(f-h);
		Matrix<T> P2 = (a+b)*h;
		Matrix<T> P3 = (c+d)*e;
		Matrix<T> P4 = d*(g-e);
		Matrix<T> P5 = (a+d)*(e+h);
		Matrix<T> P6 = (b-d)*(g+h);
		Matrix<T> P7 = (a-c)*(e+f);
		
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
	
	Matrix<T> submatrix(int startRow, int endRow, int startCol, int endCol) {
		Matrix<T> ret(endRow-startRow+1, endCol-startCol+1);
			
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
	Matrix<int> A(n,n), B(n,n);
	
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
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cout << A[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}


