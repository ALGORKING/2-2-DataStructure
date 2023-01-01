#include <iostream>
#include <stack>
#include <iterator>
using namespace std;
template <typename T>
void ChangeSize1D(T*& arr, const int size, const int newsize) {
	if (newsize < 0) { cout << "New length must be >0"; exit(1); }
	T* tmp = new T[newsize];
	int minimum = (newsize > size) ? size : newsize;
	for (int i = 0; i < minimum; i++) {
		tmp[i] = arr[i];
	}
	delete[]arr;
	arr = tmp;
}
template <typename T>
class Stack {
private:
	int top;
	int capacity;
	T* arr;
public:
	Stack(int c = 1) :capacity(1) {
		if (capacity < 1) { cout << "capacity must be >0"; exit(1); }
		top = -1;
		arr = new T[capacity];
	}
	~Stack() {
		for (int i = top; i >= 0; i--) {
			arr[i].~T();
		}
	}
	bool isempty() {
		return top == -1;
	}
	T Top() {
		if (isempty()) {
			cout << "Top must be not empty"; exit(1);
		}
		return arr[top];
	}
	void Push(const T& e) {
		if (top + 1 == capacity) {
			ChangeSize1D(arr, capacity, 2 * capacity);
			capacity *= 2;
		}
		arr[++top] = e;
	}
	void Pop() {
		if (isempty()) { cout << "pop must not empty"; exit(1); }
		arr[top--].~T();
	}
	void printalljust() {
		for (int i = top; i>=0; i--) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	void printallwithpop() {
		while (!isempty()) {
			cout << arr[top] << " ";
			Pop();
		}
		cout << endl;
	}
	template <typename T>
	friend ostream& operator<<(ostream&, Stack<T>&);
};
template <typename T>
ostream& operator<<(ostream& os, Stack<T>& c) {
	while (!c.isempty()) {
		os << c.arr[c.top] << " ";
		c.Pop();
	}
	return os;
}
class LinkedStack;
class Node {
private:
	int data;
	Node* link;
public:
	Node(int d=0,Node* p=NULL):data(d),link(p){}
	~Node(){}
	friend class LinkedStack;
	friend ostream& operator<<(ostream&, Node&);
};
ostream& operator<<(ostream& os, Node& c) {
	os << c.data;
	return os;
}
class LinkedStack {
private:
	Node* top;
public:
	LinkedStack() { top = NULL; }
	~LinkedStack() {

	}
	bool isempty() {
		return top == NULL;
	}
	void push(int e) {
		if (isempty()) {
			top = new Node(e);
		}
		else {
			top = new Node(e, top);
		}
	}
	Node* Top() {
		if (isempty()) { cout << "must be not empty"; exit(1); }
		else {
			return top;
		}
	}
	void printalljust() {
		Node* tmp = top;
		while (tmp) {
			cout << tmp->data << " ";
			tmp = tmp->link;
		}
		cout << endl;
	}
	void pop() {
		Node* tmp =top;
		top = top->link;
		delete tmp;
	}
	friend ostream& operator<<(ostream&, LinkedStack&);
};
ostream& operator<<(ostream& os, LinkedStack& c) {
	while (!c.isempty()) {
		os << *(c.Top()) << " ";
		c.pop();
	}
	return os;
}
int main(void) {
	Stack<int> s;
	s.Push(3);
	s.Push(7);
	s.Push(1);
	s.printalljust();
	s.Pop();
	cout << s << endl;
	LinkedStack p;
	p.push(3);
	p.push(7);
	p.push(1);
	p.printalljust();
	p.pop();
	cout << p<<endl;
	stack<int> t;
	t.push(3);
	t.push(7);
	t.push(1);
	int k = t.size();
	for (int i = 0; i <k; i++) {
		cout << t.top()<<endl;
		t.pop();
	}
	
}