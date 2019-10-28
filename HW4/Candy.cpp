#include<stdio.h> 
#pragma optimize ("O3")
#include <unistd.h>

//ref: https://www.geeksforgeeks.org/m-coloring-problem-backtracking-5/
//ref: travelsciencetech.blogspot.com/2012/10/graph-coloring-problem-with.html

const int kBuf = 131072;
inline char Readchar() {
  static char buf[kBuf], *p = buf, *end = buf;
  if (p == end) {
    end = buf + read(0, buf, kBuf);
	p = buf;
    if (end == p) 
		return 0;
  }
  return *p++;
}

inline bool Input(int& a) {
  static char p;
  while ((p = Readchar()) < '-')
    if (!p) return false;
  a = p ^ '0';
  while ((p = Readchar()) >= '0') a = a * 10 + (p ^ '0');
  return true;
}

int v;
int PRINT;
int x[50];
int G[50][50];

void next_color(int k){
	int i,j;
	x[k] = 1;
	for(i = 0; i<k; i++)
		if(G[i][k] != 0 && x[k] == x[i])
			x[k] = x[i]+1;
}
 
bool isSafe (int vtx, bool graph[][21], int color[], int c) 
{ 
	for (int i = 0; i < v; i++) 
		if (graph[vtx][i] && c == color[i]) 
			return false; 
	return true; 
} 

bool graphColoringUtil(bool graph[21][21], int m, int color[], int vtx) 
{ 	
	if (vtx == v) {
		int tempmax = -1;
		int m1 = 0, m2 = 0, m3 = 0;
		for(int vtx; vtx < v; vtx++){
			if(color[vtx] == 1)
				m1++;
			if(color[vtx] == 2)
				m2++;
			if(color[vtx] == 3)
				m3++;		 
		}
		if(m1 > m2)
			tempmax = m1;
		else tempmax = m2;
		if(tempmax < m3)
			tempmax = m3;
		if(PRINT < tempmax)
			PRINT = tempmax;
		tempmax = -1;		
		return true;
	}

	for (int c = 1; c <= m; c++) 
	{ 
		if (isSafe(vtx, graph, color, c) == true) 
		{ 
		color[vtx] = c; 

		(graphColoringUtil (graph, m, color, vtx+1)); 
		color[vtx] = 0; 
		} 
	} 
} 

int main() 
{ 	
	int e;
	int color[3] = {1, 2, 3};
	Input(v);
	Input(e);
	bool Graph[21][21];
	for(int i = 0; i<v; i++)
		for(int j = 0; j<v; j++){
			Graph[i][j] = 0;
			G[i][j] = 0;	
		}
	int a, b; 		
	
	for(int i = 0; i<e; i++){
		Input(a);
		Input(b);
		G[a-1][b-1] = 1;
		G[b-1][a-1] = 1;
		Graph[a-1][b-1] = 1;
		Graph[b-1][a-1] = 1;
	}

	if(v < 20 ){
        graphColoringUtil (Graph, 3, color, 0);
		if(PRINT != 0)
		printf("%d", PRINT);
		else printf("-1"); 
	}
	else{
		for(int i = 0; i<v; i++)
			next_color(i);
		int max = -1;
		for(int i = 0; i<v; i++){
			if(max < x[i])
				max = x[i];
			}
		if(max > 3){
			printf("-1");
		}
		else {
			int meow1 = 0, meow2 = 0, meow3 = 0;
			for(int i = 0; i<v; i++){
				if(x[i] == 1)
					meow1++;
				else if(x[i] == 2)
					meow2++;
				else meow3++;	
			}
			int output;
			if(meow1 > meow2)
				output = meow1;
			else output = meow2;
			if(output < meow3)
				output = meow3;
			printf("%d", output);		
		}
	}
	return 0; 
} 

