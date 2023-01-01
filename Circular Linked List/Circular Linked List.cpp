#include <iostream>
#include <forward_list>
using namespace std;
template <typename T>
class TList;
template <typename T>
class Node {
private:
	T data;
	Node* link;
public:
	friend class TList<T>;
	Node(T d, Node* l = NULL) :data(d), link(l) {}
	template<typename T>
	friend ostream& operator<<(ostream&, TList<T>&);
};
template <typename T>
class TList {
private:
	Node<T>* last;
public:
	template <typename T>
	friend ostream& operator<<(ostream&, TList<T>&);
	TList() { last= NULL; }
	~TList() {
		Node<T>* p = last->link;
		while (true) {
			Node<T>* tmp = p;
			p = p->link;
			delete tmp;
			if (p == last) {
				delete p;
				break;
			}
		}
	}
	void InsertBack(T e) {
		if (!last) {
			last = new Node<T>(e);
			last->link = last;
		}
		else {
			last->link = new Node<T>(e,last->link);
			last = last->link;
		}
	}
	void InsertFront(T e) {
		if (!last) {
			last = new Node<T>(e);
			last->link = last;
		}
		else {
			last->link = new Node<T>(e, last->link);
		}
	}
	void Delete(T k) {
		Node<T>* cur = last->link;
		Node<T>* prev = last;
		do {
			if (cur->data == k) {
				if (cur == last) {
					if (last->link == last) {
						delete cur;
						last = NULL;
					}
					else {
						prev->link = last->link;
						delete cur;
						last = prev;
					}
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
		} while (cur != last->link);
	}
	Node<T>* Find(T e) {
		Node<T>* cur = last->link;
		Node<T>* x = NULL;
		do {
			if (cur->data == e) {
				x = cur;
				break;
			}
			else {
				cur = cur->link;
			}
		} while (cur != last->link);
		return x;
	}
	void autoSortInsert(T e) {
		if (!last) {
			last = new Node<T>(e);
			last->link = last;
		}
		else if (e < (last->link->data)) {
			last->link = new Node<T>(e, last->link);
		}
		else if (e > (last->data)) {
			last = last->link = new Node<T>(e,last->link);
		}
		else {
			Node<T>* cur = last->link;
			Node<T>* prev = last->link;
			do {
				if (cur->data > e) {
					prev->link = new Node<T>(e, cur);
					break;
				}
				else if (cur->data == e) {
					break;
				}
				else {
					prev = cur;
					cur = cur->link;
				}
			} while (cur != last->link);
		}
	}
	void autoSortDelete(T e) {
		Node<T>* cur = last->link;
		Node<T>* prev = last;
		do{
			if ((cur->data) > e) {
				cout << "no item to delete";
				break;
			}
			else if ((cur->data) < e) {
				prev = cur;
				cur = cur->link;
			}
			else {
				if (last == cur) {
					if (last->link == last) {
						delete cur;
						last = NULL;
					}
					else {
						prev->link = last->link;
						last = prev;
						delete cur;
					}
				}
				else {
					prev->link = cur->link;
					delete cur;
				}
				break;
			}
			
		
		} while (cur != last->link);
	}
};
template<typename T>
ostream& operator<<(ostream& os, TList<T>& il) {
	Node<T>* ptr = il.last;
	if (il.last) {
		ptr = ptr->link;
		do {
			os << ptr->data << " ";
			ptr = ptr->link;
		} while (ptr != il.last->link);
	}
	os << endl;
	return os;
}
int main(void) {
	TList<int> il;
	il.InsertBack(5); il.InsertBack(7); il.InsertBack(9);
	cout << il;
	il.InsertFront(4); il.InsertFront(3);
	cout << il;
	il.autoSortInsert(6); il.autoSortInsert(10); il.autoSortInsert(2);
	il.autoSortInsert(5); il.autoSortInsert(2); il.autoSortInsert(10);
	cout << il;
	il.autoSortDelete(2);
	il.autoSortDelete(6);
	il.autoSortDelete(10);
	cout << il;
	TList<int> il2;
	il2.InsertBack(3); il2.InsertBack(10); il2.InsertBack(7);
	il2.InsertBack(1); il2.InsertBack(15); il2.InsertBack(4);
	cout << il2;
	if (il2.Find(7)) {
		cout << "7이 존재합니다" << endl;
	}
	else {
		cout << "7이 존재하지 않습니다" << endl;
	}
	il2.Delete(7);
	cout << il2;
	if (il2.Find(7)) {
		cout << "7이 존재합니다" << endl;
	}
	else {
		cout << "7이 존재하지 않습니다" << endl;
	}
}