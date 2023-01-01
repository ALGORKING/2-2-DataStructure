#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
int main(void) {
	vector<pair<int, int>> a;
	a.push_back({ 5,3 });
	cout << a[0].first << endl;
	cout << a[0].second << endl;
	stack<pair<double, int>> c;
	c.push({ 3.5, 5 });
	cout << c.top().first << endl;
	cout << c.top().second << endl;

}