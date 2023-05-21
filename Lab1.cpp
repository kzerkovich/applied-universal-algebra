#include <iostream>
#include <vector>
using namespace std;

class Matrix {
	int N;
	bool** matrix;


	bool** matrixMultiplication(bool** matr) {
		bool** multi;
		multi = new bool* [N];

		for (int i = 0; i < N; i++)
			multi[i] = new bool[N];

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				multi[i][j] = false;
				for (int k = 0; k < N; k++)
					multi[i][j] = multi[i][j] | (matr[i][k] & matr[k][j]);
			}
		}

		return multi;
	}

	void printClosure(bool** matr) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << matr[i][j] << " ";
			}
			cout << endl;
		}
	}

	void printVector(vector<pair<int, int>> vec) {
		for (int i = 0; i < vec.size(); i++) {
			cout << "(" << vec[i].first << ", " << vec[i].second << ")" << endl;
		}
	}


	bool transitivityClosure(bool** matr) {
		bool helpTranFlag = true;
		bool** multiMatrix = matrixMultiplication(matr);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (multiMatrix[i][j] > matr[i][j]) helpTranFlag = false;
			}
		}
		return helpTranFlag;
	}

public:

	bool refFlag = true,
		irrefFlag = true,
		symmFlag = true,
		ansymmFlag = true,
		tranFlag = true,
		strConnFlag = true;

	vector<pair<int, int>> refAdd;
	vector<pair<int, int>> symmAdd;
	vector<pair<int, int>> tranAdd;

	Matrix(int N) {
		this->N = N;
		matrix = new bool* [N];

		for (int i = 0; i < N; i++)
			matrix[i] = new bool[N];

	}

	void init() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> matrix[i][j];
			}
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

	void reflexivity() {
		for (int i = 0; i < N; i++) {
			if (!matrix[i][i]) refFlag = false;
		}
	}

	void irreflexivity() {
		for (int i = 0; i < N; i++) {
			if (matrix[i][i]) irrefFlag = false;
		}
	}

	void symmetric() {
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				if (matrix[i][j] != matrix[j][i]) symmFlag = false;
			}
		}
	}

	void antisymmetric() {
		for (int i = 0; i < N; i++) {
			for (int j = i; j < N; j++) {
				if ((matrix[i][j] == matrix[j][i]) && matrix[i][j]) ansymmFlag = false;
			}
		}
	}

	void transitivity() {
		bool** multiMatrix = matrixMultiplication(matrix);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (multiMatrix[i][j] > matrix[i][j]) tranFlag = false;
			}
		}
	}

	void stronglyConnected() {
		for (int i = 0; i < N; i++) {
			for (int j = i; j < N; j++) {
				if (!(matrix[i][j] || matrix[j][i]) && !matrix[i][i]) strConnFlag = false;
			}
		}
	}

	void refHelp(bool** matr) {
		for (int i = 0; i < N; i++) {
			if (!matr[i][i]) {
				refAdd.push_back(make_pair(i + 1, i + 1));
				matr[i][i] = true;
			}
		}
	}

	void symmHelp(bool** matr) {
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				if (matr[i][j] != matr[j][i]) {
					if (matr[i][j]) {
						symmAdd.push_back(make_pair(j + 1, i + 1));
						matr[j][i] = true;
					}
					else {
						symmAdd.push_back(make_pair(i + 1, j + 1));
						matr[i][j] = true;
					}
				}
			}
		}
	}

	void tranHelp(bool** matr) {
		while (!transitivityClosure(matr)) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (matr[i][j]) {
						for (int k = 0; k < N; k++) {
							if (matr[j][k]) {
								if (!matr[i][k]) {
									tranAdd.push_back(make_pair(i + 1, k + 1));
									matr[i][k] = true;
								}
							}
						}
					}
				}
			}
		}
	}

	void reflexiveClosure() {
		if (refFlag) {
			cout << "Your binary relation is already reflexive." << endl;
			print();
		}
		else {
			bool** newRef;
			newRef = new bool* [N];

			for (int i = 0; i < N; i++)
				newRef[i] = new bool[N];

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					newRef[i][j] = matrix[i][j];
				}
			}

			refHelp(newRef);

			cout << "Reflexive closure:" << endl;
			printClosure(newRef);
			cout << "Added pairs:" << endl;
			printVector(refAdd);
			refAdd.clear();
		}
	}

	void symmetricClosure() {
		if (symmFlag) {
			cout << "Your binary relation is already symmetric." << endl;
			print();
		}
		else {
			bool** newSymm;
			newSymm = new bool* [N];

			for (int i = 0; i < N; i++)
				newSymm[i] = new bool[N];

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					newSymm[i][j] = matrix[i][j];
				}
			}

			symmHelp(newSymm);

			cout << "Symmetric closure:" << endl;
			printClosure(newSymm);
			cout << "Added pairs:" << endl;
			printVector(symmAdd);
			symmAdd.clear();
		}
	}

	void transitiveClosure() {
		if (tranFlag) {
			cout << "Your binary relation is already transitive." << endl;
			print();
		}
		else {
			bool** newTran;
			newTran = new bool* [N];

			for (int i = 0; i < N; i++)
				newTran[i] = new bool[N];

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					newTran[i][j] = matrix[i][j];
				}
			}

			tranHelp(newTran);

			cout << "Transitive closure:" << endl;
			printClosure(newTran);
			cout << "Added pairs:" << endl;
			printVector(tranAdd);
			tranAdd.clear();
		}
	}

	void equivalenceÑlasses(bool** matr) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i != j && matr[i][j]) {
					for (int k = 0; k < N; k++) {
						matr[j][k] = false;
						matr[k][j] = false;
					}
				}

			}
		}
	}

	void equivalenceClosure() {
		if (refFlag && symmFlag && tranFlag) {
			cout << "Your binary relation is already equivalent." << endl;
			print();

			equivalenceÑlasses(matrix);

			cout << endl << "Elements of the set included in the complete system of representatives:" << endl;
			for (int i = 0; i < N; i++) {
				if (matrix[i][i]) cout << i + 1 << " ";
			}
		}
		else {
			bool** newEq;
			newEq = new bool* [N];

			for (int i = 0; i < N; i++)
				newEq[i] = new bool[N];

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					newEq[i][j] = matrix[i][j];
				}
			}

			refHelp(newEq);
			symmHelp(newEq);
			tranHelp(newEq);
			cout << "Equivalent closure:" << endl;
			printClosure(newEq);
			cout << "Added pairs:" << endl;
			printVector(refAdd);
			printVector(symmAdd);
			printVector(tranAdd);

			equivalenceÑlasses(newEq);

			cout << endl << "Elements of the set included in the complete system of representatives:" << endl;
			for (int i = 0; i < N; i++) {
				if (newEq[i][i]) cout << i + 1 << " ";
			}

		}
	}
};

