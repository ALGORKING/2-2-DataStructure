#include <iostream>
#include <queue>
#define MAX 99999
using namespace std;
template <typename T>
class Chain;
template <typename T>
class WChain;
template <typename T>
class ChainNode {
private:
	T data;
	ChainNode<T>* link;
public:
	ChainNode(T d = 0, ChainNode<T>* l = NULL) :data(d), link(l) {}
	friend class Chain<T>;
	friend class LinkedGraph;
	friend class LinkedDiGraph;
	friend ostream& operator<<(ostream&, Chain<T>*);
};
template <typename T>
class ChainWNode {
private:
	T data;
	int weight;
	ChainWNode<T>* link;
public:
	ChainWNode(T d = 0,int w=0, ChainWNode<T>* l = NULL) :data(d), link(l),weight(w) {}
	friend class WChain<T>;
	friend class LinkedWDiGraph;
	friend ostream& operator<<(ostream&, Chain<T>*);
};
template <typename T>
class Chain {
private:
	ChainNode<T>* first;
	ChainNode<T>* last;
public:
	Chain() { last = first = NULL; }
	friend ostream& operator<<(ostream&, Chain<T>&);
	friend class LinkedGraph;
	friend class LinkedDiGraph;
	friend class LinkedWDiGraph;
	void InsertBack(T& e) {
		if (!first) {
			first = last = new ChainNode<T>(e);
		}
		else {
			last = last->link = new ChainNode<T>(e);
		}
	}
	int count() {
		ChainNode<T>* cur = first;
		int cou = 0;
		while (cur) {
			cur = cur->link;
			cou++;
		}
		return cou;
	}
	bool Find(int v) {
		ChainNode<T>* cur = first;
		while (cur) {
			if (cur->data == v) { return true; }
			cur = cur->link;
		}
		return false;
	}
	void NormalDelete(T& k) {
		ChainNode<T>* cur = first;
		ChainNode<T>* prev = first;
		while (cur) {
			if (cur->data == k) {
				if (first == cur) {
					ChainNode<T>* p = first;
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
	void showall() {
		ChainNode<T>* cur = first;
		while (cur) {
			cout << cur->data << " ";
			cur = cur->link;
		}
		cout << endl;
	}
};
template <typename  T>
class WChain {
private:
	ChainWNode<T>* first;
	ChainWNode<T>* last;
public:
	WChain() { last = first = NULL; }
	friend ostream& operator<<(ostream&, Chain<T>&);
	friend class LinkedGraph;
	friend class LinkedDiGraph;
	friend class LinkedWDiGraph;
	void InsertBack(T& e,int w) {
		if (!first) {
			first = last = new ChainWNode<T>(e,w);
		}
		else {
			last = last->link = new ChainWNode<T>(e,w);
		}
	}
	int count() {
		ChainWNode<T>* cur = first;
		int cou = 0;
		while (cur) {
			cur = cur->link;
			cou++;
		}
		return cou;
	}
	bool Find(int v) {
		ChainWNode<T>* cur = first;
		while (cur) {
			if (cur->data == v) { return true; }
			cur = cur->link;
		}
		return false;
	}
	void NormalDelete(T& k) {
		ChainWNode<T>* cur = first;
		ChainWNode<T>* prev = first;
		while (cur) {
			if (cur->data == k) {
				if (first == cur) {
					ChainWNode<T>* p = first;
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
	void showall() {
		ChainWNode<T>* cur = first;
		while (cur) {
			cout << cur->data << " "<<cur->weight<<" ";
			cur = cur->link;
		}
		cout << endl;
	}
};
template <typename T>
ostream& operator<<(ostream& os, Chain<T>& il) {
	ChainNode<T>* ptr = il.first;
	while (ptr != NULL) {
		os << ptr->data << " ";
		ptr = ptr->link;
	}
	os << endl;
	return os;
}
class Graph {
protected:
	int n;//정점의 수
	int e;//간선의 수
	bool* visited;
public:
	//virtual ~Graph() = 0;
	bool isempty() const { return n == 0; }//그래프에 정점이 없으면 true를 반환
	int NumberofVertices() const { return n; }//그래프의 정점의 수를 반환
	int NumberofEdges() const { return e; }//그래프의 간선의 수를 반환
	virtual int Degree(int u) const = 0;//정점 u에 인접한 간선의 수를 반환
	virtual bool ExistsEdge(int u, int v) const = 0;//그래프에 간선 u,v가 있으면 true반환
	//virtual void InsertEdge(int u, int v) = 0;//간선 u,v를 그래프에 삽입
	virtual void DeleteVertex(int v) = 0;//정점 v와 이에 인접한 모든 간선을 삭제
	virtual void DeleteEdge(int u, int v) = 0;//그래프에 간선 u,v를 삭제
	virtual void DFS() = 0;
	virtual void DFS(const int v) = 0;
	virtual void BFS(int v) = 0;
};
class MatrixGraph :public Graph {
private:
	int** matrix;
public:
	MatrixGraph(const int vertices = 0) {
		e = 0;
		n = vertices;
		matrix = new int* [n];
		for (int i = 0; i < n; i++) {
			matrix[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = 0;
			}
		}
	}
	~MatrixGraph() {
		for (int i = 0; i < n; i++) {
			delete[]matrix[i];
		}
		delete[]matrix;
	}
	int Degree(int u) const {
		int count = 0;
		for (int i = 0; i < n; i++) {
			if (!matrix[u][i]) {
				count++;
			}
		}
		return count;
	}
	bool ExistsEdge(int u, int v) const {
		if (matrix[u][v]!=0) {
			return true;
		}
		else {
			return false;
		}
	}
	void InsertEdge(int u, int v) {
		if (!matrix[u][v]) {
			matrix[u][v] = 1;
			matrix[v][u] = 1;
			e++;
		}
	}
	void InsertVertex(int v) {
		n++;
		int** matrix2 = new int* [n];
		for (int i = 0; i < n; i++) {
			matrix2[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matrix2[i][j] = 0;
			}
		}
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				matrix2[i][j] = matrix[i][j];
			}
		}
		for (int i = 0; i < n - 1; i++) {
			delete[]matrix[i];
		}
		delete matrix;
		matrix = matrix2;
	}
	void ShowMatrixGraph() {
		cout << "showmatrixGraph()" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << matrix[i][j] << " ";
			}cout << endl;
		}
	}
	void DeleteVertex(int v) {
		for (int i = 0; i < n; i++) {
			if (matrix[v][i] != 0||matrix[i][v]!=0) {
				matrix[v][i] = 0;
				matrix[i][v] = 0;
				e--;
			}
		}
	}
	void DeleteEdge(int u, int v) {
		if (matrix[u][v]) {
			matrix[u][v] = 0;
			matrix[v][u] = 0;
			e--;
		}
	}
	void DFS() {
		visited = new bool[n];
		fill(visited, visited + n, false);
		DFS(0);
		delete[]visited;
	}
	void DFS(const int v) {
		cout << v << " ";
		visited[v] = true;
		for (int i = 0; i < n; i++) {
			if (matrix[v][i] && !visited[i]) {
				DFS(i);
			}
		}
	}
	void BFS(int v) {
		visited = new bool[n];
		fill(visited, visited + n, false);
		visited[v] = true;
		queue<int> q;
		q.push(v);
		while (!q.empty()) {
			v = q.front();
			q.pop();
			cout << v << " ";
			for (int i = 0; i < n; i++) {
				if (!visited[i] && matrix[v][i]) {
					q.push(i);
					visited[i] = true;
				}
			}
		}
		delete[] visited;
	}
};
class MatrixDiGraph :public Graph {
private:
	int** matrix;
public:
	MatrixDiGraph(const int vertices = 0) {
		e = 0;
		n = vertices;
		matrix = new int* [n];
		for (int i = 0; i < n; i++) {
			matrix[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = 0;
			}
		}
	}
	~MatrixDiGraph() {
		for (int i = 0; i < n; i++) {
			delete[]matrix[i];
		}
		delete[]matrix;
	}
	int Degree(int u) const {
		int count = 0;
		for (int i = 0; i < n; i++) {
			if (matrix[u][i]) {
				count++;
			}
		}
		return count;
	}
	bool ExistsEdge(int u, int v) const {
		if (matrix[u][v] != 0) {
			return true;
		}
		else {
			return false;
		}
	}
	void InsertEdge(int u, int v) {
		if (!matrix[u][v]) {
			matrix[u][v] = 1;
			e++;
		}
	}
	void InsertVertex(int v) {
		n++;
		int** matrix2 = new int* [n];
		for (int i = 0; i < n; i++) {
			matrix2[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matrix2[i][j] = 0;
			}
		}
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				matrix2[i][j] = matrix[i][j];
			}
		}
		for (int i = 0; i < n - 1; i++) {
			delete[]matrix[i];
		}
		delete matrix;
		matrix = matrix2;
	}
	void ShowMatrixDiGraph() {
		cout << "showmatrixDiGraph()" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << matrix[i][j] << " ";
			}cout << endl;
		}
	}
	void DeleteVertex(int v) {
		for (int i = 0; i < n; i++) {
			if (matrix[v][i] != 0) {
				matrix[v][i] = 0;
				e--;
			}
		}
	}
	void DeleteEdge(int u, int v) {
		if (matrix[u][v]) {
			matrix[u][v] = 0;
			e--;
		}
	}
	void DFS() {
		visited = new bool[n];
		fill(visited, visited + n, false);
		DFS(0);
		delete[]visited;
	}
	void DFS(const int v) {
		cout << v << " ";
		visited[v] = true;
		for (int i = 0; i < n; i++) {
			if (matrix[v][i] && !visited[i]) {
				DFS(i);
			}
		}
	}
	void BFS(int v) {
		visited = new bool[n];
		fill(visited, visited + n, false);
		visited[v] = true;
		queue<int> q;
		q.push(v);
		while (!q.empty()) {
			v = q.front();
			q.pop();
			cout << v << " ";
			for (int i = 0; i < n; i++) {
				if (!visited[i] && matrix[v][i]) {
					q.push(i);
					visited[i] = true;
				}
			}
		}
		delete[] visited;
	}
};
class MatrixWDiGraph :public Graph {
private:
	int** matrix;
public:
	MatrixWDiGraph(const int vertices = 0) {
		e = 0;
		n = vertices;
		matrix = new int* [n];
		for (int i = 0; i < n; i++) {
			matrix[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) { matrix[i][j] = 0; }
				else {
					matrix[i][j] = MAX;
				}
			}
		}
	}
	~MatrixWDiGraph() {
		for (int i = 0; i < n; i++) {
			delete[]matrix[i];
		}
		delete[]matrix;
	}
	int Degree(int u) const {
		int count = 0;
		for (int i = 0; i < n; i++) {
			if (matrix[u][i]!=MAX&&matrix[u][i]!=0) {
				count++;
			}
		}
		return count;
	}
	bool ExistsEdge(int u, int v) const {
		if (matrix[u][v] != MAX) {
			return true;
		}
		else {
			return false;
		}
	}
	void InsertEdge(int u, int v,int weight) {
		if (matrix[u][v]==MAX) {
			matrix[u][v] = weight;
			e++;
		}
	}
	void InsertVertex(int v) {
		n++;
		int** matrix2 = new int* [n];
		for (int i = 0; i < n; i++) {
			matrix2[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matrix2[i][j] = MAX;
			}
		}
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				matrix2[i][j] = matrix[i][j];
			}
		}
		for (int i = 0; i < n - 1; i++) {
			delete[]matrix[i];
		}
		delete matrix;
		matrix = matrix2;
	}
	void ShowMatrixWDiGraph() {
		cout << "showmatrixWDiGraph()" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%-6d", matrix[i][j]);
			}cout << endl;
		}
	}
	void DeleteVertex(int v) {
		for (int i = 0; i < n; i++) {
			if (matrix[v][i] != 0) {
				matrix[v][i] = MAX;
				matrix[i][v] = MAX;
			}
		}
	}
	void DeleteEdge(int u, int v) {
		if (matrix[u][v]!=MAX) {
			matrix[u][v] = MAX;
			e--;
		}
	}
	void DFS() {
		visited = new bool[n];
		fill(visited, visited + n, false);
		DFS(0);
		delete[]visited;
	}
	void DFS(const int v) {
		cout << v << " ";
		visited[v] = true;
		for (int i = 0; i < n; i++) {
			if (matrix[v][i] && !visited[i]) {
				DFS(i);
			}
		}
	}
	void BFS(int v) {
		visited = new bool[n];
		fill(visited, visited + n, false);
		visited[v] = true;
		queue<int> q;
		q.push(v);
		while (!q.empty()) {
			v = q.front();
			q.pop();
			cout << v << " ";
			for (int i = 0; i < n; i++) {
				if (!visited[i] && matrix[v][i]) {
					q.push(i);
					visited[i] = true;
				}
			}
		}
		delete[] visited;
	}
	void ShortestPath(const int n, const int v) {
		bool* s = new bool[n];
		int* dist = new int[n];
		for (int i = 0; i < n; i++) {
			s[i] = false; dist[i] = matrix[v][i];
		}
		s[v] = true;
		dist[v] = 0;
		for (int i = 0; i < n - 2; i++) {
			int u = 0;
			for (int w = 0; w < n; w++) {
				if (!s[w] && (dist[u] == 0 || dist[u] > dist[w])) {
					u = w;
				}
			}
			for (int i = 0; i < n; i++) {
				cout << dist[i] << " ";
			}
			cout << endl;
			cout << v << "," << u << "weighted:" << dist[u] << endl;
			s[u] = true;
			for (int w = 0; w < n; w++) {
				if (!s[w] && dist[u] + matrix[u][w] < dist[w]) {
					dist[w] = dist[u] + matrix[u][w];
				}
			}
		}
		/*int t = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == false) {
				t = i;
				s[i] = true;
				break;
			}
		}
		cout << v << "," << t << "weighted:" << dist[t] << endl;*/
	}
	void AllLengths(const int n) {
		cout << "All Lengths" << endl;
		int** a = new int* [n];
		for (int i = 0; i < n; i++) {
			a[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				a[i][j] = matrix[i][j];
			}
		}
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (a[i][k] + a[k][j] < a[i][j]) {
						a[i][j] = a[i][k] + a[k][j];
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%-6d", a[i][j]);
			}
			cout << endl;
		}
	}
};
class LinkedGraph :public Graph {
private:
	Chain<int>* adjLists;
public:
	LinkedGraph(const int vertices = 0) {
		n = vertices;
		e = 0;
		adjLists = new Chain<int>[n];
	}
	~LinkedGraph(){}
	int Degree(int u) const {
		return adjLists[u].count();
	}
	bool ExistsEdge(int u, int v) const {
		return adjLists[u].Find(v);
	}
	void InsertVertex(int v){}//정점 v를 삽입
	void InsertEdge(int u, int v) {
		adjLists[u].InsertBack(v);
		adjLists[v].InsertBack(u);
		e++;
	}
	void DeleteVertex(int v){}//정점 v와 이에 인접한 모든 간선을 삭제
	void DeleteEdge(int u, int v) {
		adjLists[u].NormalDelete(v);
		adjLists[v].NormalDelete(u);
		e--;
	}
	void ShowLinkedGraph() {
		for (int i = 0; i < n; i++) {
			cout << "adjLists[" << i << "]";
			adjLists[i].showall();
		}
	}
	void DFS() {
		visited = new bool[n];
		fill(visited, visited + n, false);
		DFS(0);
		delete[]visited;
	}
	void DFS(const int v){
		visited[v] = true;
		cout << v << " ";
		for (ChainNode<int>* p = adjLists[v].first; p != NULL; p = p->link) {
			if (!visited[p->data]) {
				DFS(p->data);
			}
		}
	}
	void BFS(int v) {
		visited = new bool[n];
		fill(visited, visited + n, false);
		visited[v] = true;
		queue<int> q;
		q.push(v);
		while (!q.empty()) {
			v = q.front();
			cout << v << " ";
			q.pop();
			for (ChainNode<int>* p = adjLists[v].first; p != NULL; p = p->link) {
				if (!visited[p->data]) {
					q.push(p->data);
					visited[p->data] = true;
				}
			}
		}
		delete[]visited;
	}
};
class LinkedDiGraph :public Graph {
private:
	Chain<int>* adjLists;
public:
	LinkedDiGraph(const int vertices = 0) {
		n = vertices;
		e = 0;
		adjLists = new Chain<int>[n];
	}
	~LinkedDiGraph() {}
	int Degree(int u) const {
		return adjLists[u].count();
	}
	bool ExistsEdge(int u, int v) const{
		return adjLists[u].Find(v);
	}
	void InsertVertex(int v) {}//정점 v를 삽입
	void InsertEdge(int u, int v) {
		adjLists[u].InsertBack(v);
		e++;
	}
	void DeleteVertex(int v) {}//정점 v와 이에 인접한 모든 간선을 삭제
	void DeleteEdge(int u, int v) {
		adjLists[u].NormalDelete(v);
		e--;
	}
	void ShowLinkedGraph() {
		for (int i = 0; i < n; i++) {
			cout << "adjLists[" << i << "]";
			adjLists[i].showall();
		}
	}
	void DFS() {
		visited = new bool[n];
		fill(visited, visited + n, false);
		DFS(0);
		delete[]visited;
	}
	void DFS(const int v) {
		visited[v] = true;
		cout << v << " ";
		for (ChainNode<int>* p = adjLists[v].first; p != NULL; p = p->link) {
			if (!visited[p->data]) {
				DFS(p->data);
			}
		}
	}
	void BFS(int v) {
		visited = new bool[n];
		fill(visited, visited + n, false);
		visited[v] = true;
		queue<int> q;
		q.push(v);
		while (!q.empty()) {
			v = q.front();
			cout << v << " ";
			q.pop();
			for (ChainNode<int>* p = adjLists[v].first; p != NULL; p = p->link) {
				if (!visited[p->data]) {
					q.push(p->data);
					visited[p->data] = true;
				}
			}
		}
		delete[]visited;
	}
};
class LinkedWDiGraph :public Graph {
private:
	WChain<int>* adjLists;
public:
	LinkedWDiGraph(const int vertices = 0) {
		n = vertices;
		e = 0;
		adjLists = new WChain<int>[n];
	}
	~LinkedWDiGraph() {}
	int Degree(int u) const {
		return adjLists[u].count();
	}
	bool ExistsEdge(int u, int v) const {
		return adjLists[u].Find(v);
	}
	void InsertVertex(int v) {}//정점 v를 삽입
	void InsertEdge(int u, int v,int w) {
		adjLists[u].InsertBack(v, w);
		e++;
	}
	void DeleteVertex(int v) {}//정점 v와 이에 인접한 모든 간선을 삭제
	void DeleteEdge(int u, int v) {
		adjLists[u].NormalDelete(v);
		e--;
	}
	void ShowLinkedWDiGraph() {
		for (int i = 0; i < n; i++) {
			cout << "adjLists[" << i << "]";
			adjLists[i].showall();
		}
	}
	void DFS() {
		visited = new bool[n];
		fill(visited, visited + n, false);
		DFS(0);
		delete[]visited;
	}
	void DFS(const int v) {
		visited[v] = true;
		cout << v << " ";
		for (ChainWNode<int>* p = adjLists[v].first; p != NULL; p = p->link) {
			if (!visited[p->data]) {
				DFS(p->data);
			}
		}
	}
	void BFS(int v) {
		visited = new bool[n];
		fill(visited, visited + n, false);
		visited[v] = true;
		queue<int> q;
		q.push(v);
		while (!q.empty()) {
			v = q.front();
			cout << v << " ";
			q.pop();
			for (ChainWNode<int>* p = adjLists[v].first; p != NULL; p = p->link) {
				if (!visited[p->data]) {
					q.push(p->data);
					visited[p->data] = true;
				}
			}
		}
		delete[]visited;
	}
	void ShortestPath(const int n, const int v) {
		bool* s = new bool[n];
		int* dist = new int[n];
		for (int i = 0; i < n; i++) {
			s[i] = false; dist[i] = MAX;
		}
		for (ChainWNode<int>* p = adjLists[v].first; p != NULL; p = p->link) {
			dist[p->data] = p->weight;
		}
		s[v] = true;
		dist[v] = 0;
		for (int i = 0; i < n - 2; i++) {
			int u = 0;
			for (int w = 0; w < n; w++) {
				if (!s[w] && (dist[u] == 0 || dist[u] > dist[w])) {
					u = w;
				}
			}
			for (int i = 0; i < n; i++) {
				cout << dist[i] << " ";
			}
			cout << endl;
			cout << v << "," << u << "weighted:" << dist[u] << endl;
			s[u] = true;
			for (ChainWNode<int>* p = adjLists[u].first; p != NULL; p = p->link) {
				if (!s[p->data] && dist[u] + p->weight < dist[p->data]) {
					dist[p->data] = dist[u] + p->weight;
				}
			}
		}
		/*int t = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == false) {
				t = i;
				s[i] = true;
				break;
			}
		}
		cout << v << "," << t << "weighted:" << dist[t] << endl;*/
	}
	void AllLengths(const int n) {
		cout << "All Lengths" << endl;
		int** a = new int* [n];
		for (int i = 0; i < n; i++) {
			a[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) { a[i][j] = 0; }
				else { a[i][j] = MAX; }
			}
		}
		for (int i = 0; i < n; i++) {
			for (ChainWNode<int>* p = adjLists[i].first; p != NULL; p = p->link) {
				a[i][p->data] = p->weight;
			}
		}
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (a[i][k] + a[k][j] < a[i][j]) {
						a[i][j] = a[i][k] + a[k][j];
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%-6d", a[i][j]);
			}
			cout << endl;
		}
	}
};
int main(void) {
	MatrixWDiGraph G(6);
	G.InsertEdge(0, 1, 50);
	G.InsertEdge(0, 2, 45);
	G.InsertEdge(0, 3, 10);
	G.InsertEdge(1, 3, 15);
	G.InsertEdge(1, 2, 10);
	G.InsertEdge(2, 4, 30);
	G.InsertEdge(3, 0, 20);
	G.InsertEdge(3, 4, 15);
	G.InsertEdge(4, 1, 20);
	G.InsertEdge(4, 2, 35);
	G.InsertEdge(5, 4, 3);
	G.ShowMatrixWDiGraph();
	G.ShortestPath(6, 0);
	G.AllLengths(6);
	cout << "LinkedWDiGraph" << endl;
	LinkedWDiGraph G2(6);
	G2.InsertEdge(0, 1, 50);
	G2.InsertEdge(0, 2, 45);
	G2.InsertEdge(0, 3, 10);
	G2.InsertEdge(1, 3, 15);
	G2.InsertEdge(1, 2, 10);
	G2.InsertEdge(2, 4, 30);
	G2.InsertEdge(3, 0, 20);
	G2.InsertEdge(3, 4, 15);
	G2.InsertEdge(4, 1, 20);
	G2.InsertEdge(4, 2, 35);
	G2.InsertEdge(5, 4, 3);
	G2.ShowLinkedWDiGraph();
	G2.ShortestPath(6, 0);
	G2.AllLengths(6);
	/*MatrixGraph mg(4);
	mg.InsertEdge(0, 1);
	mg.InsertEdge(0, 2);
	mg.InsertEdge(0, 3);
	mg.InsertEdge(1, 2);
	mg.InsertEdge(1, 3);
	mg.InsertEdge(2, 3);
	mg.ShowMatrixGraph();
	mg.DFS();
	mg.InsertVertex(5);
	mg.ShowMatrixGraph();
	mg.DeleteEdge(0, 1);
	mg.ShowMatrixGraph();
	mg.DeleteVertex(3);
	mg.ShowMatrixGraph();
	MatrixGraph two(8);
	two.InsertEdge(0, 1);
	two.InsertEdge(0, 2);
	two.InsertEdge(1, 3);
	two.InsertEdge(1, 4);
	two.InsertEdge(2, 5);
	two.InsertEdge(2, 6);
	two.InsertEdge(3, 7);
	two.InsertEdge(4, 7);
	two.InsertEdge(5, 7);
	two.InsertEdge(6, 7);
	cout << "two" << endl;
	two.ShowMatrixGraph();
	cout << "two.DFS "; two.DFS();
	cout << "two.BFS "; two.BFS(0);
	cout << "two.DFS(3) "; two.DFS();
	cout << "two.BFS(3) "; two.BFS(3);
	MatrixDiGraph mg2(4);
	mg2.InsertEdge(0, 1);
	mg2.InsertEdge(0, 2);
	mg2.InsertEdge(0, 3);
	mg2.InsertEdge(1, 2);
	mg2.InsertEdge(1, 3);
	mg2.InsertEdge(2, 3);
	mg2.ShowMatrixDiGraph();
	mg2.DFS();
	mg2.InsertVertex(5);
	mg2.ShowMatrixDiGraph();
	mg2.DeleteEdge(0, 1);
	mg2.ShowMatrixDiGraph();
	mg2.DeleteVertex(3);
	mg2.ShowMatrixDiGraph();
	LinkedGraph LG(4);
	LG.InsertEdge(0, 1);
	LG.InsertEdge(0, 2);
	LG.InsertEdge(0, 3);
	LG.InsertEdge(1, 2);
	LG.InsertEdge(1, 3);
	LG.InsertEdge(2, 3);
	LG.ShowLinkedGraph();
	for (int i = 0; i < 4; i++) {
		cout << LG.Degree(i) << endl;
	}
	if (LG.ExistsEdge(1, 3)) {
		cout << "존재합니다!" << endl;
	}
	else {
		cout << "존재하지 않습니다" << endl;
	}
	if (LG.ExistsEdge(3, 3)) {
		cout << "존재합니다!" << endl;
	}
	else {
		cout << "존재하지 않습니다" << endl;
	}
	LG.DeleteEdge(1, 3);
	LG.ShowLinkedGraph();
	for (int i = 0; i < 4; i++) {
		cout << LG.Degree(i) << endl;
	}
	if (LG.ExistsEdge(1, 3)) {
		cout << "존재합니다!" << endl;
	}
	else {
		cout << "존재하지 않습니다" << endl;
	}
	LinkedDiGraph LDG(4);
	LDG.InsertEdge(0, 1);
	LDG.InsertEdge(0, 2);
	LDG.InsertEdge(0, 3);
	LDG.InsertEdge(1, 2);
	LDG.InsertEdge(1, 3);
	LDG.InsertEdge(2, 3);
	LDG.ShowLinkedGraph();
	for (int i = 0; i < 4; i++) {
		cout << LDG.Degree(i) << endl;
	}
	if (LDG.ExistsEdge(1, 3)) {
		cout << "존재합니다!" << endl;
	}
	else {
		cout << "존재하지 않습니다" << endl;
	}
	if (LDG.ExistsEdge(3, 3)) {
		cout << "존재합니다!" << endl;
	}
	else {
		cout << "존재하지 않습니다" << endl;
	}
	LDG.DeleteEdge(1, 3);
	LDG.ShowLinkedGraph();
	for (int i = 0; i < 4; i++) {
		cout << LDG.Degree(i) << endl;
	}
	if (LDG.ExistsEdge(1, 3)) {
		cout << "존재합니다!" << endl;
	}
	else {
		cout << "존재하지 않습니다" << endl;
	}
	LinkedGraph ntwo(8);
	ntwo.InsertEdge(0, 1);
	ntwo.InsertEdge(0, 2);
	ntwo.InsertEdge(1, 3);
	ntwo.InsertEdge(1, 4);
	ntwo.InsertEdge(2, 5);
	ntwo.InsertEdge(2, 6);
	ntwo.InsertEdge(3, 7);
	ntwo.InsertEdge(4, 7);
	ntwo.InsertEdge(5, 7);
	ntwo.InsertEdge(6, 7);
	ntwo.ShowLinkedGraph();
	cout << "LINKEDGRAPH DFS(0)"; ntwo.DFS();
	cout << "LINKEDGRAPH BFS(3)"; ntwo.BFS(3);
	cout << "LINKEDGRAPH BFS(0)"; ntwo.BFS(0);*/
}