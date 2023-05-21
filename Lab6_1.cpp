#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

pair<string, vector<int>> multiplication(pair<string, vector<int>> A, pair<string, vector<int>> B) {
	string n = A.first + B.first;
	vector<int> help;
	for (int i = 0; i < A.second.size(); i++) {
		help.push_back(B.second[A.second[i] - 1]);
	}
	return make_pair(n, help);
}

bool myfind(vector<pair<string, vector<int>>> vec, pair<string, vector<int>> matr) {
	bool flag = false;
	for (int i = 0; i < vec.size(); i++) {
		if (matr.second[0] == vec[i].second[0] && matr.second[1] == vec[i].second[1] && matr.second[2] == vec[i].second[2]) {
			flag = true;
			break;
		}
	}
	return flag;
}


void monoid(vector<pair<string, vector<int>>> vec) {
	vector<pair<string, vector<int>>> a;
	for (int i = 0; i < vec.size(); i++) {
		a.push_back(vec[i]);
	}
	bool flag = true;

	while (flag) {
		flag = false;

		pair<string, vector<int>> newEl;

		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < vec.size(); j++) {
				newEl = multiplication(a[i], vec[j]);
				if (!myfind(a, newEl)) {
					a.push_back(newEl);
					flag = true;
				}
			}
		}
	}

	cout << endl << "Monoid: " << "{ ";
	for (int i = 0; i < a.size(); i++) {
		cout << a[i].first << " ";
	}
	cout << "}";
}

int main() {
	cout << "Enter the alphabet: ";
	vector<string> sym;
	vector<int> state;

	vector<pair<string, vector<int>>> matr;

	string tmp;
	getline(cin, tmp, '\n');
	for (int i = 0; i < tmp.length(); i++) {
		if (tmp[i] != ' ') {
			sym.push_back(string(1, tmp[i]));
		}
	}

	cout << "Enter the statement: ";
	tmp.clear();
	getline(cin, tmp, '\n');
	for (int i = 0; i < tmp.length(); i++) {
		if (tmp[i] != ' ') {
			state.push_back(tmp[i] - 48);
		}
	}

	cout << "Enter the table:" << endl;
	int** elem;
	elem = new int* [state.size()];

	for (int i = 0; i < state.size(); i++)
		elem[i] = new int[sym.size()];

	for (int i = 0; i < state.size(); i++) {
		for (int j = 0; j < sym.size(); j++) {
			cin >> elem[i][j];
		}
	}

	for (int i = 0; i < sym.size(); i++) {
		vector<int> help;
		help.clear();
		for (int j = 0; j < state.size(); j++) {
			help.push_back(elem[j][i]);
		}
		matr.push_back(make_pair(sym[i], help));
	}

	monoid(matr);
}
