#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <unistd.h>
#define SIZE 1000001
#pragma GCC Optimize("O3")
#pragma GCC Optimize("unroll-loops")


//reference: //https://www.geeksforgeeks.org/printing-items-01-knapsack///

typedef long long int ll;

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

inline bool Input(ll& a) {
  static char p;
  while ((p = Readchar()) < '-')
    if (!p) return false;
  a = p ^ '0';
  while ((p = Readchar()) >= '0') a = a * 10 + (p ^ '0');
  return true;
}

ll min(ll a, ll b){
	if(a > b)
		return b;
	else return a;	
}

ll max(ll a, ll b){
	if(a < b)
		return b;
	else return a;		
}

struct Items{
	ll value;
	ll weight;
//	ll v_approx;
};

int count = 0;
int output[1003];

//ll A[1003][SIZE];
ll knapsack(ll W, ll wt[], ll val[], ll n){
	int i, w; 
    long long int K[n + 1][W + 1]; 
  
    // Build table K[][] in bottom up manner 
    for (i = 0; i <= n; i++) { 
        for (w = 0; w <= W; w++) { 
            if (i == 0 || w == 0) 
                K[i][w] = 0; 
            else if (wt[i - 1] <= w) 
                K[i][w] = max(val[i - 1] +  K[i - 1][w - wt[i - 1]], K[i - 1][w]); 
            else
                K[i][w] = K[i - 1][w]; 
        } 
    }  
    long long int res = K[n][W]; 
    w = W; 
    for (i = n; i > 0 && res > 0; i--) { 
        
        if (res == K[i - 1][w])  
            continue;         
        else { 
  			output[count] = i;
			count++;           
            res = res - val[i - 1]; 
            w = w - wt[i - 1]; 
		}
	}
}


ll Knapsack(struct Items arr[], ll W, ll n, ll V){
	ll A[n+3][V+2];
//	ll A[1003][V+10000];
//	A[0][0] = 0;
//	for(int i = 0; i<=n; i++){
//		A[i][0] = 0;
//	}
	for(int i = 0; i<=V; i++){
		A[0][i] = W+1;
	}
	for(int i = 1; i<n+2; i++){
		for(int j = 1; j<=V; j++){
		//	if(arr[i].value <= j)
				A[i][j] = min(A[i-1][j], arr[i].weight + A[i-1][max(j-arr[i].value, 0)]);	
		//	else A[i][j] = A[i-1][j];
		}
	}
	
	ll OPT = 0;
//	for(int i = 1; i<n+2; i++){
		for(int j = 0; j<=V; j++){
			if(A[n][j] <= W && OPT <= j){
					OPT = j;
				}
		}
	//}
//	return OPT;
//	for(int i = 0; i<n; i++){
//		for(int j = 0; j<=V; j++){
//			printf("%d ", A[n][j]);
			//printf("\n");
//		}
	//	printf("\n");
//	}
	ll p = OPT;
	for(int i = n+2; i>=2; i--){
		if(arr[i].value <= p){
			if(arr[i].weight + A[i-1][p-arr[i].value] < A[i-1][p]){
				output[count] = i-1;
				count++;
				p = p - arr[i].value;
			}
		}
	}
}


int main(){
	ll n, W;
	Input(n);
//    scanf("%lld %lld", &n, &W);
	Input(W);
//	ll V = 0;
	ll LB = 0;
//	ll V_approx = 0;
	Items item[1004];
	ll val[1001], wt[1001];
	for(int i = 0; i<n; i++){
		Input(item[i+2].value);
        Input(item[i+2].weight);
//      scanf("%lld %lld", &item[i+2].value, &item[i+2].weight);
		val[i] = item[i+2].value;
		wt[i] = item[i+2].weight;  
		//Input(item[i+2].value);
		//Input(item[i+2].weight);
//		V = V + item[i+2].value;
		if(LB < item[i+2].value)
			LB = item[i+2].value;
	}
///	float err = 0.1;
///	float K = (err*LB)/n;
	ll B = 0;
	for(int i = 0; i<n; i++){
		ll temp = floor(item[i+2].value/(0.1*LB));
		item[i+2].value = temp;
		B += item[i+2].value;
	}
	if(n*W <= 1000)
		knapsack(W, wt, val, n);
	else Knapsack(item, W, n, B);
	printf("%d\n", count);
	for(int i = 0; i<count; i++){
		printf("%d ", output[i]);
	}
	return 0;
}
