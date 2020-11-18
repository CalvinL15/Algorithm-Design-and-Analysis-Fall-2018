#include <stdio.h>
#include <string.h>
#define RANGE 300000
#define SIZE 1000001
#pragma optimize "O3"

typedef long long int ll;
 
void karatsubamult(ll *result, const ll *poly1, const ll *poly2, int k){
    ll t0[k], t1[k], r[k<<1];
    int i, j;
    memset(r, 0, (k<<1) * sizeof(ll));
    if ( k <= 4 ){ 
        for (i = 0 ; i < k; i++ )
            for (j = 0 ; j < k; j++){
                r[i + j] += poly1[i] * poly2[j];
            }
    } 
	
	else {
        int newk = (k >> 1);

        for (i = 0 ; i < newk ; i++ ){
            t0[i] = poly1[i] + poly1[newk + i];   
            t1[i] = poly2[i] + poly2[newk + i];  
            t0[i + newk] = t1[i + newk] = 0;  
        }

        karatsubamult(r + newk, t0, t1, newk);     
        karatsubamult(t0, poly1, poly2, newk);             
        karatsubamult(t1, poly1 + newk, poly2 + newk, newk); 

        for (i = 0 ; i < k ; i++ ){
            r[i] += t0[i];                        
			r[i + newk] -= t0[i] + t1[i];    
			r[i + k] += t1[i];     
        }
    }

    memcpy(result, r, (k<<1) * sizeof(ll));
}

void polyMult(ll *r, ll *poly, int j){
    if ( j & (j - 1) ){ 
        int k = 1;
        while ( k < j ) 
			k <<= 1;
        while ( ++j <= k ) 
			poly[j - 1] = 0;
        j--;
    }
    karatsubamult(r, poly, poly, j);
}
    
int main(){
   	int n;
	scanf("%d", &n);
	int i, j;
	ll saveresult[RANGE] = {0};
	int k;
	int arr[SIZE];
	int ac = 2;
	int thebiggest = 0;
	ll reoccurences[RANGE/2] = {0};
	for(i = 0; i < n; i++){
		scanf("%d", &arr[i]);
		reoccurences[arr[i]]++;
		if(thebiggest < arr[i])
		thebiggest = arr[i];
		}
		
	while(ac < 100000)
		ac = ac << 1;			
		
	polyMult(saveresult, reoccurences, ac-1);
	for(i = 0; i <= 200000; i++){
		if (i%2 == 0)
            saveresult[i] -= reoccurences[i/2];
        saveresult[i] /= 2;    
	}	
	int m;
	scanf("%d ", &m);
	for (i = 0; i < m; i++) { 
        scanf("%d",&k);
       if (k > 2*thebiggest) {
            printf("0 ");
        }
        else
            printf("%lld ", saveresult[k]);
    }
    return 0;
}
