#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;
template <class K, class E> class BST;
template <class K, class E>
class TreeNode {
	friend class BST<K, E>;
	TreeNode(K ky, E el, TreeNode<K, E>* left = 0, TreeNode<K, E>* right = 0) :key(ky), element(el), leftChild(left), rightChild(right) {
	}
private:
	TreeNode<K, E>* leftChild;
	K key;
	E element;
	TreeNode <K, E>* rightChild;
};
template <class K, class E>
class BST {
public:
	BST() { root = 0; }
	void Insert(K& newkey, E& el) {
		Insert(root, newkey, el);
	}
	void Preorder() {
		Preorder(root);
	}
	void Inorder() {
		Inorder(root);
	}
	void Postorder() {
		Postorder(root);
	}
	void Levelorder();
	bool Find(const K& k, E& e);
	void Delete(K& oldkey) { Delete(root, oldkey); }
	void NonRecurInorder() { NonRecurInorder(root); }
	void NonRecurPreorder() { NonRecurPreorder(root); }
	void NonRecurPostorder() { NonRecurPostorder(root); }
private:
	void Visit(TreeNode<K, E>*);
	void Insert(TreeNode<K, E>*&, K&, E&);
	void Preorder(TreeNode<K, E>*);
	void Inorder(TreeNode<K, E>*);
	void Postorder(TreeNode<K, E>*);
	void Delete(TreeNode<K, E>*&, K&);
	void NonRecurInorder(TreeNode<K, E>*);
	void NonRecurPreorder(TreeNode<K, E>*);
	void NonRecurPostorder(TreeNode<K, E>*);
	TreeNode<K, E>* root;
};
template <class K, class E>
void BST<K, E>::Visit(TreeNode<K, E>* ptr) {
	cout << ptr->key << ":" << ptr->element << " ";
}
template <class K, class E>
void BST<K, E>::Insert(TreeNode<K, E>*& ptr, K& newkey, E& el) {
	if (ptr == 0) { ptr = new TreeNode<K, E>(newkey, el); }
	else if (newkey < ptr->key) { Insert(ptr->leftChild, newkey, el); }
	else if (newkey > ptr->key) { Insert(ptr->rightChild, newkey, el); }
	else { ptr->element = el; }
}
template <class K, class E>
void BST<K, E>::Preorder(TreeNode<K, E>* currentNode) {
	if (currentNode) {
		Visit(currentNode);
		Preorder(currentNode->leftChild);
		Preorder(currentNode->rightChild);
	}
}
template <class K, class E>
void BST<K, E>::Inorder(TreeNode<K, E>* currentNode) {
	if (currentNode) {
		Inorder(currentNode->leftChild);
		Visit(currentNode);
		Inorder(currentNode->rightChild);
	}
}
template <class K, class E>
void BST<K, E>::Postorder(TreeNode<K, E>* currentNode) {
	if (currentNode) {
		Postorder(currentNode->leftChild);
		Postorder(currentNode->rightChild);
		Visit(currentNode);
	}
}
template <class K, class E>
void BST<K, E>::Levelorder() {
	queue<TreeNode<K, E>*> q;
	TreeNode<K, E>* currentNode = root;
	while (currentNode) {
		Visit(currentNode);
		if (currentNode->leftChild) { q.push(currentNode->leftChild); }
		if (currentNode->rightChild) { q.push(currentNode->rightChild); }
		if (q.empty()) { return; }
		currentNode = q.front();
		q.pop();
	}
}
template <class K, class E>
bool BST<K, E>::Find(const K& k, E& e) {
	TreeNode<K, E>* ptr = root;
	while (ptr) {
		if (ptr->key < k) {
			ptr = ptr->rightChild;
		}
		else if (ptr->key > k) {
			ptr = ptr->leftChild;
		}
		else {
			e = ptr->element; return true;
		}
	}
	return false;
}
template <class K, class E>
void BST<K, E>::Delete(TreeNode<K, E>*& ptr, K& oldkey) {
	TreeNode<K, E>* tmpptr; TreeNode<K, E>* tmpparentptr;
	if (ptr == 0) { return; }
	if (oldkey < ptr->key) { Delete(ptr->leftChild, oldkey); }
	else if (oldkey > ptr->key) { Delete(ptr->rightChild, oldkey); }
	else {
		if (!ptr->leftChild && !ptr->rightChild) {
			delete ptr; ptr = 0; return;
		}
		else if (ptr->leftChild && !ptr->rightChild) {
			tmpptr = ptr; ptr = ptr->leftChild; delete tmpptr; return;
		}
		else if (!ptr->leftChild && ptr->rightChild) {
			tmpptr = ptr; ptr = ptr->rightChild; delete tmpptr; return;
		}
		else {
			TreeNode<K, E>* rc = ptr->rightChild;
			if (!rc->leftChild) {
				ptr->key = rc->key;
				ptr->element = rc->element;
				ptr->rightChild = rc->rightChild;
				delete rc;
			}
			else {
				tmpparentptr = ptr;
				while (rc->leftChild) {
					tmpparentptr = rc;
					rc = rc->leftChild;
				}
				ptr->element = rc->element;
				ptr->key = rc->key;
				tmpparentptr->leftChild = rc->rightChild;
				delete rc;
			}
		}
	}
}
template <class K, class E>
void BST<K, E>::NonRecurInorder(TreeNode<K, E>* currentNode) {
	stack<TreeNode<K, E>*> s;
	while (1) {
		while (currentNode) {
			s.push(currentNode);
			currentNode = currentNode->leftChild;
		}
		if (s.empty()) { return; }
		currentNode = s.top(); s.pop();
		Visit(currentNode);
		currentNode = currentNode->rightChild;
	}
}
template <class K, class E>
void BST<K, E>::NonRecurPreorder(TreeNode<K, E>* currentNode) {
	stack<TreeNode<K, E>*> s;
	while (1) {
		while (currentNode) {
			s.push(currentNode);
			Visit(currentNode);
			currentNode = currentNode->leftChild;
		}
		if (s.empty()) { return; }
		currentNode = s.top(); s.pop();
		currentNode = currentNode->rightChild;
	}
}
template <class K, class E>
void BST<K, E>::NonRecurPostorder(TreeNode<K, E>* currentNode) {
	//변수를 추가해서 이게 지나온건지 아닌건지 확인이 필요하다.
}
int main() {
	BST<string, double> tree;
	string command, str; double dval;
	while (cin >> command) {
		if (command == "insert") {
			cin >> str >> dval; tree.Insert(str, dval);
		}
		else if (command == "delete") {
			cin >> str; tree.Delete(str);
		}
		else if (command == "print") {
			cout << endl << "Inorder traversal:  "; tree.Inorder();
			cout << endl << "Postorder traversal:  "; tree.Postorder();
			cout << endl;
		}
		else if (command == "find") {
			cin >> str;
			if (tree.Find(str, dval)) {
				cout << "The value of " << str << " is " << dval << endl;
			}
			else {
				cout << "No such key: " << str << endl;
			}
		}
		else {
			cout << "Invalid command: " << command << endl;
		}
	}

}