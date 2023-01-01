#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
template <typename T>
class PQ {
public:
	virtual ~PQ(){}
	virtual bool isEmpty() const = 0;
	virtual const T& Top() const = 0;
	virtual void Push(const T&) = 0;
	virtual void Pop() = 0;
};
template <typename T>
class Maxheap :public PQ<T> {
private:
	void ChangeSize1D(T*&, int, int);
	T* heap;
	int heapSize;
	int capacity;
public:
	Maxheap(int);
	Maxheap();
	~Maxheap();
	void Push(const T& e);
	void Pop();
	bool isEmpty() const { return heapSize == 0; }
	const T& Top() const { return heap[1]; }
	template <typename T>
	friend ostream& operator<<(ostream&, Maxheap<T>&);
};
template<typename T>
ostream& operator<<(ostream& os, Maxheap<T>& H) {
	os << "<Heap Contents>";
	for (int i = 1; i <= H.heapSize; i++) {
		os << i << ':' << H.heap[i] << " ";
	}
	os << endl;
	return os;
}
template <typename T>
Maxheap<T>::~Maxheap() {
	if (heapSize) {
		delete[]heap;
	}
}
template<typename T>
void Maxheap<T>::ChangeSize1D(T*& a, int oldsize, int newsize) {
	if (newsize < 0) { cout << "New length must be >=0"; }
	int* temp = new int[newsize+1];
	int number = min(oldsize, newsize);
	copy(a, a + number+1, temp);
	delete[]a;
	a = temp;
}
template <typename T>
Maxheap<T>::Maxheap(int theCapacity) {
	if (theCapacity < 1) { cout << "Capacity must be >=1"; }
	capacity = theCapacity;
	heap = new T[capacity + 1];
	heapSize = 0;
}
template <typename T>
Maxheap<T>::Maxheap() {
	heapSize = 0;
	capacity = 10;
	heap = new T[capacity + 1];
}
template <typename T>
void Maxheap<T>::Push(const T& e) {
	if (heapSize == capacity) {
		ChangeSize1D(heap, capacity, 2 * capacity);
		capacity *= 2;
	}
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < e) {
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = e;
}
template <typename T>
void Maxheap<T>::Pop() {
	if (isEmpty()) { cout << "heap is empty.Cannot delete"; exit(1); }
	heap[1].~T();
	T lastE = heap[heapSize--];
	int currentNode = 1;
	int child = 2;
	while (child <= heapSize) {
		if (child < heapSize && heap[child] < heap[child + 1]) { child++; }
		if (lastE >= heap[child]) { break; }
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastE;
}
template <typename T>
class Minheap :public PQ<T> {
private:
	void ChangeSize1D(T*&, int, int);
	T* heap;
	int heapSize;
	int capacity;
public:
	Minheap(int);
	Minheap();
	~Minheap();
	void Push(const T& e);
	void Pop();
	bool isEmpty() const { return heapSize == 0; }
	const T& Top() const { return heap[1]; }
	template <typename T>
	friend ostream& operator<<(ostream&, Minheap<T>&);
};
template<typename T>
ostream& operator<<(ostream& os, Minheap<T>& H) {
	os << "<Heap Contents>";
	for (int i = 1; i <= H.heapSize; i++) {
		os << i << ':' << H.heap[i] << " ";
	}
	os << endl;
	return os;
}
template <typename T>
Minheap<T>::~Minheap() {
	if (heapSize) {
		delete[]heap;
	}
}
template<typename T>
void Minheap<T>::ChangeSize1D(T*& a, int oldsize, int newsize) {
	if (newsize < 0) { cout << "New length must be >=0"; }
	int* temp = new int[newsize+1];
	int number = min(oldsize, newsize);
	copy(a, a + number + 1, temp);
	delete[]a;
	a = temp;
}
template <typename T>
Minheap<T>::Minheap(int theCapacity) {
	if (theCapacity < 1) { cout << "Capacity must be >=1"; }
	capacity = theCapacity;
	heap = new T[capacity + 1];
	heapSize = 0;
}
template <typename T>
Minheap<T>::Minheap() {
	heapSize = 0;
	capacity = 10;
	heap = new T[capacity + 1];
}
template <typename T>
void Minheap<T>::Push(const T& e) {
	if (heapSize == capacity) {
		ChangeSize1D(heap, capacity, 2 * capacity);
		capacity *= 2;
	}
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] > e) {
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = e;
}
template <typename T>
void Minheap<T>::Pop() {
	if (isEmpty()) { cout << "heap is empty.Cannot delete"; exit(1); }
	heap[1].~T();
	T lastE = heap[heapSize--];
	int currentNode = 1;
	int child = 2;
	while (child <= heapSize) {
		if (child < heapSize && heap[child] > heap[child + 1]) { child++; }
		if (lastE <= heap[child]) { break; }
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastE;
}
int main(void) {
	Maxheap<int> H(3);
	H.Push(15);
	H.Push(14);
	H.Push(21);
	H.Push(2);
	H.Push(10);
	H.Push(20);
	H.Push(17);
	H.Push(3);
	H.Push(8);
	cout << H;
	while (!H.isEmpty()) {
		cout << H.Top() << " ";
		H.Pop();
	}
	cout << endl;
	priority_queue<int, vector<int>, less<int>> PQ;
	PQ.push(15);
	PQ.push(14);
	PQ.push(21);
	PQ.push(2);
	PQ.push(10);
	PQ.push(20);
	PQ.push(17);
	PQ.push(3);
	PQ.push(8);
	int k = PQ.size();
	for (int i = 0; i < k; i++) {
		cout << PQ.top() << " ";
		PQ.pop();
	}
	Minheap<int> H2(3);
	H2.Push(15);
	H2.Push(14);
	H2.Push(21);
	H2.Push(2);
	H2.Push(10);
	H2.Push(20);
	H2.Push(17);
	H2.Push(3);
	H2.Push(8);
	cout <<endl<< H2;
	while (!H2.isEmpty()) {
		cout << H2.Top() << " ";
		H2.Pop();
	}
	cout << endl;
	priority_queue<int, vector<int>, greater<int>> PQ2;
	PQ2.push(15);
	PQ2.push(14);
	PQ2.push(21);
	PQ2.push(2);
	PQ2.push(10);
	PQ2.push(20);
	PQ2.push(17);
	PQ2.push(3);
	PQ2.push(8);
	int p = PQ2.size();
	for (int i = 0; i < p; i++) {
		cout << PQ2.top() << " ";
		PQ2.pop();
	}
}

