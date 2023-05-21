#include <iostream>
#include <vector>
using namespace std;

int N;

void print(bool** matr) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << matr[i][j] << " ";
		}
		cout << endl;
	}
}

bool** multiplication(bool** matrA, bool** matrB) {
	bool** multi;
	multi = new bool* [N];

	for (int i = 0; i < N; i++)
		multi[i] = new bool[N];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			multi[i][j] = false;
			for (int k = 0; k < N; k++)
				multi[i][j] = multi[i][j] | (matrA[i][k] & matrB[k][j]);
		}
	}

	return multi;
}

bool equal(bool** matrA, bool** matrB) {
	bool flag = true;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (matrA[i][j] != matrB[i][j]) {
				flag = false;
				break;
			}

		}
	}
	return flag;
}

bool myfind(vector<bool**> vec, bool** matr) {
	bool flag = false;
	for (int i = 0; i < vec.size(); i++) {
		if (equal(vec[i], matr)) {
			flag = true;
			break;
		}
	}
	return flag;
}

void semigroup(vector<bool**> vec) {
	vector<bool**> a;
	for (int i = 0; i < vec.size(); i++) {
		a.push_back(vec[i]);
	}
	bool flag = true;

	while (flag) {
		flag = false;

		bool** newEl;
		newEl = new bool* [N];

		for (int k = 0; k < N; k++)
			newEl[k] = new bool[N];

		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < a.size(); j++) {
				newEl = multiplication(a[i], a[j]);
				if (!myfind(a, newEl)) {
					a.push_back(newEl);
					flag = true;
				}
			}
		}
	}

	cout << endl << "Semigroup: " << endl << "{" << endl;
	for (int i = 0; i < a.size(); i++) {
		print(a[i]);
		cout << endl;
	}
	cout << " }";
}

int main() {
	int n;
	cout << "Enter the number of matrix: "; cin >> n;
	cout << endl << "Enter the size of matrix: ";
	cin >> N;
	cout << "Enter matrix:" << endl;
	vector<bool**> binmatrix(n);

	for (int i = 0; i < n; i++) {
		bool** newTran;
		newTran = new bool* [N];

		for (int j = 0; j < N; j++)
			newTran[j] = new bool[N];

		for (int k = 0; k < N; k++) {
			for (int j = 0; j < N; j++) {
				cin >> newTran[k][j];
			}
		}

		binmatrix[i] = newTran;
	}

	for (int i = 0; i < n; i++) {
		print(binmatrix[i]);
		cout << endl;
	}
	semigroup(binmatrix);
	return 0;
}
