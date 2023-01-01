#include <iostream>
using namespace std;
class Sets {
private:
	int* parent;
	int n;
public:
	Sets(int numberofElements);
	void SimpleUnion(int i, int j);
	int SimpleFind(int i);
	void WeightedUnion(int i, int j);
	int CollapsingFind(int i);
	friend ostream& operator<<(ostream&, Sets&);
};
Sets::Sets(int numberofElements) {
	if (numberofElements < 2) { cout << "Must have at least 2 elements"; exit(1); }
	n = numberofElements;
	parent = new int[n];
	fill(parent, parent + n, -1);
}
ostream& operator<<(ostream& os, Sets& s) {
	for (int i = 0; i < s.n; i++) {
		os << i << ':' << s.parent[i] << " ";
	}
	os << endl;
	return os;
}
void Sets::SimpleUnion(int i, int j) {
	parent[i] = j;
}
int Sets::SimpleFind(int i) {
	while (parent[i] >= 0) {
		i = parent[i];
	}
	return i;
}
void Sets::WeightedUnion(int i, int j) {
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j]) {
		parent[i] = j;
		parent[j] = temp;
	}
	else {
		parent[j] = i;
		parent[i] = temp;
	}
}
int Sets::CollapsingFind(int i) {
	int r;
	for (r = i; parent[r] >= 0; r = parent[r]);
	while (i != r) {
		int s = parent[i];
		parent[i] = r;
		i = s;
	}
	return r;
}
int main(void) {
	Sets a(8), b(8);
	cout << "SimpleUnion example of set a" << endl;
	cout << a << endl;
	a.SimpleUnion(0, 1);
	a.SimpleUnion(1, 2);
	a.SimpleUnion(2, 3);
	a.SimpleUnion(3, 4);
	a.SimpleUnion(4, 5);
	a.SimpleUnion(5, 6);
	a.SimpleUnion(6, 7);
	cout << a << endl;
	cout << "WeightedUnion Example of set b" << endl;
	cout << b << endl;
	b.WeightedUnion(0, 1);
	b.WeightedUnion(2, 3);
	b.WeightedUnion(4, 5);
	b.WeightedUnion(6, 7);
	cout << b << endl;
	b.WeightedUnion(0, 2);
	b.WeightedUnion(4, 6);
	cout << b << endl;
	b.WeightedUnion(0, 4);
	cout << b << endl << endl;
	b.CollapsingFind(7);
	cout << b << endl << endl;



}
