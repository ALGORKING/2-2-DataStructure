#include <iostream>
#include <list>
using namespace std;
template <typename T>
class DblList;
template <typename T>
class DblListNode {
private:
	T data;
	DblListNode<T>* left,* right;
public:
	friend class DblList<T>;
	DblListNode<T>(T d = 0, DblListNode<T>* l = 0, DblListNode<T>* r = 0) :data(d), left(l), right(r) {}
	template <typename T>
	friend ostream& operator<<(ostream&, DblList<T>&);
};
template <typename T>
class DblList {
private:
	DblListNode<T>* first;
	DblListNode<T>* last;
public:
	template <typename T>
	friend ostream& operator<<(ostream&, DblList<T>&);
	DblList() {
		first = new DblListNode<T>();
		first->right = first;
		first->left = first;
		last = first;
	}
	void IntInsert(T e) {//������ ���� ����
		//��� ����� ���� empty�϶� ���� ó���� �ʿ䰡 ����.
		last = last->right = new DblListNode<T>(e, last, first);
		first->left = last;
	}
	void IntDelete(T e) {//������ ã�Ƽ� ����
		DblListNode<T>* p = first->right;
		while (p != first) {
			if (p->data == e) {
				p->left->right = p->right;
				p->right->left = p->left;
				delete p;
				break;
			}
			else {
				p = p->right;
			}
		}
	}
	DblListNode<T>* Find(T k) {//������ ã�� �� ��ȯ
		DblListNode<T>* p = first->right;
		DblListNode<T>* x = NULL;
		while (p != first) {
			if (p->data == k) {
				x = p;
				break;
			}
			else {
				p = p->right;
			}
		}
		return x;
	}
	void Insert(DblListNode<T>* p, DblListNode<T>* x)/*��� x�� ������ ��� p����*/ {
		p->left = x;
		p->right = x->right;//p���� ó��
		x->right->left = p;
		x->right = p;
	}
	void Delete(DblListNode<T>* x) {//��� ������ x ã�Ƽ� ����
		if (x == first) { throw "Deletion of header node not permitted"; }
		else {
			x->left->right = x->right;
			x->right->left = x->left;
			delete x;
		}
	}
	DblListNode<T>* returnFirst() {//������ ����
		return first;
	}
};
template <typename T>
ostream& operator<<(ostream& os, DblList<T>& dbl) {
	DblListNode<T>* p = dbl.first->right;
	while (p != dbl.first) {
		os << p->data << " ";
		p = p->right;
	}
	os << endl;
	return os;
}
int main(void) {
	DblList<int> dbl;
	dbl.IntInsert(5);
	dbl.IntInsert(7);
	dbl.IntInsert(9);
	cout << dbl;
	dbl.IntDelete(7);
	cout << dbl;
	dbl.IntInsert(22);
	dbl.IntInsert(10);
	cout << dbl;
	dbl.Insert(new DblListNode<int>(3), dbl.Find(22));
	cout << dbl;
	dbl.Insert(new DblListNode<int>(7), dbl.Find(10));
	cout << dbl;
	dbl.Insert(new DblListNode<int>(100), dbl.returnFirst());//ó���� ����
	cout << dbl;
	cout << "-----" << endl;
	dbl.Delete(dbl.Find(9));
	cout << dbl;
	dbl.Delete(dbl.Find(100));
	cout << dbl;
	dbl.Delete(dbl.Find(10));
	cout << dbl;
	dbl.Delete(dbl.Find(7));
	cout << dbl;
	cout << "-----����Ʈ ����------" << endl;
	list<int> li;
	li.push_back(15);
	li.push_back(30);
	li.push_back(7);
	li.push_back(1);
	li.push_front(100);
	li.pop_back();
	li.pop_front();
	cout << li.size() << endl;//������ �Լ��� ��� ����
	list<int>::iterator iter;
	iter = li.begin();
	for (; iter != li.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
	iter = li.begin();
	advance(iter,2);// forward_list �� �޸� ������ ������ �����ϴ� �׷��� ���� ���� �ݺ����� ��� ó�� �ѹ���
	//�̵� �Ұ� ex)iter+=8;
	advance(iter, -1);
	li.insert(iter, 298);
	iter = li.begin();
	for (; iter != li.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
	iter = li.begin();
	advance(iter, 1);
	li.insert(iter, 1000);
	iter = li.begin();
	for (; iter != li.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
	iter = li.begin();
	li.insert(iter, 0);
	iter = li.begin();
	for (; iter != li.end(); iter++) {
		cout << *iter << " ";
	}
	iter = li.begin();
	cout << endl;
	li.erase(iter);
	iter = li.begin();
	for (; iter != li.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
	li.remove(298);
	iter = li.begin();
	for (; iter != li.end(); iter++) {
		cout << *iter << " ";
	}
	li.erase(li.begin(), li.end());
	iter = li.begin();
	for (; iter != li.end(); iter++) {
		cout << *iter << " ";
	}
	
}