string convert(bool flag) {
	return (flag ? "+" : "-");
}

int main() {
	int N;
	cout << "Enter the size of matrix." << endl << "Size: ";
	cin >> N;

	cout << endl << "Enter the matrix:" << endl;
	Matrix matrix(N);
	matrix.init();

	cout << endl << "Your matrix:" << endl;
	matrix.print();

	matrix.reflexivity();
	matrix.irreflexivity();
	matrix.symmetric();
	matrix.antisymmetric();
	matrix.transitivity();
	matrix.stronglyConnected();

	cout << endl << "Properties of your binary relation:" << endl;
	cout << "Reflexivity: " << convert(matrix.refFlag) << endl;
	cout << "Irreflexivity: " << convert(matrix.irrefFlag) << endl;
	cout << "Symmetric: " << convert(matrix.symmFlag) << endl;
	cout << "Antisymmetric: " << convert(matrix.ansymmFlag) << endl;
	cout << "Transitivity: " << convert(matrix.tranFlag) << endl;
	cout << "Strongly connected: " << convert(matrix.strConnFlag) << endl;


	cout << endl;
	matrix.reflexiveClosure();
	cout << endl;
	matrix.symmetricClosure();
	cout << endl;
	matrix.transitiveClosure();
	cout << endl;
	matrix.equivalenceClosure();

	return 0;
}
