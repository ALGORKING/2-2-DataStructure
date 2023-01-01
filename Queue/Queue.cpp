#include <iostream>
#include <queue>
using namespace std;
class Queue {
private:
	int front;
	int rear;
	int* queue;
	int capacity;
public:
	Queue(int c) :capacity(c) {
		if (c < 1) { cout << "Capacity must be >0"; }
		queue = new int[capacity];
		rear = front = 0;
	}
	~Queue() {
		delete[]queue;
	}
	bool isempty() {
		return rear == front;
	}
	bool isfull() {
		return front == (rear + 1) % capacity;
	}
	void Push(int k) {
		if (isfull()) {
			int* newQueue = new int[2 * capacity];
			int start = (front + 1) % capacity;
			if (start < 2) {
				copy(queue + start, queue + start + capacity - 1, newQueue);
				//queue+start+capacity-1을 queue+rear+1로 바꾸어도 된다.
			}
			else {
				copy(queue + start, queue + capacity, newQueue);
				copy(queue, queue + rear + 1, newQueue+capacity - start);
			}
			front = 2 * capacity - 1;
			rear = capacity - 2;
			capacity *= 2;
			delete[]queue;
			queue = newQueue;
		}
		rear = (rear + 1) % capacity;
		queue[rear] = k;
		cout << "front:" << front << endl;
		cout << "rear: " << rear << endl;
	}
	void Pop() {
		if (isempty()) { cout << "pop must be not empty"; exit(1); }
		front = (front + 1) % capacity;
		cout << "front:" << front << endl;
		cout << "rear: " << rear << endl;
	}
	int Front() {
		if (isempty()) { cout << "Queue is empty. No front elment"; exit(1); }
		return queue[(front + 1) % capacity];
	}
	int Rear() {
		if (isempty()) { cout << "Queue is empty. No rear element"; exit(1); }
		return queue[rear];
	}
	void showQueue() {
		int maxi = (front < rear)? rear:rear + capacity;
		for (int i = (front + 1); i <= maxi; i++) {
			cout << queue[i % capacity] << " ";
		}
		cout << endl;
	}
};
class LinkedQueue;
class Node {
private:
	int data;
	Node* link;
public:
	Node(int d=0,Node* l=NULL):data(d),link(l){}
	~Node(){}
	friend ostream& operator<<(ostream&, Node&);
	friend class LinkedQueue;
};
ostream& operator<<(ostream& os, Node& c) {
	os << c.data << " ";
	return os;
}
class LinkedQueue {
private:
	Node* front;
	Node* rear;
public:
	LinkedQueue() {
		front = NULL;
		rear = NULL;
	}
	~LinkedQueue(){}
	bool isempty() {
		return front == NULL;
	}
	void Push(int e) {
		if (isempty()) {
			front = rear = new Node(e);
		}
		else {
			rear = rear->link = new Node(e, NULL);
		}
	}
	void Pop() {
		if (isempty()) { cout << "must be not empty"; exit(1); }
		Node* tmp = front;
		front = front->link;
		delete tmp;
	}
	Node* Front() {
		return front;
	}
	Node* Rear() {
		return rear;
	}
	void showQueue() {
		for (Node* p = front; p != NULL; p = p->link) {
			cout << p->data << " ";
		}
	}
	friend ostream& operator<<(ostream&, LinkedQueue&);
};
ostream& operator<<(ostream& os, LinkedQueue& c) {
	Node* tmp = c.front;
	while (!c.isempty()) {
		cout << *(c.front);
		c.Pop();
	}
	return os;
}
int main(void) {
	Queue que(1);
	que.Push(1);
	que.Push(7);
	que.Push(3);
	que.Push(8);
	que.showQueue();
	que.Pop();
	que.showQueue();
	LinkedQueue que2;
	que2.Push(1);
	que2.Push(7);
	que2.Push(3);
	que2.Push(8);
	que2.showQueue();
	cout << endl;
	que2.Pop();
	cout << que2<<endl;
	queue<int> que3;
	que3.push(1);
	que3.push(7);
	que3.push(3);
	que3.push(8);
	int k = que3.size();
	for (int i = 0; i < k; i++) {
		cout << que3.front() << endl;
		que3.pop();
	}


}