#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx")
#include <algorithm>
#include <vector>
#include <bits/stdc++.h> 
#include <unistd.h>
#include <cstring>
using namespace std; 
#define MAX_ 200000

//Reference: https://www.geeksforgeeks.org/topological-sorting/
//Reference: https://www.hackerrank.com/challenges/string-similarity/topics
const int kBuf = 131072;
inline int my_getchar() {
	const int N = 1<<20;
	static char buf[N];
	static char *p = buf , *end = buf;
	if(p == end) {
		if((end = buf + fread(buf , 1 , N , stdin)) == buf) return EOF;
			p = buf;
	}
	return *p++;
}

inline int readint(int &x) {
	static char c;
	while((c = my_getchar()) < '-') {
		if(c == EOF) return 0;
	}
	x = c - '0';
	while((c = my_getchar()) >= '0') x = (x << 3) + (x << 1) + (c - '0');
	return 1;
}

char buf_[kBuf]; size_t size_;
inline void Flush_() { write(1, buf_, size_); size_ = 0; }
inline void CheckFlush_(size_t sz) { if (sz + size_ > kBuf) Flush_(); }

inline void PutInt(long long a) {
	static char tmp[22] = "01234567890123456789 ";
	CheckFlush_(16);
	int tail = 20;
	if (!a) {
		tmp[--tail] = '0';
	} else {
		for (; a; a /= 10) tmp[--tail] = (a % 10) ^ '0';
	}
	memcpy(buf_ + size_, tmp + tail, 21 - tail);
	size_ += 21 - tail;
}

class Graph { 
    int V;
    list<int> *adj; 
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack); 
public: 
    Graph(int V);	//constructor
    void addEdge(int v, int w); 
    void topologicalSort(); 
    int Search(int x, int y);
}; 
  
Graph::Graph(int V) { 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::addEdge(int v, int w) { 
    adj[v].push_back(w); 
} 

int Graph::Search(int x, int y) {
	for (auto i : adj[x]) 
		if (i == y)
			return 1;
	return 0;
}

void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack) { 
    visited[v] = true; 
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            topologicalSortUtil(*i, visited, Stack); 
    Stack.push(v); 
} 

void Graph::topologicalSort() 
{ 
    stack<int> Stack; 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
    for (int i = 0; i < V; i++) 
      if (visited[i] == false) 
        topologicalSortUtil(i, visited, Stack); 
    while (Stack.empty() == false) { 
        PutInt(Stack.top()+1);
        Stack.pop(); 
    }
    buf_[size_++] = '\n';
} 

typedef struct {
	int u;
	int v;
}meow;

bool cmp(meow a, meow b) {
	if (a.u != b.u)
		return a.u < b.u;
	else
		return a.v < b.v;
}
int master[MAX_];
meow edges[MAX_];
vector<int> lengths(MAX_);
vector<int> lcp(MAX_);
vector<int> sa(MAX_);

void kasai(int s[], int n, vector<int> sa) {
    int k=0;
    vector<int> rank(n,0);
    for(int i=0; i<n; i++) {
    	rank[sa[i]]=i;
    }

    for(int i=0; i<n; i++, k?k--:0)
    {
        if(rank[i]==n-1) {
        	k=0; 
        	continue;
        }
        int j = sa[rank[i]+1];
        while (i+k<n && j+k<n && s[i+k]==s[j+k]) 
        	k++;
        lcp[rank[i]]=k;
    }
    return;
}

void solve(int n, int k) {
	Graph g(k);
	int a, j, posa, posb, flag = 0;
	int count = 0;
	kasai(master, n, sa);
	for (int i = 0; i < n-1; i++) {
		int min = (lengths[i] < lengths[i+1]) ? lengths[i]: lengths[i+1];
		if (min == lcp[i])
			continue;
		else {
			edges[count].u = master[sa[i] + lcp[i]]-1;
			edges[count].v = master[sa[i+1] + lcp[i]]-1;
			count++;
		}
	}
	std::sort(edges, edges+count, cmp);
	for (int i = 0; i < count; i++) {
		if (i == 0)	{
			g.addEdge(edges[0].u, edges[0].v);
			continue;
		}
		g.addEdge(edges[i].u, edges[i].v);
	}
	g.topologicalSort();
	return;
}

int main(int argc, char const *argv[])
{
	int T, n, k, temp;
	readint(T);
	for (int i = 0; i < T; i++) {
		readint(n);
		readint(k);
		for (int j = 0; j < n; j++) {
			readint(master[j]);
		}
		for (int j = 0; j < n; j++) {
			readint(temp);
			sa[temp-1] = j;
			lengths[temp-1] = n-j;
		}
		solve(n, k);
	}
	Flush_();
	return 0;
}
