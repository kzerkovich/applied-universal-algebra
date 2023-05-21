#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int alt(char sym) {
	if (sym == 'a') return 0;
	if (sym == 'b') return 1;
	if (sym == 'c') return 2;
	if (sym == 'd') return 3;
}

void ideals(vector<vector<char>>& matrix, vector<int>& altGen, vector<char>& gen) {
	for (int i = 0; i < gen.size(); i++) {
		set<char> leftIdeal;
		set<char> rightIdeal;
		set<char> tsIdeal;

		for (int j = 0; j < matrix.size(); j++) {
			leftIdeal.insert(matrix[j][altGen[i]]);
			rightIdeal.insert(matrix[altGen[i]][j]);

			char temp = matrix[j][altGen[i]];

			tsIdeal.insert(matrix[alt(temp)][j]);
		}
		tsIdeal.insert(leftIdeal.begin(), leftIdeal.end());
		tsIdeal.insert(rightIdeal.begin(), rightIdeal.end());

		cout << "Left ideal for element " << gen[i] << ": { ";
		for (auto const& e : leftIdeal) {
			std::cout << e << " ";
		}
		cout << "}" << endl;
		cout << "Right ideal for element " << gen[i] << ": { ";
		for (auto const& e : rightIdeal) {
			std::cout << e << " ";
		}
		cout << "}" << endl;
		cout << "Two-sided ideal for element " << gen[i] << ": { ";
		for (auto const& e : tsIdeal) {
			std::cout << e << " ";
		}
		cout << "}" << endl << endl;
	}
}

bool myFind(char s, set<set<char>> classes) {
	bool flag = false;
	for (auto const& e : classes) {
		for (auto const& t : e) {
			if (t == s) flag = true;
		}
	}
	return flag;
}

void GreensRelations(vector<vector<char>>& matrix, vector<int>& altGen, vector<char>& gen) {
	vector<pair<set<char>, char>> r;
	vector<pair<set<char>, char>> l;
	for (int i = 0; i < gen.size(); i++) {
		set<char> leftIdeal;
		set<char> rightIdeal;

		for (int j = 0; j < matrix.size(); j++) {
			leftIdeal.insert(matrix[j][altGen[i]]);
			rightIdeal.insert(matrix[altGen[i]][j]);
		}

		l.push_back(make_pair(leftIdeal, gen[i]));
		r.push_back(make_pair(rightIdeal, gen[i]));
	}

	set<set<char>> LClasses;
	set<set<char>> RClasses;

	for (int i = 0; i < l.size(); i++) {
		for (int j = 0; j < l.size(); j++) {
			if (i != j) {
				if (l[i].first == l[j].first) {
					set<char> temp;
					temp.insert(l[i].second);
					temp.insert(l[j].second);
					LClasses.insert(temp);
				}

			}
		}

		if (!myFind(l[i].second, LClasses)) {
			set<char> tmp;
			tmp.insert(l[i].second);
			LClasses.insert(tmp);
		}

	}

	for (int i = 0; i < r.size(); i++) {
		for (int j = 0; j < r.size(); j++) {
			if (i != j) {
				if (r[i].first == r[j].first) {
					set<char> temp;
					temp.insert(r[i].second);
					temp.insert(r[j].second);
					RClasses.insert(temp);
				}

			}
		}

		if (!myFind(r[i].second, RClasses)) {
			set<char> tmp;
			tmp.insert(r[i].second);
			RClasses.insert(tmp);
		}

	}
	set<set<char>> DClasses;

	DClasses.insert(LClasses.begin(), LClasses.end());
	DClasses.insert(RClasses.begin(), RClasses.end());

	set<set<char>> HClasses;
	set_intersection(LClasses.begin(), LClasses.end(), RClasses.begin(), RClasses.end(), inserter(HClasses, HClasses.begin()));

	cout << "L Green's relation: ";
	for (auto const& e : LClasses) {
		cout << "{ ";
		for (auto const& t : e) {
			cout << t << " ";
		}
		cout << "} ";
	}
	cout << endl;

	cout << "R Green's relation: ";
	for (auto const& e : RClasses) {
		cout << "{ ";
		for (auto const& t : e) {
			cout << t << " ";
		}
		cout << "} ";
	}

	cout << endl;

	cout << "D Green's relation: ";
	for (auto const& e : DClasses) {
		cout << "{ ";
		for (auto const& t : e) {
			cout << t << " ";
		}
		cout << "} ";
	}

	cout << endl;

	cout << "H Green's relation: ";
	for (auto const& e : HClasses) {
		cout << "{ ";
		for (auto const& t : e) {
			cout << t << " ";
		}
		cout << "} ";
	}
	cout << endl;
	cout << endl << endl << "Egg-box-diagram" << endl;
	for (auto const& e : DClasses) {
		cout << "-------" << endl;
		for (auto const& t : e) {
			cout << "[" << t << "] ";
		}
		cout << endl;
	}
	cout << "-------";
}

int main() {
	cout << "Enter the size of semigroup:" << endl;
	int n; cin >> n;

	cout << "Enter the semigroup" << endl;

	vector<vector<char>> semigroup;
	semigroup.resize(n, vector<char>(n));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> semigroup[i][j];
		}
	}

	cout << "Enter the size of generating set:" << endl;
	int k; cin >> k;

	cout << "Enter generating set:" << endl;

	vector<char> genSet;
	vector<int> altGenSet;

	for (int i = 0; i < k; i++) {
		char elem; cin >> elem;
		genSet.push_back(elem);
		altGenSet.push_back(alt(elem));
	}

	cout << endl << "Your semigroup:" << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << semigroup[i][j] << " ";
		}
		cout << endl;
	}

	cout << "Your generating set:" << endl;

	for (int i = 0; i < k; i++) {
		cout << genSet[i] << " ";
	}
	cout << endl << endl;
	ideals(semigroup, altGenSet, genSet);
	GreensRelations(semigroup, altGenSet, genSet);
}
