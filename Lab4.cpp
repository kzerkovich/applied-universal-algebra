#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;
vector<pair<vector<vector<int>>, string>> A;
vector<vector<string>> R;

bool operator==(const pair<vector<vector<int>>, string>& a, const pair<vector<vector<int>>, string>& b) { return (a.first == b.first); }

vector<vector<int>> multiplyMatrix(vector<vector<int>> a, vector<vector<int>> b, int n) {
	vector<vector<int>> c;
	vector<int> aba(n);
	for (int i = 0; i < n; i++) {
		aba[i] = i + 1;
	}
	c.push_back(aba);
	vector<int> aba1(n);
	for (int i = 0; i < n; i++) {
		aba1[i] = b[1][a[1][i] - 1];
	}
	c.push_back(aba1);
	return c;
}

int index(vector<vector<int>> a) {
	int i;
	for (i = 0; i < A.size(); i++) {
		if (a == A[i].first) {
			break;
		}
	}
	return i;
}

void newMatrix(int n) {
	bool flag = true;
	while (flag) {
		flag = false;
		for (auto i : A) {
			for (auto j : A) {
				if (find_if(A.begin(), A.end(), [=](const pair<vector<vector<int>>, string>& x) { return x.first == multiplyMatrix(i.first, j.first, n); }) != A.end()) {
					continue;
				}
				else {
					flag = true;
					A.push_back(make_pair(multiplyMatrix(i.first, j.first, n), i.second + j.second));
					break;
				}
			}
			if (flag) {
				break;
			}
		}
	}
}

void tableCayley(int n) {
	R.resize(A.size(), vector<string>(A.size()));
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A.size(); j++) {
			R[i][j] = A[index(multiplyMatrix(A[i].first, A[j].first, n))].second;
		}
	}
}

int main() {
	int n = 3;
	A = { {{{1, 2, 3}, {2, 3, 1}}, "x"}, {{{1, 2, 3}, {2, 2, 2}}, "y"} };
	newMatrix(n);
	tableCayley(n);
	cout << "Semigroup <A|R>" << endl << "{";
	int ll = 1;
	for (auto i : A) {
		cout << i.second << " ";
	}
	cout << "}" << endl << endl;
	for (auto i : A) {
		cout << "Matrix " << ll++ << ":" << endl;
		for (auto j : i.first) {
			for (auto k : j) {
				cout << k << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << "Cayley table" << endl << setw(8) << "*" << setw(8);
	for (int i = 0; i < A.size(); i++) {
		cout << A[i].second << setw(8);
	}
	cout << endl;
	for (int i = 0; i < R.size(); i++) {
		cout << A[i].second << setw(8);
		for (auto j : R[i]) {
			cout << j << setw(8);
		}
		cout << endl;
	}
	cout << endl << "The left cayley graph:" << endl;
	for (int i = 0; i < A.size(); i++) {
		cout << endl << "Element " << A[i].second << ": " << endl;
		for (int j = 0; j < A.size(); j++) {
			cout << A[i].second << " converts " << A[j].second << " to " << R[i][j] << endl;
		}
	}
	cout << endl << "The right cayley graph:" << endl;
	for (int i = 0; i < A.size(); i++) {
		cout << endl << "Element " << A[i].second << ": " << endl;
		for (int j = 0; j < A.size(); j++) {
			cout << A[i].second << " converts " << A[j].second << " to " << R[j][i] << endl;
		}
	}
}
