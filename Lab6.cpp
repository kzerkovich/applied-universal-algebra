#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

struct three {
	int fst;
	char sym;
	int lst;

	bool operator<(const three& other) const {
		if (fst != other.fst) {
			return fst < other.fst;
		}
		else if (sym != other.sym) {
			return sym < other.sym;
		}
		else if (lst != other.lst) {
			return lst < other.lst;
		}
		else return false;
	}
};

struct automaton {
	set<int> Z;
	set<char> A;
	set<three> E;
	set<int> I;
	set<int> F;
};

void readAuto(automaton& A) {
	cout << "Z: ";
	string tmp;
	getline(cin, tmp, '\n');
	for (int i = 0; i < tmp.length(); i++) {
		if (tmp[i] != ' ') {
			A.Z.insert(tmp[i] - 48);
		}
	}
	cout << "A: ";
	tmp.clear();
	getline(cin, tmp, '\n');
	for (int i = 0; i < tmp.length(); i++) {
		if (tmp[i] != ' ') {
			A.A.insert(tmp[i]);
		}
	}
	cout << "E: ";
	tmp.clear();
	getline(cin, tmp, '\n');
	for (int i = 0; i < tmp.length(); i++) {
		if (tmp[i] == '(') {
			three* elem = new three;
			elem->fst = (tmp[i + 1] - 48);
			elem->sym = tmp[i + 4];
			elem->lst = (tmp[i + 7] - 48);
			A.E.insert(*elem);
		}
		else continue;
	}
	cout << "I: ";
	tmp.clear();
	getline(cin, tmp, '\n');
	for (int i = 0; i < tmp.length(); i++) {
		if (tmp[i] != ' ') {
			A.I.insert(tmp[i] - 48);
		}
	}
	cout << "F: ";
	tmp.clear();
	getline(cin, tmp, '\n');
	for (int i = 0; i < tmp.length(); i++) {
		if (tmp[i] != ' ') {
			A.F.insert(tmp[i] - 48);
		}
	}
}

void printAuto(automaton& A) {
	cout << "Z: ";
	for (auto& e : A.Z) {
		cout << e << " ";
	}
	cout << endl << "A: ";
	for (auto& e : A.A) {
		cout << e << " ";
	}
	cout << endl << "E: ";
	for (auto& e : A.E) {
		cout << "(" << e.fst << ", " << e.sym << ", " << e.lst << ") ";
	}
	cout << endl << "I: ";
	for (auto& e : A.I) {
		cout << e << " ";
	}
	cout << endl << "F: ";
	for (auto& e : A.F) {
		cout << e << " ";
	}
}

void sumAuto(automaton& A1, automaton& A2) {
	automaton res;
	set<int> inter;
	set_intersection(A1.Z.begin(), A1.Z.end(), A2.Z.begin(), A2.Z.end(), inserter(inter, inter.begin()));
	if (inter.empty()) {
		res.Z.insert(A1.Z.begin(), A1.Z.end());
		res.Z.insert(A2.Z.begin(), A2.Z.end());
		res.E.insert(A1.E.begin(), A1.E.end());
		res.E.insert(A2.E.begin(), A2.E.end());
		res.I.insert(A1.I.begin(), A1.I.end());
		res.I.insert(A2.I.begin(), A2.I.end());
		res.F.insert(A1.F.begin(), A1.F.end());
		res.F.insert(A2.F.begin(), A2.F.end());
		res.A.insert(A1.A.begin(), A1.A.end());
		cout << "Automaton A1 + A2:" << endl;
		printAuto(res);
	}
	else {
		set<int> new_I, new_F;
		new_I.insert(A1.I.begin(), A1.I.end());
		new_I.insert(A2.I.begin(), A2.I.end());
		new_F.insert(A1.F.begin(), A1.F.end());
		new_F.insert(A2.F.begin(), A2.F.end());
		res.Z.insert(A1.Z.begin(), A1.Z.end());
		res.Z.insert(A2.Z.begin(), A2.Z.end());
		res.A.insert(A1.A.begin(), A1.A.end());
		res.E.insert(A1.E.begin(), A1.E.end());
		res.E.insert(A2.E.begin(), A2.E.end());

		cout << "Automaton A1 + A2:" << endl;
		cout << "Z: ";
		for (auto& e : res.Z) {
			cout << e << " ";
		}
		cout << "i0 f0" << endl << "A: ";
		for (auto& e : res.A) {
			cout << e << " ";
		}
		cout << endl << "E: ";
		for (auto& e : res.E) {
			cout << "(" << e.fst << ", " << e.sym << ", " << e.lst << ") ";
		}
		for (auto& e : new_I) {
			cout << "(i0, ^, " << e << ") ";
		}
		for (auto& e : new_F) {
			cout << "(" << e << ", ^, f0) ";
		}
		cout << endl << "I: i0";
		cout << endl << "F: f0";
	}
}

void multiAuto(automaton& A1, automaton& A2) {
	automaton res;
	res.Z.insert(A1.Z.begin(), A1.Z.end());
	res.Z.insert(A2.Z.begin(), A2.Z.end());
	res.A.insert(A1.A.begin(), A1.A.end());
	res.E.insert(A1.E.begin(), A1.E.end());
	res.E.insert(A2.E.begin(), A2.E.end());
	cout << "Automaton A1 * A2:" << endl;
	cout << "Z: ";
	for (auto& e : res.Z) {
		cout << e << " ";
	}
	cout << "i0 f0" << endl << "A: ";
	for (auto& e : res.A) {
		cout << e << " ";
	}
	cout << endl << "E: ";
	for (auto& e : res.E) {
		cout << "(" << e.fst << ", " << e.sym << ", " << e.lst << ") ";
	}
	for (auto& e : A1.I) {
		cout << "(i0, ^, " << e << ") ";
	}
	for (auto& e : A2.F) {
		cout << "(" << e << ", ^, f0) ";
	}
	for (auto& e : A1.F) {
		for (auto& k : A2.I) {
			cout << "(" << e << ", ^, " << k << ") ";
		}
	}
	cout << endl << "I: i0";
	cout << endl << "F: f0";
}

void composAuto(automaton& A1, automaton& A2) {
	cout << "Automaton compose A1 and A2:" << endl;
	cout << "Z: ";
	for (auto& e : A1.Z) {
		for (auto& k : A2.Z) {
			cout << "(" << e << ", ^, " << k << ") ";
		}
	}
	cout << endl << "A: ";
	for (auto& e : A1.A) {
		cout << e << " ";
	}
	cout << endl << "E: ";
	for (auto& e : A1.E) {
		for (auto& k : A2.E) {
			cout << "((" << e.fst << ", " << k.fst << "), " << "(" << e.sym << ", " << k.sym << "), " << "(" << e.lst << ", " << k.lst << ")) ";
		}
	}
	cout << endl << "I: ";
	for (auto& e : A1.I) {
		for (auto& k : A2.I) {
			cout << "(" << e << ", " << k << ") ";
		}
	}
	cout << endl << "F: ";
	for (auto& e : A1.F) {
		for (auto& k : A2.F) {
			cout << "(" << e << ", " << k << ") ";
		}
	}
}

int main() {
	cout << "Enter the first automaton:" << endl;
	automaton A1, A2;
	readAuto(A1);
	cout << "Enter the second automaton:" << endl;
	readAuto(A2);
	sumAuto(A1, A2); cout << endl;
	multiAuto(A1, A2); cout << endl;
	composAuto(A1, A2);
}
