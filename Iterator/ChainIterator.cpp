
#include <iostream>
#include <vector>
#include <iterator>
#include <list>
using namespace std;
class IntList;
class Node {
private:
	int data;
	Node* link;
public:
	friend class IntList;
	Node(int d = 0, Node* l = NULL) :data(d), link(l) {}
	friend ostream& operator<<(ostream&, IntList&);

};
class IntList {
private:
	Node* first;
	Node* last;
public:
	IntList() { last = first = NULL; }
	friend ostream& operator<<(ostream&, IntList&);
	class ChainIterator {
	private:
		Node* current;
	public:
		ChainIterator(Node* startNode = 0) { current = startNode; }
		int& operator*() const { return current->data; }
		int* operator->() const { return &current->data; }
		ChainIterator& operator++() {
			current = current->link;
			return *this;
		}
		ChainIterator operator++(int) {
			ChainIterator old = *this;
			current = current->link;
			return old;
		}
		bool operator!=(const ChainIterator right) const {
			return current != right.current;
		}
		bool operator==(const ChainIterator right) const {
			return current == right.current;
		}
	};
	void InsertBack(int);
	void InsertFront(int);
	void Insert(int);
	void Delete(int);
	void NormalDelete(int);
	Node* Find(int);
	void Concatenate(IntList&);
	void Reverse();
};
ostream& operator<<(ostream& os, IntList& il) {
	Node* ptr = il.first;
	while (ptr != 0) {
		os << ptr->data << " ";
		ptr = ptr->link;
	}
	os << endl;
	return os;
}
void IntList::InsertBack(int e) {
	if (!first) {
		first = last = new Node(e);
	}
	else {
		last = last->link = new Node(e);
	}
}

void IntList::InsertFront(int e) {
	if (!first) { first = last = new Node(e); }
	else {
		first = new Node(e, first);
	}
}
void IntList::Insert(int e) {
	if (!first) { first = last = new Node(e); }
	else if (e < (first->data)) { first = new Node(e, first); }
	else if (e > (last->data)) { last = last->link = new Node(e); }
	else {
		Node* cur = first;
		Node* prev = first;
		while (cur) {
			if (cur->data > e) {
				prev->link = new Node(e, cur);
				break;
			}
			else if (cur->data == e) {
				break;
			}
			else {
				prev = cur;
				cur = cur->link;
			}
		}
	}
}
void IntList::Delete(int e) {
	Node* cur = first;
	Node* prev = first;
	while (cur) {
		if (cur->data > e) {
			throw "no item to delete";
		}
		else if (cur->data < e) {
			prev = cur;
			cur = cur->link;
		}
		else if (cur->data == e) {
			if (first == cur) {

				cur = first->link;

				delete first;

				first = cur;

				if (first == NULL) {

					last = NULL;

				}

			}

			else if (last == cur) {

				prev->link = NULL;

				delete last;

				last = prev;

			}

			else {

				prev->link = cur->link;

				delete cur;

			}

			break;

		}

	}

}

void IntList::NormalDelete(int k) {

	Node* cur = first;

	Node* prev = first;

	while (cur) {

		if (cur->data == k) {

			if (first == cur) {

				Node* p = first;

				first = first->link;

				delete p;

				if (first == NULL) {

					last = NULL;

				}

			}

			else if (cur == last) {

				last = prev;

				last->link = NULL;

				delete cur;

			}

			else {

				prev->link = cur->link;

				delete cur;

			}

			break;

		}

		else {

			prev = cur;

			cur = cur->link;

		}

	}

}

Node* IntList::Find(int e) {

	Node* cur = first;

	while (cur) {

		if (cur->data == e) {

			return cur;

		}

		else {

			cur = cur->link;

		}

	}

	return NULL;

}

void IntList::Concatenate(IntList& b) {

	if (!b.first) { return; }

	if (first) { last->link = b.first; last = b.last; }

	else { first = b.first; last = b.last; }

	b.first = b.last = 0;

}

void IntList::Reverse() {

	Node* current = first;

	Node* prev = 0;

	while (current) {

		Node* tmp = prev;

		prev = current;

		current = current->link;

		prev->link = tmp;

	}

	last = first;

	first = prev;

}
int main() {

	IntList il;

	il.InsertBack(5);

	il.InsertBack(7);

	il.InsertBack(9);

	cout << il;

	il.InsertFront(4);

	il.InsertFront(3);

	cout << il;

	il.Insert(6); il.Insert(10); il.Insert(2);

	il.Insert(5); il.Insert(2); il.Insert(10);

	cout << il;

	il.Delete(2);

	il.Delete(6);

	il.Delete(10);

	cout << il;

	IntList il2;

	il2.InsertBack(10);

	il2.InsertBack(5);

	il2.InsertBack(20);

	il2.InsertBack(1);

	cout << il2;

	il2.NormalDelete(5);

	cout << il2;

	il2.NormalDelete(1);

	cout << il2;

	il2.NormalDelete(10);

	cout << il2;
	cout << il;
	cout << "여기가 chainiterator" << endl;
	for (IntList::ChainIterator a=il.Find(3); a != NULL; a++) {
		cout << *a << " ";
	}//ChainIterator 활용의 예
	IntList::ChainIterator b(il.Find(3));
	cout << endl;

	il.Concatenate(il2);

	cout << il;

	il.Reverse();

	cout << il;

	vector<int> a;

	a.push_back(1);

	a.push_back(10);

	a.push_back(3);

	a.push_back(7);

	vector<int>::iterator iter;
	for (iter = a.begin(); iter != a.end(); iter++) {
		cout << *iter << " ";
	}
	iter = a.begin() + 3;//된다
	list<int> c;
	c.push_back(3);
	c.push_back(1);
	c.push_back(7);
	c.push_front(5);
	//c.insert(c.begin() + 2, 100); 이런거 안됨
	list<int>::iterator it = c.begin();
	advance(it, 2);
	c.insert(it, 100);
	cout << endl;
	for (it = c.begin(); it != c.end(); it++) {
		if (*it == 7) {
			*it = 50;
		}
		cout << *it << " ";
	}
}