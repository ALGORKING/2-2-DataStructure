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
	Node(T d,Node* l=NULL):data(d),link(l){}
	template<typename T>
	friend ostream& operator<<(ostream&, TList<T>&);
};
template <typename T>
class TList {
private:
	Node<T>* first;
	Node<T>* last;
public:
	template <typename T>
	friend ostream& operator<<(ostream&, TList<T>&);
	TList() { last = first = NULL; }
	~TList() {
		Node<T>* p = first;
		while (p != NULL) {
			Node<T>* k = p;
			p = p->link;
			delete k;
		}
	}
	void InsertBack(T e) {
		if (!first) {
			first = last = new Node<T>(e);
		}
		else {
			last->link = new Node<T>(e);
			last = last->link;
		}
	}
	void InsertFront(T e) {
		if (!first) {
			first = last = new Node<T>(e);
		}
		else {
			first = new Node<T>(e, first);
		}
	}
	void Delete(T k) {
		Node<T>* cur = first;
		Node<T>* prev = first;
		while (cur) {
			if (cur->data == k) {
				if (cur == first) {
					Node<T>* p = first;
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
	Node<T>* Find(T e) {
		Node<T>* cur = first;
		Node<T>* x = NULL;
		while (cur) {
			if (cur->data == e) {
				x = cur;
				break;
			}
			else {
				cur = cur->link;
			}
		}
		return x;
	}
	void autoSortInsert(T e) {
		if (!first) {
			first = last = new Node<T>(e);
		}
		else if (e < (first->data)) {
			first = new Node<T>(e, first);
		}
		else if (e > (last->data)) {
			last = last->link = new Node<T>(e);
		}
		else {
			Node<T>* cur = first;
			Node<T>* prev = first;
			while (cur) {
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
			}
		}
	}
	void autoSortDelete(T e) {
		Node<T>* cur = first;
		Node<T>* prev = first;
		while (cur) {
			if ((cur->data) > e) {
				cout << "no item to delete";
			}
			else if ((cur->data) < e) {
				prev = cur;
				cur = cur->link;
			}
			else {
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
};
template<typename T>
ostream& operator<<(ostream& os, TList<T>& il) {
	Node<T>* ptr = il.first;
	while (ptr != 0) {
		os << ptr->data << " ";
		ptr = ptr->link;
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
	forward_list<int> fl = { 1,2,3 };
	fl.push_front(0);//맨 앞에 0추가
	forward_list<int>::iterator iter = fl.begin();
	for (; iter != fl.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
	iter = fl.begin();
	fl.insert_after(iter, 5);//맨 처음 원소 뒤에 5 추가
	for (; iter != fl.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
	iter = fl.begin();
	fl.insert_after(iter, 6);//같은 위치에 6추가
	for (; iter != fl.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
	fl.emplace_front(7);
	iter = fl.begin();
	for (; iter != fl.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
	iter = fl.begin();
	//iter += 2;->안된다 벡터 반복자는 된다.
	advance(iter, 2);
	fl.emplace_after(iter,100);
	iter = fl.begin();
	for (; iter != fl.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
	iter = fl.begin();
	fl.remove(100);
	iter = fl.begin();
	for (; iter != fl.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
	fl.remove_if([](int a) {
		return a < 5;
		});
	iter = fl.begin();
	for (; iter != fl.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
	fl.sort();
	iter = fl.begin();
	for (; iter != fl.end(); iter++) {
		cout << *iter << " ";
	}
	fl.sort(greater<int>());
	cout << endl;
	iter = fl.begin();
	for (; iter != fl.end(); iter++) {
		cout << *iter << " ";
	}
	fl.reverse();
	cout << endl;
	iter = fl.begin();
	for (; iter != fl.end(); iter++) {
		cout << *iter << " ";
	}




	




	
}