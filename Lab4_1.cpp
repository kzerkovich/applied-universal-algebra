#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
vector <vector<int>> S;
vector <int> remain;

double fact(double i) {
	double b = 1;
	for (int j = 1; j < i + 1; j++) {
		b *= j;
	}
	return b;
}

void elementsOfGroup(int n) {
	vector <int> a;
	for (int i = 0; i < n; i++) {
		a.push_back(i);
	}
	S.push_back(a);
}

double formulaForDistance(vector<int> sn, vector<int> s) {
	if (s.size() > sn.size()) {
		swap(s, sn);
	}
	vector<vector<int>> temp(s.size());
	for (int j = 0; j < sn.size(); j++) {
		temp[sn[j] % s.size()].push_back(sn[j]);
	}
	double length = fact(sn.size()) / (fact(sn.size() - 2) * fact(2));
	double ll = 0;
	for (int i = 0; i < temp.size(); i++) {
		ll += fact(temp[i].size()) / (fact(temp[i].size() - 2) * fact(2));
	}
	return (ll / length);
}

void GCD() {
	int a;
	for (int i = 1; i <= max(remain[0], remain[1]); i++) {
		if (remain[0] % i == 0 and remain[1] % i == 0)
			a = i;
	}
	remain.push_back(a);
	elementsOfGroup(a);
}

double distanceBetweenGroups() {
	GCD();
	double tmp;
	if (remain[1] == 1 or remain[0] == 1) {
		tmp = 1;
	}
	else if (remain[0] == remain[1]) {
		tmp = 0;
	}
	else if (remain[2] == remain[0] or remain[1] == remain[0]) {
		tmp = formulaForDistance(S[0], S[1]);
	}
	else {
		tmp = 0.5 * (formulaForDistance(S[0], S[2]) + formulaForDistance(S[1], S[2]));
	}
	return tmp;
}

int main() {
	int S1, S2;
	cout << "Enter the size of first group: " << endl;
	cin >> S1;
	cout << endl << "Enter the size of second group: " << endl;
	cin >> S2;
	remain.push_back(S1);
	remain.push_back(S2);
	elementsOfGroup(S1);
	elementsOfGroup(S2);

	cout << endl << "Distance between groups: " << setprecision(5) << distanceBetweenGroups();
}
