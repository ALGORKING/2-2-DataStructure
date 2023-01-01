#include <iostream>
#include <deque>
#include <iterator>
using namespace std;
int main(void) {
	deque<int> p = { 1,2,3,4,5 };
	p.push_front(0);
	p.push_back(6);
	p.insert(p.begin() + 2, 10);
	p.pop_back();
	p.pop_front();
	p.erase(p.begin() + 1);
	p.erase(p.begin() + 3, p.end());
	int k = p.size();
	for (int i = 0; i < k; i++) {
		cout << p[i] << " ";
	}
	cout << endl;
	deque<int>::iterator iter = p.begin();
	for (; iter != p.end(); iter++) {
		cout << *(iter) << endl;
	}
    iter = p.begin();
	iter += 2;
	cout << *(iter) << endl;
}