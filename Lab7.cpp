#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>

using namespace std;

struct three {
	int fst;
	string sym;
	int lst;
};

bool operator<(const three& first, const three& other) {
	if (first.fst != other.fst) {
		return first.fst < other.fst;
	}
	else if (first.sym != other.sym) {
		return first.sym < other.sym;
	}
	else if (first.lst != other.lst) {
		return first.lst < other.lst;
	}
	else return false;
}

void union_all(vector<three>& a) {
	for (int i = 0; i < a.size(); i++) {
		int x = a[i].fst;
		int y = a[i].lst;
		for (int j = i + 1; j < a.size(); j++) {
			if (a[j].fst == x && a[j].lst == y) {
				a[i].sym = "(" + a[i].sym + "+" + a[j].sym + ")";
				a.erase(a.begin() + j);
				j -= 1;
			}
		}
	}

}

void closure(vector<three>& a) {
	for (int i = 0; i < a.size(); i++) {
		int x = a[i].fst;
		int y = a[i].lst;
		if (x == y) {
			for (int j = 0; j < a.size(); j++) {
				if (a[j].lst == x && a[j].fst != x) {
					a[j].sym = a[j].sym + "(" + a[i].sym + ")*";
				}
			}
			a.erase(a.begin() + i);
			i -= 1;
		}
	}

}

void rationExp(vector<three>& a) {
	for (int i = 0; i < a.size(); i++) {
		int x = a[i].fst;
		int y = a[i].lst;
		bool flag = false;
		for (int j = 0; j < a.size(); j++) {
			if (a[j].fst == y) {
				a[j].fst = x;
				a[j].sym = a[i].sym + a[j].sym;
				flag = true;
			}
		}
		if (flag) {
			a.erase(a.begin() + i);
			i -= 1;
		}
	}

}

int main() {
	cout << "Enter automaton: \nZ: ";
	vector<string> sym;
	vector<int> state;

	vector<pair<string, vector<int>>> matr;

	string tmp;
	getline(cin, tmp, '\n');
	for (int i = 0; i < tmp.length(); i++) {
		if (tmp[i] != ' ') {
			state.push_back(tmp[i] - 48);
		}
	}


	cout << "A: ";
	tmp.clear();
	getline(cin, tmp, '\n');
	for (int i = 0; i < tmp.length(); i++) {
		if (tmp[i] != ' ') {
			sym.push_back(string(1, tmp[i]));
		}
	}

	cout << "E: " << endl;
	int** elem;
	elem = new int* [state.size()];

	for (int i = 0; i < state.size(); i++)
		elem[i] = new int[sym.size()];

	for (int i = 0; i < state.size(); i++) {
		for (int j = 0; j < sym.size(); j++) {
			cin >> elem[i][j];
		}
	}
	vector<three> help;
	for (int i = 0; i < sym.size(); i++) {

		for (int j = 0; j < state.size(); j++) {
			if (elem[j][i] == -1) continue;
			three* element = new three;
			element->fst = state[j];
			element->sym = sym[i];
			element->lst = elem[j][i];
			help.push_back(*element);
		}
	}
	int I, F;
	cout << "I: "; cin >> I;
	cout << "F: "; cin >> F;
	sort(help.begin(), help.end());

	union_all(help);

	closure(help);

	rationExp(help);
	cout << "\n\nRational expression";
	for (auto& e : help) {
		cout << "(" << e.fst << ", " << e.sym << ", " << e.lst << ") " << endl;
	}
}
