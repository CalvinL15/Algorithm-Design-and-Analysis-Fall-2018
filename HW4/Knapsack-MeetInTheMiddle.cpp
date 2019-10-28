#include <stdio.h>
#include <algorithm>
#include <queue>
#define SIZE 2000005
#pragma GCC Optimize ("O3")
#pragma GCC Optimize ("unroll-loops")
#include <unistd.h>

//reference: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
//reference: www.geeksforgeeks.org/meet-in-the-middle/
//reference: https://community.topcoder.com/tc?module=HSProblemSolution&cr=21111148&rd=10763&pm=6742
//reference: https://www.geeksforgeeks.org/implementation-of-0-1-knapsack-using-branch-and-bound/

using namespace std;
typedef long long ll;

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

ll swap(ll a, ll b){
	if( a >= b)
		return a;
	return b;	
}

inline bool Input(ll& a) {
  static char p;
  while ((p = Readchar()) < '-')
    if (!p) return false;
  a = p ^ '0';
  while ((p = Readchar()) >= '0') a = a * 10 + (p ^ '0');
  return true;
}

struct Item{
	ll value;
	ll weight;
};

struct Item X[SIZE];
struct Item Y[SIZE];

bool cmp(struct Item a, struct Item b){
	ll r1 = a.weight, r2 = b.weight;
	return (r1 < r2);
}

ll knapSack(ll W, ll wt[], ll val[], int n) 
{  
	if (n == 0 || W == 0) 
       return 0; 
	
   if (wt[n-1] > W) 
       return knapSack(W, wt, val, n-1); 
   else return swap(val[n-1] + knapSack(W-wt[n-1], wt, val, n-1), knapSack(W, wt, val, n-1)); 
} 


ll KnapSum(struct Item arr[], int n, int c, struct Item sav[]){
	for(int i = 0; i<(1<<n); i++){
		ll sval = 0;
		ll swei = 0;
		for (int j=0; j<n; j++) 
            if (i & (1<<j)){
                sval += arr[j+c].value;
				swei += arr[j+c].weight;	
			}
    	sav[i].value = sval;
		sav[i].weight = swei; 
    } 	
}  

ll SolveKnap(struct Item arr[], int n, int W){
	KnapSum(arr, n/2, 0, X);
	KnapSum(arr, n-n/2, n/2, Y);
	int size_X = 1<<(n/2); 
    int size_Y = 1<<(n-n/2); 
    ll max = -1;
    // Sort X and Y by weight
    sort(Y, Y + size_Y, cmp);
    sort(X, X + size_X, cmp);
    
    for (int i=0; i<size_X; i++){
			if(X[i].weight <= W){
				if(max < X[i].value)
					max = X[i].value;
			}
			else break;	 
		}
		
	for (int i = 0; i<size_Y; i++){
			if(Y[i].weight <= W){
				if(max < Y[i].value)
					max = Y[i].value;
			}
			else break;
		}	

	for (int i = 0; i<size_X; i++){
		int mi = 0, ma = size_Y - 1, av;
		while(mi < ma){
			av = (mi+ma+1)/2;
			if(Y[av].weight + X[i].weight <= W){
				if(Y[av].value + X[i].value > max)
					max = Y[av].value + X[i].value;
				mi = av;	
			}
			else 
				ma = av-1;	
		}			
	}
	
	for (int i = 0; i<size_Y; i++){
		int me = 0, mo = size_X - 1, avg;
		while(me < mo){
			avg = (me+mo+1)/2;
			if(X[avg].weight + Y[i].weight <= W){
				if(X[avg].value + Y[i].value > max)
					max = X[avg].value + Y[i].value;
				me = avg;	
			}
			else 
				mo = avg-1;	
		}
	}
	int mi = 0, ma = size_Y - 1, av;
	int me = 0, mo = size_X - 1, avg;
	while(mi < ma || me < mo){
		av = (mi+ma+1)/2;
		avg = (me+mo+1)/2;
		if(X[avg].weight + Y[av].weight <= W){
			if(Y[av].value + X[avg].value > max)
				max = Y[av].value + X[avg].value;
				mi = av;
				me = avg;
		}
		else{
			ma = av-1;
			mo = avg-1;
		}
	}	
	return max; 
}


int main() {
	ll N, W;
	Input(N);
	Input(W);
	Item items[N+1];
	ll val[N+1];
	ll w[N+1];
	for (int i = 0; i < N; i++){
		Input(items[i].value);
		Input(items[i].weight);
		val[i] = items[i].value;
		w[i] = items[i].weight;
	}
	ll res;
	if(N > 20)
		res = SolveKnap(items, N, W);	
	else res = knapSack(W, w, val, N);	
 	printf("%lld", res);
	return 0;
}
