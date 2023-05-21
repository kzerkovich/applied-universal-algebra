#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct three {
	int fst;
	string sym;
	int lst;
};

vector<char> letter(string tmp) {
	vector<char> res;
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i] == '(') continue;
		if (tmp[i] == ')') continue;
		if (tmp[i] == ' ') continue;
		if (tmp[i] == '+') continue;
		if (tmp[i] == '*') continue;
		if (find(res.begin(), res.end(), tmp[i]) == res.end()) res.push_back(tmp[i]);
	}
	return res;
}

int newPoint(vector<int>& allrd) {
	int i = 0;
	while (find(allrd.begin(), allrd.end(), i) != allrd.end()) i++;
	allrd.push_back(i);
	return i;
}

vector<three> deleteAutomaton(string tmp, int st, int end, vector<int>& allrd) {
	int count = 0;
	int oldst = st;
	int end2;
	string word = "";
	vector<three> split;
	for (int i = 0; i < tmp.size(); i++) {
		word = "";
		if (tmp[i] == '(') {
			count = 1;
			while (count != 0) {
				i++;
				if (tmp[i] == ')')	count -= 1;
				if (tmp[i] == '(')	count += 1;
				if (count != 0)	word += tmp[i];
			}
			if (i < tmp.size() - 1) {
				if (tmp[i + 1] == '*') {
					i++;
					if (i == tmp.size() - 1) {
						st = end;
						allrd.erase(allrd.end() - 1);
						split[split.size() - 1].lst = end;
					}
					split.push_back({ st, word, st });
					continue;
				}
			}
			if (i == tmp.size() - 1) end2 = end;
			else end2 = newPoint(allrd);
			split.push_back({ st, word, end2 });
			st = end2;
		}
		else {
			if (tmp[i] == '+') {
				st = oldst;
				allrd.erase(allrd.end() - 1);
				split[split.size() - 1].lst = end;

			}
			else {
				word += tmp[i];
				if (i == tmp.size() - 1) end2 = end;
				else end2 = newPoint(allrd);
				split.push_back({ st, word, end2 });
				st = end2;
			}
		}
	}
	return split;
}

vector<three> automaton(string tmp, int st, int end, vector<int>& allready) {
	int n = tmp.size();
	vector<three> vtmp, res, wres;
	vtmp = deleteAutomaton(tmp, st, end, allready);
	for (int i = 0; i < vtmp.size(); i++) {
		if (vtmp[i].sym.size() == 1) {
			res.push_back(vtmp[i]);
		}
		else {
			wres = automaton(vtmp[i].sym, vtmp[i].fst, vtmp[i].lst, allready);
			for (int i = 0; i < wres.size(); i++) {
				res.push_back(wres[i]);
			}
		}
	}
	return res;
}

int main() {
	string tmp;
	vector<char> vec;
	vector<three> vtmp;
	vector<int> vertex = { 0, 1 };
	cout << "Rational expression: " << endl;
	cin >> tmp;
	vec = letter(tmp);
	vtmp = automaton(tmp, 0, 1, vertex);

	cout << "\nAutomaton:\n";
	cout << "Z: { ";
	for (int i = 0; i < vertex.size(); i++) {
		cout << vertex[i] << " ";
	}
	cout << "}" << endl;
	cout << "A: { ";
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << "}" << endl;
	cout << "E: {" << endl;
	for (int i = 0; i < vtmp.size(); i++) {
		cout << "(" << vtmp[i].fst << ", " << vtmp[i].sym << ", " << vtmp[i].lst << ")" << endl;
	}
	cout << "}\nI: {0}" << endl << "F: {1}" << endl;
}
