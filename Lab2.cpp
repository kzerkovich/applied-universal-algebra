#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


bool compMax(pair<int, int> a, pair<int, int> b) { return a.second < b.second; };
vector<pair<int, int>> help;

void minMax(vector<int>& vec, int n) {
	help = vector<pair<int, int>>(n);
	for (int i = 0; i < n; i++) {
		int count = 0;
		for (int j = 0; j < n; j++) {
			if ((vec[j] % vec[i]) == 0 && i != j) count++;
		}
		help[i] = make_pair(vec[i], count);
	}

	vector<int> max_list;
	vector<int> min_list;

	vector<pair<int, int>>::iterator max = max_element(help.begin(), help.end(), compMax);
	int maximum = (*max).second;

	vector<pair<int, int>>::iterator min = min_element(help.begin(), help.end(), compMax);
	int minimum = (*min).second;

	for (int i = 0; i < n; i++) {
		if (help[i].second == maximum) max_list.push_back(help[i].first);
		if (help[i].second == minimum) min_list.push_back(help[i].first);
	}

	if (max_list.size() > 1) {
		cout << "The smallest element is missing." << endl << "Minimum elements: ";
		for (int i = 0; i < max_list.size(); i++) cout << max_list[i] << " ";
	}
	else {
		cout << endl << "Minimum and smallest element: " << max_list[0] << endl;
	}

	if (min_list.size() > 1) {
		cout << endl << "The largest element is missing." << endl << "Maximum elements: ";
		for (int i = 0; i < min_list.size(); i++) cout << min_list[i] << " ";
	}
	else {
		cout << endl << "Maximum and largest element: " << min_list[0];
	}
	cout << endl;
}

void remove(std::vector<int>& v) {
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}
	v.erase(end, v.end());
}

void hasseDiagram(vector<pair<int, int>>& vec) {
	int n = vec.size();
	vector<int> div(n);

	for (int i = 0; i < n; i++) div[i] = vec[i].second;

	remove(div);
	sort(div.begin(), div.end());
	cout << endl << "Hasse Diagram: " << endl;
	int k = div.size();
	for (int i = 0; i < k; i++) {
		cout << "Level " << k - i << ": ";
		for (int j = 0; j < n; j++) {
			if (vec[j].second == div[i]) cout << vec[j].first << " ";
		}
		cout << endl;
	}

	cout << endl << "Edges: " << endl;

	for (int i = 0; i < k - 1; i++) {
		cout << "Level " << k - i - 1 << " to " << k - i << ": ";
		for (int j = 0; j < n; j++) {
			if (vec[j].second == div[i]) {
				for (int l = 0; l < n; l++) {
					if (vec[l].second == div[i + 1] && (vec[j].first % vec[l].first == 0))
						cout << "(" << vec[l].first << ", " << vec[j].first << ") ";
				}
			}
		}
		cout << endl;
	}
}

int main() {
	int n;
	cout << "Enter the size of array" << endl << "Size: "; cin >> n;

	vector<int> relation(n);
	cout << "Enter the order relation: " << endl;

	for (int i = 0; i < n; i++) cin >> relation[i];

	minMax(relation, n);

	hasseDiagram(help);
