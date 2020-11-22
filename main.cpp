#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <map>
using namespace std;
struct Atom {
	string type = "";
	int num = 1;
};
struct Molecule {
	vector<Atom>vec;
	int num = 1;
};
vector<Molecule>vecL, vecR;
Atom getAtom() {
	Atom atom;
	char c = cin.get();
	atom.type += c;
	while (islower(c = cin.peek())) {
		atom.type += c;
		cin.get();
	}
	atom.num = 0;
	while (isdigit(c)) {
		cin.get();
		atom.num *= 10;
		atom.num += (c - '0');
		c = cin.peek();
	}
	if (atom.num == 0) {
		atom.num = 1;
	}
	return atom;
}
Molecule getMolecule() {
	Molecule mol;
	mol.num = 1;
	while (isalpha(cin.peek())) {
		Atom temp = getAtom();
		mol.vec.push_back(temp);
	}
	return mol;
}
void print() {
	int numL = vecL.size();
	int numR = vecR.size();
	for (int i = 0; i < numL; i++) {
		int temp = vecL[i].vec.size();
		cout << "(";
		for (int j = 0; j < temp; j++) {
			cout << vecL[i].vec[j].type;
			if (vecL[i].vec[j].num != 1) {
				cout << vecL[i].vec[j].num;
			}
		}
		cout << ")";
		if (vecL[i].num != 1) {
			cout << vecL[i].num;
		}
		if (i != numL - 1) {
			cout << "+";
		}
	}
	cout << "=";
	for (int i = 0; i < numR; i++) {
		int temp = vecR[i].vec.size();
		cout << "(";
		for (int j = 0; j < temp; j++) {
			cout << vecR[i].vec[j].type;
			if (vecR[i].vec[j].num != 1) {
				cout << vecR[i].vec[j].num;
			}
		}
		cout << ")";
		if (vecR[i].num != 1) {
			cout << vecR[i].num;
		}
		if (i != numR - 1) {
			cout << "+";
		}
	}
	cout << endl;
}
bool is_OK() {
	map<string, int>Map;
	int numL = vecL.size();
	for (int i = 0; i < numL; i++) {
		int temp = vecL[i].vec.size();
		for (int j = 0; j < temp; j++) {
			Map[vecL[i].vec[j].type] += (vecL[i].vec[j].num * vecL[i].num);
		}
	}
	int numR = vecR.size();
	for (int i = 0; i < numR; i++) {
		int temp = vecR[i].vec.size();
		for (int j = 0; j < temp; j++) {
			Map[vecR[i].vec[j].type] -= (vecR[i].vec[j].num * vecR[i].num);
		}
	}
	for (auto pre : Map) {
		if (pre.second != 0) {
			return false;
		}
	}
	return true;
}
bool dfs(bool is_left, int k, int n) {
	int numL = vecL.size();
	int numR = vecR.size();
	if (is_left && (k == numL)) {
		return dfs(false, 0, n);
	}
	else if ((!is_left) && (k == numR)) {
		return is_OK();
	}
	else{
		for (int i = 1; i <= n; i++) {
			if (is_left) {
				vecL[k].num = i;
			}
			else {
				vecR[k].num = i;
			}
			bool b = dfs(is_left, k + 1, n);
			if (b) {
				return true;
			}
		}
		return false;
	}
}
bool work(int n) {
	return dfs(true, 0, n);
}
int main() {
	while (true) {
		vecL.clear();
		vecR.clear();
		char c;
		bool is_left = true;
		while ((c = cin.peek()) != '\n') {
			if (c == '-') {
				cin.get();
				is_left = false;
			}
			else if (isalpha(c)) {
				Molecule mol = getMolecule();
				if (is_left) {
					vecL.push_back(mol);
				}
				else {
					vecR.push_back(mol);
				}
			}
			else {
				cin.get();
			}
		}
		cin.get();
		for (int i = 1;; i++) {
			if (work(i)) {
				print();
				break;
			}
		}
	}
	return 0;
}