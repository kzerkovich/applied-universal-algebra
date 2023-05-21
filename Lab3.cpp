#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Matrix {
public:
	int N;
	int** matrix;


	Matrix(int N) {
		this->N = N;
		matrix = new int* [N];

		for (int i = 0; i < N; i++)
			matrix[i] = new int[N];

	}

	void init() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> matrix[i][j];
			}
		}
	}

	void printClosure(int** matr) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << matr[i][j] << " ";
			}
			cout << endl;
		}
	}

	void print() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	bool equal(int** a, int** b) {
		bool flag = true;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (a[i][j] != b[i][j]) flag = false;
			}
		}
		return flag;
	}

	void associativity() {
		int** xa;
		int** az;
		xa = new int* [N];
		az = new int* [N];
		bool flag = true;
		for (int i = 0; i < N; i++)
			xa[i] = new int[N];
		for (int i = 0; i < N; i++)
			az[i] = new int[N];

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < N; k++) {
					int row = matrix[j][i];
					xa[j][k] = matrix[row][k];
				}
			}
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < N; k++) {
					int col = matrix[i][j];
					az[k][j] = matrix[col][k];
				}
			}
			if (!equal(xa, az)) {
				flag = false;
				break;
			}
		}

		if (flag) {
			cout << "The operation is associative" << endl;
		}
		else {
			cout << "The operation is not associative" << endl;
		}

	}

	void subsemigroup(vector<int> vec) {
		vector<int> a;
		for (int i = 0; i < vec.size(); i++) {
			a.push_back(vec[i]);
		}
		bool flag = true;

		while (flag) {
			flag = false;
			for (int i = 0; i < a.size(); i++) {
				for (int j = 0; j < a.size(); j++) {
					int newEl = matrix[i][j];
					if (find(a.begin(), a.end(), newEl) == a.end()) {
						a.push_back(newEl);
						flag = true;
					}
				}
			}
		}

		cout << endl << "Subsemigroup: " << endl << "{";
		for (int i = 0; i < a.size(); i++) {
			cout << " " << a[i];
		}
		cout << " }";
	}
};

int main() {
	int N;
	cout << "Enter the size of matrix." << endl << "Size: ";
	cin >> N;

	cout << endl << "Enter the matrix:" << endl;
	Matrix matrix(N);
	matrix.init();

	cout << endl << "Your matrix:" << endl;
	matrix.print();

	matrix.associativity();
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	int K;
	cout << "Enter the size of the generating set:" << endl;
	cin >> K;
	vector<int> genSet(K);
	cout << "Enter the generating set:" << endl;
	for (int i = 0; i < K; i++) {
		cin >> genSet[i];
	}

	int M;
	cout << "Enter the size of matrix." << endl << "Size: ";
	cin >> M;

	cout << endl << "Enter the matrix:" << endl;
	Matrix matr(M);
	matr.init();

	cout << endl << "Your matrix:" << endl;
	matr.print();
	cout << "Your generating set:" << endl;
	for (int i = 0; i < K; i++) {
		cout << genSet[i] << " ";
	}

	matr.subsemigroup(genSet);
}
