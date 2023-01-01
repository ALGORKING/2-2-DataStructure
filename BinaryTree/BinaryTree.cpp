#include <iostream>
#include <queue>
#include <stack>
using namespace std;
template <typename T>
class Tree;
template <typename T>
class TreeNode {
private:
	TreeNode<T>* leftChild;
	TreeNode<T>* rightChild;
	T data;
public:
	TreeNode(T d, TreeNode<T>* left = NULL, TreeNode<T>* right = NULL) :data(d), leftChild(left), rightChild(right) {

	}
	friend class Tree<T>;
};
template <typename T>
class Tree {
private:
	TreeNode<T>* root;
	void Visit(TreeNode<T>*);
	void Insert(TreeNode<T>*&, T&);
	void Delete(TreeNode<T>*&, T&);
	void Preorder(TreeNode<T>*);
	void Inorder(TreeNode<T>*);
	void Postorder(TreeNode<T>*);
	int getCount(TreeNode<T>*);
	int getLeafCount(TreeNode<T>*);
	int getHeight(TreeNode<T>*);
	bool isFull(TreeNode<T>*);
	int level(TreeNode<T>*, TreeNode<T>*, int lev = 1);
public:
	Tree() { root = NULL; }
	void Insert(T& value) { Insert(root, value); }
	void Delete(T& dvalue) { Delete(root, dvalue); }
	void Preorder() { Preorder(root); }
	void NonRecurPreorder();
	void Inorder() { Inorder(root); }
	void NonRecurInorder();
	void Postorder() { Postorder(root); }
	void Levelorder();
	int getCount() { return root == NULL ? 0 : getCount(root); }
	int getLeafCount() { return root == NULL ? 0 : getLeafCount(root); }
	int getHeight() { return root == NULL ? 0 : getHeight(root); }
	bool isFull() { return root == NULL ? false : isFull(root); }
	int level(TreeNode<T>* node) {
		return level(root, node);
	}
	TreeNode<T>* Find(T);
};
template <typename T>
void Tree<T>::Visit(TreeNode<T>* ptr) { cout << ptr->data << " "; }
template <typename T>
void Tree<T>::Insert(TreeNode<T>*& ptr, T& value) {
	if (ptr == NULL) { ptr = new TreeNode<T>(value); }
	else if (value < ptr->data) { Insert(ptr->leftChild, value); }
	else if (value > ptr->data) { Insert(ptr->rightChild, value); }
	else { cout << endl << "Duplicate value: " << value << "ignored\n"; }
}
template <typename T>
void Tree<T>::Delete(TreeNode<T>*& ptr, T& dvalue) {
	if (ptr == NULL) { return; }
	if (dvalue < ptr->data) { Delete(ptr->leftChild, dvalue); }
	else if (dvalue > ptr->data) { Delete(ptr->rightChild, dvalue); }
	else {
		TreeNode<T>* tmpptr; TreeNode<T>* tmpparentptr;
		if (!ptr->leftChild && !ptr->rightChild) {
			delete ptr;
			ptr = NULL;
			return;
		}
		else if (ptr->leftChild && !ptr->rightChild) {
			tmpptr = ptr;
			ptr = ptr->leftChild;
			delete tmpptr;
			return;
		}
		else if (!ptr->leftChild && ptr->rightChild) {
			tmpptr = ptr;
			ptr = ptr->rightChild;
			delete tmpptr;
			return;
		}
		else {
			TreeNode<T>* rc = ptr->rightChild;
			if (!rc->leftChild) {
				ptr->data = rc->data;
				ptr->rightChild = rc->rightChild;
				delete rc;
			}
			else {
				tmpparentptr = ptr;
				while (rc->leftChild) {
					tmpparentptr = rc;
					rc = rc->leftChild;
				}
				ptr->data = rc->data;
				tmpparentptr->leftChild = rc->rightChild;
				delete rc;
			}
			return;
		}
	}
}
template <typename T>
void Tree<T>::Preorder(TreeNode<T>* currentNode) {
	if (currentNode) {
		Visit(currentNode);
		Preorder(currentNode->leftChild);
		Preorder(currentNode->rightChild);
	}
}
template <typename T>
void Tree<T>::NonRecurPreorder() {
	stack<TreeNode<T>*> s;
	TreeNode<T>* currentNode = root;
	while (1) {
		while (currentNode) {
			Visit(currentNode);
			s.push(currentNode);
			currentNode = currentNode->leftChild;
		}
		if (s.empty()) { return; }
		currentNode = s.top(); s.pop();
		currentNode = currentNode->rightChild;
	}
}
template <typename T>
void Tree<T>::Inorder(TreeNode<T>* currentNode) {
	if (currentNode) {
		Inorder(currentNode->leftChild);
		Visit(currentNode);
		Inorder(currentNode->rightChild);
	}
}
template <typename T>
void Tree<T>::NonRecurInorder() {
	stack<TreeNode<T>*> s;
	TreeNode<T>* currentNode = root;
	while (1) {
		while (currentNode) {
			s.push(currentNode);
			currentNode = currentNode->leftChild;
		}
		if (s.empty()) { return; }
		currentNode = s.top(); Visit(currentNode); s.pop();
		currentNode = currentNode->rightChild;
	}
}
template <typename T>
void Tree<T>::Postorder(TreeNode<T>* currentNode) {
	if (currentNode) {
		Postorder(currentNode->leftChild);
		Postorder(currentNode->rightChild);
		Visit(currentNode);
	}
}
template <typename T>
void Tree<T>::Levelorder() {
	TreeNode<T>* currentNode = root;
	queue<TreeNode<T>*> q;
	while (currentNode) {
		Visit(currentNode);
		if (currentNode->leftChild) { q.push(currentNode->leftChild); }
		if (currentNode->rightChild) { q.push(currentNode->rightChild); }
		if (q.empty()) { return; }
		currentNode = q.front(); q.pop();
	}
}
template<typename T>
int Tree<T>::getCount(TreeNode<T>* currentNode) {
	if (!currentNode) { return 0; }
	else {
		return 1 + getCount(currentNode->leftChild) + getCount(currentNode->rightChild);
	}
}
template <typename T>
int Tree<T>::getLeafCount(TreeNode<T>* currentNode) {
	if (!currentNode) { return 0; }
	if (!currentNode->leftChild && !currentNode->rightChild) {
		return 1;
	}
	else {
		return getLeafCount(currentNode->leftChild) + getLeafCount(currentNode->rightChild);
	}
}
template <typename T>
int Tree<T>::getHeight(TreeNode<T>* currentNode) {
	if (currentNode == NULL) { return 0; }
	else {
		return getHeight(currentNode->leftChild) > getHeight(currentNode->rightChild) ? 1+getHeight(currentNode->leftChild) :1+ getHeight(currentNode->rightChild);
	}
}
template<typename T>
bool Tree<T>::isFull(TreeNode<T>* currentNode) {
	queue<TreeNode<T>*> q;
	q.push(currentNode);
	TreeNode<T>* tmp;
	bool flag = false;
	while (!q.empty()) {
		tmp = q.front();
		q.pop();
		if (flag && (tmp->leftChild || tmp->rightChild)) {
			return false;
		}
		if (tmp->leftChild == NULL && tmp->rightChild) {
			return false;
		}
		if (tmp->leftChild) {
			q.push(tmp->leftChild);
		}
		else {
			flag = true;
		}
		if (tmp->rightChild) {
			q.push(tmp->rightChild);
		}
		else {
			flag = true;
		}
	}
	return true;
}
template <typename T>
int Tree<T>::level(TreeNode<T>* node1, TreeNode<T>* node2, int lev) {
	if (node1 == NULL) { return 0; }
	if (node1 == node2) { return lev; }
	if (node1->leftChild == NULL && node1->rightChild == NULL) { return 0; }
	int left = level(node1->leftChild, node2, lev + 1);
	int right = level(node1->rightChild, node2, lev + 1);
	if (!left) {
		return right;
	}
	else {
		return left;
	}
}
template <typename T>
TreeNode<T>* Tree<T>::Find(T k) {
	TreeNode<T>* tmp = root;
	while (tmp) {
		if (tmp->data < k) { tmp = tmp->rightChild; }
		else if (tmp->data > k) { tmp = tmp->leftChild; }
		else {
			return tmp;
		}
	}
	return NULL;
}
int main(void) {
	Tree<double> tree;
	double dval;
	double a = 81.5;
	double b = 94.5;
	double c = 2.3;
	double d = 5.2;
	double e = 16.7;
	cout << "Enter doubles\n";
	while (cin >> dval) {
		tree.Insert(dval);
	}
	cout << endl << "Preorder traversal:"; tree.Preorder();
	cout << endl << "NonRecur Preorder traversal: "; tree.NonRecurPreorder();
	cout << endl << "Inorder traversal: "; tree.Inorder();
	cout << endl << "NonRecur Inorder traversal: "; tree.NonRecurInorder();
	cout << endl << "Postorder traversal: "; tree.Postorder();
	cout << endl << "Levelorder traversal: "; tree.Levelorder();
	cout <<endl<< "노드의 개수:" << tree.getCount() << endl;
	cout << "단말 노드의 개수:" << tree.getLeafCount() << endl;
	cout << "트리의 높이:" << tree.getHeight() << endl;
	cout << "완전 이진 트리인가:" << tree.isFull() << endl;
	cout << "특정 노드의 레벨:" << tree.level(tree.Find(66.7)) << endl;
	cout << "특정 노드의 레벨:" << tree.level(tree.Find(88.2)) << endl;
	tree.Delete(a);
	cout << endl << "Levelorder traversal: "; tree.Levelorder();
	cout << endl << "노드의 개수:" << tree.getCount() << endl;
	cout << "단말 노드의 개수:" << tree.getLeafCount() << endl;
	cout << "트리의 높이:" << tree.getHeight() << endl;
	cout << "완전 이진 트리인가:" << tree.isFull() << endl;
	tree.Delete(b);
	tree.Delete(c);
	tree.Delete(d);
	tree.Insert(e);
	cout << endl << "Levelorder traversal: "; tree.Levelorder();
	cout << endl << "노드의 개수:" << tree.getCount() << endl;
	cout << "단말 노드의 개수:" << tree.getLeafCount() << endl;
	cout << "트리의 높이:" << tree.getHeight() << endl;
	cout << "완전 이진 트리인가:" << tree.isFull() << endl;
}

