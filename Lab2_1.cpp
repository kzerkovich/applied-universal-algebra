#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <set>
using namespace std;

struct help1 {
	set<int> num;
	set<string> word;
};

struct three {
	set<int> num;
	vector<help1> conn;
	set<string> word;
};

vector<vector<int>> matrix;
vector<set<int>> link;
vector<set<int>> grid;
set<set<int>> load;
vector<vector<set<int>>> hasse;
vector<vector<help1>> low;
vector<int> index;
vector<three> chapter;

void search() {
	set<int> tmp;
	for (int i = 0; i < matrix.size(); i++) {
		tmp.clear();
		for (int j = 0; j < matrix.size(); j++) {
			if (matrix[j][i] == 1)
			{
				tmp.insert(j + 1);
			}
		}
		link.push_back(tmp);
	}
}
void insertion() {
	for (int i = 0; i < link.size(); i++) {
		int a = grid.size();
		for (int j = 0; j < a; j++) {
			set<int> intersect;
			intersect.clear();
			set_intersection(link[i].begin(), link[i].end(),
				grid[j].begin(), grid[j].end(), std::inserter(intersect, intersect.begin()));
			grid.push_back(intersect);
		}
	}
	for (int i = 0; i < grid.size(); i++) {
		load.insert(grid[i]);
	}
	grid.clear();
	for (auto elem : load) {
		if (elem.size() == 0)
		{
			vector<set<int>> kont;
			kont.push_back(elem);
			hasse.push_back(kont);
		}
		else {
			grid.push_back(elem);
		}
	}
}
bool inc(set<int> a, set<int> b) {
	bool flag = true;
	for (auto it : a) {
		if (!(b.find(it) != b.end())) {
			flag = false;
			break;
		}
	}
	return flag;
}
bool include(set<int> a) {
	bool flag = false;
	for (auto it1 : grid) {
		if (it1 != a and inc(a, it1)) {
			flag = true;
		}
	}
	return flag;
}
void del() {
	vector<set<int>> tmp;
	for (int i = grid.size() - 1; i >= 0; i--) {
		if (!include(grid[i])) {
			tmp.push_back(grid[i]);
			index.push_back(i);
		}
	}
	hasse.push_back(tmp);
	for (auto i : index) {
		swap(grid[i], grid[grid.size() - 1]);
		grid.pop_back();
	}
	index.clear();
}
void mult() {
	while (grid.size() > 0) {
		del();
	}
}
vector<help1> prelast(int i, set<int> j) {
	vector<help1> temp;
	temp.clear();
	for (auto k : low[i + 1]) {
		if (inc(k.num, j)) {
			temp.push_back({ k.num, k.word });
		}
	}
	return temp;
}
void last() {
	for (int i = 0; i < low.size(); i++) {
		for (auto j : low[i]) {
			if (j.num.size() == 0) {
				break;
			}
			vector<help1> n;
			int k = i;
			while (n.size() == 0 and k < low.size() - 1) {
				n = prelast(k, j.num);
				k++;
			}
			if (n.size() == 0) {
				help1 a = { { 0 }, { "M" } };
				n = { a };
			}
			three lo = { j.num, n, j.word };
			chapter.push_back(lo);
		}
	}
}
help1 supernotlast(set<int> ork) {
	vector<set<string>> mm;
	set<string> tmp;
	string a;
	for (auto i : ork) {
		tmp.clear();
		for (int j = 0; j < matrix.size(); j++) {
			if (matrix[i - 1][j] == 1) {
				a = char(j + 'a');
				tmp.insert(a);
			}
		}
		mm.push_back(tmp);
	}
	set<string> b = mm[0];
	set<string> intersect;
	if (mm.size() == 1) {
		intersect = b;
	}
	for (int i = 1; i < mm.size(); i++) {
		set_intersection(b.begin(), b.end(), mm[i].begin(), mm[i].end(),
			std::inserter(intersect, intersect.begin()));
	}
	return { ork, intersect };
}
void notlast(int n) {
	vector<help1> tmp;
	for (int i = 0; i < hasse.size(); i++) {
		tmp.clear();
		for (auto k : hasse[i]) {
			if (k.size() == 0) {
				tmp.push_back({ k, {"M"} });
				break;
			}
			if (k.size() == n) {
				tmp.push_back({ k, {"0"} });
				break;
			}
			help1 a = supernotlast(k);
			tmp.push_back(a);
		}
		low.push_back(tmp);
	}
}
int main() {
	int n;
	cin >> n;
	set<int> temp;
	vector<int> tmp;
	for (int i = 0; i < n; i++) {
		tmp.clear();
		for (int j = 0; j < n; j++) {
			int b;
			cin >> b;
			tmp.push_back(b);
		}
		matrix.push_back(tmp);
		temp.insert(i + 1);
	}
	cout << "\nContext matrix:\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	grid.push_back(temp);
	search();
	insertion();
	mult();
	notlast(n);

	cout << "\nGrid of concepts:\n";
	bool flag1 = false;
	for (int i = 0; i < low.size(); i++) {
		if (low[i].size() == 1 and low[i][0].num.size() == 0) {
			flag1 = true;
		}
		else {
			for (int j = 0; j < low[i].size(); j++) {
				cout << "({ ";
				for (auto k : low[i][j].num) {
					cout << k << " ";
				}
				cout << "}, ";
				cout << "{ ";
				for (auto k : low[i][j].word) {
					cout << k << " ";
				}
				cout << "}), ";
			}
		}
	}
	if (flag1) {
		cout << "({ 0, M })\n";
	}

	cout << "\nHasse Diagram:\n";
	bool flag = false;
	for (int i = 0; i < low.size(); i++) {
		if (low[i].size() == 1 and low[i][0].num.size() == 0) {
			flag = true;
		}
		else {
			cout << "Level " << low.size() - i + 1 << ": ";
			for (int j = 0; j < low[i].size(); j++) {
				cout << "({ ";
				for (auto k : low[i][j].num) {
					cout << k << " ";
				}
				cout << "}, { ";
				for (auto k : low[i][j].word) {
					cout << k << " ";
				}
				cout << "})" << setw(5);
			}
			cout << endl;
		}
	}
	if (flag) {
		cout << "Level 1: ({ 0 }, { M })\n\n";
	}

	last();
	cout << "Edges:\n";
	for (int i = 0; i < chapter.size(); i++) {
		cout << "({ ";
		for (auto j : chapter[i].num) {
			cout << j << " ";
		}
		cout << "}, { ";
		for (auto j : chapter[i].word) {
			cout << j << " ";
		}
		cout << "}):" << setw(5);
		for (int k = 0; k < chapter[i].conn.size(); k++) {
			cout << "({ ";
			for (auto l : chapter[i].conn[k].num) {
				cout << l << " ";
			}
			cout << "}, { ";
			for (auto l : chapter[i].conn[k].word) {
				cout << l << " ";
			}
			cout << "})";
			if (k < chapter[i].conn.size() - 1) {
				cout << ", ";
			}
		}
		cout << endl;
	}
}
